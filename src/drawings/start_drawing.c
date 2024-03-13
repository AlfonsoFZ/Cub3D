/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:35:32 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/14 11:34:12 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief convert 4 bytes to an uint32_t.
 * pixels are saved in 4 bytes, so we need to convert them to an uint32_t
 * it is a reverse function of the function mlx_draw_pixel that converts an 
 * uint32_t to 4 pixels used in the mlx_put_pixel function.
 * 
 * @param conv 
 * @param n 
 * @return uint32_t 
 */
static uint32_t	clr32(uint8_t *conv, int n)
{
	uint32_t	u;

	u = conv[n] << 24;
	u += conv[n + 1] << 16;
	u += conv[n + 2] << 8;
	u += conv[n + 3];
	return (u);
}

/**
 * @brief Get the wallx object with the exact position of the impact of the ray
 * The value wallX represents the exact value where the wall was hit and will 
 * be use to get the exact texture pixel that has to be shown. Although it can
 * be the y coordenate of the wall for certain values of sides, it is always 
 * the x coordenate of the texture. 
 * 
	texturing asignation:
     the side value is usesd as the index in the texture array asigning 
	 one texture to each side vallue.

    calculate value of wallX:
		if (dt->side < 2)
			wallx = dt->piy + dt->perp_wll_dist * dt->raydiry;
		else
			wallx = dt->pix + dt->perp_wll_dist * dt->raydirx;
	substracting the entire map position to get the exact value of the
	coordenate in the texture
    	wallX -= floor((wallX));

    x coordinate on the texture:
	I have used all the texture with the same width, so texture[0] width
	is used to get the exact x coordinate. 
		dt->sc->txtur_x = (int)(wallx * (double)dt->sc->txtur[0]->width);
		
	then we flip vertically the texture in 2 of the sides to improve
	the visual effect in the corners.
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
 * 
 * step: How much to increase the texture coordinate per screen pixel
 * we calculate the step:
		step = (double)dt->sc->txtur[0]->height / dt->ln_hght;
 * tex_pos: initial position of the texture
		tex_pos = (dt->draw_st - SHEIGHT / 2 + dt->ln_hght / 2) * step;
 * color: get the color of the pixel in the texture
		color = clr32(dt->sc->txtur[dt->side]->pixels, dt->sc->txtur[0]->width
				* (int)tex_pos * 4 + (int)dt->sc->txtur_x * 4);
	position are multiplied by 4 because the pixels are saved in 4 bytes.
 * put the pixel in the screen
		mlx_put_pixel(dt->sc->walls, x, dt->i, color);
 * @param dt 
 * @param x 
 */
void	get_wallx(t_dt *dt, int x)
{
	double		wallx;
	double		step;
	double		tex_pos;
	uint32_t	color;

	if (dt->side < 2)
		wallx = dt->piy + dt->perp_wll_dist * dt->raydiry;
	else
		wallx = dt->pix + dt->perp_wll_dist * dt->raydirx;
	wallx -= floor(wallx);
	dt->sc->txtur_x = (int)(wallx * (double)dt->sc->txtur[0]->width);
	if ((dt->side == 0 || dt->side == 2))
		dt->sc->txtur_x = dt->sc->txtur[0]->width - dt->sc->txtur_x - 1;
	step = (double)dt->sc->txtur[0]->height / dt->ln_hght;
	tex_pos = (dt->draw_st - SHEIGHT / 2 + dt->ln_hght / 2) * step;
	dt->i = dt->draw_st;
	while (dt->i < dt->draw_end)
	{
		color = clr32(dt->sc->txtur[dt->side]->pixels, dt->sc->txtur[0]->width
				* (int)tex_pos * 4 + (int)dt->sc->txtur_x * 4);
		mlx_put_pixel(dt->sc->walls, x, dt->i, color);
		tex_pos += step;
		dt->i++;
	}
}

/**
 * @brief this fuction is the main drawing function, and it will be called in
 * every iteration of the game loop so we need to clean de sc->walls image if 
 * it is already created and create a new one.
 * 
 * we iterate through the screen width to calculate all the values needed to
 * calculate the height of the walls and the position of the textures.
 * @param dt 
 * rays starts at the position of the player
 * dt->pix and dt->piy represent the position vector of the player, 
 * dt->raydirx and dt->raydiry represent the direction of the player,
 * and dt->planx and dt->plany the camera plane of the player.
 * FOV is 2 * atan(0.66/1.0)=66 "perfect for a first person shooter game)"
 * camx is the x-coordinate on the camera plane that the current x of the 
 * screen represents, done this way so that the right side of the screen 
 * will get coordinate 1, the center of the screen gets coordinate 0, 
 * and the left side of the screen gets coordinate -1.
 * The direction of the ray can be calculated as the sum of the direction 
 * vector, and a part of the plane vector.
 * This has to be done x and y (since adding two vectors is adding their 
 * x-coordinates, and adding their y-coordinates).
 * run the calculations for the delta distance, run DDA algorithm, set the
 * drawing limits, and get the wallx to draw the walls.
 * if the mlx_image_to_window fails we exit the program.
 * 
 * we set the values dt->intpix and dt->intpiy to the integer part of the
 * position of the player, this will be used as the map coordenates.
 */
void	start_drawing(t_dt *dt)
{
	int		x;
	double	camx;

	x = -1;
	if (dt->sc->walls)
	{
		mlx_delete_image(dt->sc->mlx, dt->sc->walls);
		dt->sc->walls = mlx_new_image(dt->sc->mlx, SWIDTH, SHEIGHT);
	}
	while (++x < SWIDTH)
	{
		camx = 2 * x / (double)SWIDTH - 1;
		dt->raydirx = dt->piox + dt->planx * camx;
		dt->raydiry = dt->pioy + dt->plany * camx;
		dt->intpix = (int)dt->pix;
		dt->intpiy = (int)dt->piy;
		delta(dt);
		init_step_sidedist(dt);
		dt->hit = 0;
		run_dda(dt);
		set_drawing_limits(dt);
		get_wallx(dt, x);
	}
	if (mlx_image_to_window(dt->sc->mlx, dt->sc->walls, 0, 0) < 0)
		exit (EXIT_FAILURE);
}
