/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:35:23 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/21 14:36:33 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief setting limit value and calculate delta distances 
 * dt->delta_x  and dt->delta_y are the distance the ray has to travel to go 
 * from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
 * 
	* deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
	* deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
 * or
	* deltaDistX = abs(|rayDir| / rayDirX)
	* deltaDistY = abs(|rayDir| / rayDirY)
 * 
 * we can use 1 instead of |rayDir|, because only the *ratio* between 
 * deltaDistX and deltaDistY matters for the DDA, so:
 * 
	* deltaDistX = abs(1 / rayDirX)
	* deltaDistY = abs(1 / rayDirY)
 * to avoid problems dividing by 0, we can set the deltaDistX and deltaDistY
 * to a very high value if the rayDirX or rayDirY are 0.
 * @param dt 
 */
void	delta(t_dt *dt)
{
	if (dt->raydirx == 0)
		dt->delta_x = 1e30;
	else
		dt->delta_x = fabs(1 / dt->raydirx);
	if (dt->raydiry == 0)
		dt->delta_y = 1e30;
	else
		dt->delta_y = fabs(1 / dt->raydiry);
}

/**
 * @brief we use the direction to set the value of each step and
 * calculate the initial value of the sidedist x and y.
 * intpix and intpiy are the map position.
 * dt->pix and dt->piy are the player position.
 * Once we get the perpendicular distance to each side, 
 * we multiply it with deltaDistX or deltaDistY to get the real distance.
 * @param dt 
 */
void	init_step_sidedist(t_dt *dt)
{
	if (dt->raydirx < 0)
	{
		dt->stepx = -1;
		dt->sd_dist_x = (dt->pix - dt->intpix) * dt->delta_x;
	}
	else
	{
		dt->stepx = 1;
		dt->sd_dist_x = (dt->intpix + 1.0 - dt->pix) * dt->delta_x;
	}
	if (dt->raydiry < 0)
	{
		dt->stepy = -1;
		dt->sd_dist_y = (dt->piy - dt->intpiy) * dt->delta_y;
	}
	else
	{
		dt->stepy = 1;
		dt->sd_dist_y = (dt->intpiy + 1.0 - dt->piy) * dt->delta_y;
	}
}

/**
 * @brief The DDA algorithm will always jump exactly one square each loop 
 * untill it finds a wall.
 * 
 * dt->sd_dist_x y dt->sd_dist_y are initially the distance from 
 * ray start position to the first x-side and the first y-side.
 * dt->stepx and dt->stepy are used to know in which direction to step.
 * it will vary depending on the ray direction. (either +1 or -1)
 * dt->hit  = 0; // was there a wall hit?
 * dt->side; // was a N, S, W or E wall hit?
 * 
 * sd_dist_x and sd_dist_y get incremented with delta_x or delta_y 
 * with every jump in their direction, and mapX and mapY get incremented
 * with stepX and stepY respectively.
 * 
 * When the ray has hit a wall, the loop ends, and we'll know which side 
 * of the wall was hit save¡ing this in the variable "side",
 * and what wall was hit with intpix and intpiy.
 * we still don't know where was the exact point of the ray impact.
 * it will be calculated in the next function.
 * @param dt 
 */
void	run_dda(t_dt *dt)
{
	while (dt->hit == 0)
	{
		if (dt->sd_dist_x < dt->sd_dist_y)
		{
			dt->sd_dist_x += dt->delta_x;
			dt->intpix += dt->stepx;
			if ((dt->intpix < dt->pix))
				dt->side = 0;
			else
				dt->side = 1;
		}
		else
		{
			dt->sd_dist_y += dt->delta_y;
			dt->intpiy += dt->stepy;
			if ((dt->intpiy < dt->piy))
				dt->side = 2;
			else
				dt->side = 3;
		}
		if (dt->rmap[dt->intpix][dt->intpiy] == '1')
			dt->hit = 1;
	}
}

/**
 * @brief Set the drawing limits object
 * The fisheye effect is avoided by the way the distance is calculated here:
 * The variable dt->perp_wll_dist is used to calculate the length of the ray.
 * Depending on whether the ray hit an X side or Y side, 
 * the formula is computed using sd_dist_x, or sd_dist_y.
 * the height of the line that has to be drawn on screen: 
 * this is the inverse of perpWallDist, and then multiplied by h, 
 * the height in pixels of the screen, to bring it to pixel coordinates.
 * it can be multiplied by a factor to make the walls taller or shorter.
 * * 1.75 can be used to make the walls taller.I leave as they are to keep
 * the textures in the right proportion.
 * The center of the wall should be at the center of the screen, and if these
 * points lie outside the screen, they're capped to 0 or h-1
 * @param dt 
 */
void	set_drawing_limits(t_dt *dt)
{
	if (dt->side < 2)
		dt->perp_wll_dist = (dt->sd_dist_x - dt->delta_x);
	else
		dt->perp_wll_dist = (dt->sd_dist_y - dt->delta_y);
	dt->ln_hght = (int)(SHEIGHT / dt->perp_wll_dist);
	dt->draw_st = -dt->ln_hght / 2 + SHEIGHT / 2;
	if (dt->draw_st < 0)
		dt->draw_st = 0;
	dt->draw_end = dt->ln_hght / 2 + SHEIGHT / 2;
	if (dt->draw_end >= SHEIGHT)
		dt->draw_end = SHEIGHT - 1;
}
