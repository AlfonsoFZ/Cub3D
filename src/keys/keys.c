/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:47:52 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/14 12:38:45 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief plane and direction are rotated by the value using the formula:
 * 
 * To rotate a vector, multiply it with the rotation matrix

	[ cos(a) -sin(a) ]
	[ sin(a)  cos(a) ]
 * @param dt 
 * @param vel 
 */
static void	rotate(t_dt	*dt, double vel)
{
	double		olddirx;
	double		oldplanex;

	olddirx = dt->piox;
	oldplanex = dt->planx;
	dt->piox = dt->piox * cos(vel) - dt->pioy * sin(vel);
	dt->pioy = olddirx * sin(vel) + dt->pioy * cos(vel);
	dt->planx = dt->planx * cos(vel) - dt->plany * sin(vel);
	dt->plany = oldplanex * sin(vel) + dt->plany * cos(vel);
}

/**
 * @brief we have to check if the next cell is not a wall before moving
 * we use the planx and plany to move the player form one side to other
 * 
 * @param dt 
 * @param vel 
 */
static void	side_move(t_dt *dt, double vel)
{
	if (dt->rmap[(int)(dt->pix + dt->planx * vel)][(int)dt->piy] != '1')
		dt->pix += dt->planx * vel;
	if (dt->rmap[(int)dt->pix][(int)(dt->piy + dt->plany * vel)] != '1')
		dt->piy += dt->plany * vel;
}

/**
 * @brief althought it is called vertical move, it is really a moving forward
 * or backward funtion, as it use the directions of the player to move. 
 * 
 * @param dt 
 * @param vel 
 */
static void	vertical_move(t_dt *dt, double vel)
{
	if (dt->rmap[(int)(dt->pix + dt->piox * vel)][(int)dt->piy] != '1')
		dt->pix += dt->piox * vel;
	if (dt->rmap[(int)dt->pix][(int)(dt->piy + dt->pioy * vel)] != '1')
		dt->piy += dt->pioy * vel;
}

/**
 * @brief this function is used to control the keys events.
 * this is called from the hook function in the ft_startthegame funtion.
 * and exit if the escape key is pressed, closing the window and freeing
 * the allocated memory. It need to be confirmed if the memory is freed 
 * properly or if it is necessary to do it. 
 * 
 * The speed modifiers are used to determinate the speed and direction
 * of the moving and rotating of the input keys
 * @param param 
 */
void	keys(void *param)
{
	t_dt	*dt;

	dt = param;
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(dt->sc->mlx);
		ft_free_dt(dt);
	}
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_LEFT))
		rotate(dt, R_VEL);
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_RIGHT))
		rotate(dt, -R_VEL);
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_D))
		side_move(dt, M_VEL);
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_A))
		side_move(dt, -M_VEL);
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_W))
		vertical_move(dt, M_VEL);
	if (mlx_is_key_down(dt->sc->mlx, MLX_KEY_S))
		vertical_move(dt, -M_VEL);
	start_drawing(dt);
}
