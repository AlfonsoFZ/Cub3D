/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:44:08 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/13 10:26:52 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Get the rgba object leaving the alpha value to 255
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 * @return int 
 */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief with the function put_pixel and iterating through the screen
 * wi filled the top half of the screen with the ceiling colour and the bottom
 * half with the floor colour.
 * 
 * colours are set in the ft_fill function and are stored in the dt struct.
 * we use the last 3 values to get the rgb values and convert them into an int
 * @param dt 
 */
void	ft_drawbackground(t_dt *dt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SHEIGHT)
	{
		j = -1;
		while (++j < SWIDTH)
		{
			if (i < SHEIGHT / 2)
				mlx_put_pixel(dt->sc->main_img, j, i,
					get_rgba(dt->c[1], dt->c[2], dt->c[3], 255));
			else
				mlx_put_pixel(dt->sc->main_img, j, i,
					get_rgba(dt->f[1], dt->f[2], dt->f[3], 255));
		}
	}
}

/**
 * @brief Set the main screen object using false to restrict the window from
 * being resizable. 
 * set the main images wherethe background floor and ceiling will be drawn.
 * set the wall image where the walls will be drawn.
 * @param dt 
 */
void	set_main_screen(t_dt *dt)
{
	dt->sc->mlx = mlx_init(SWIDTH, SHEIGHT, "Cub3D", false);
	if (!dt->sc->mlx)
		exit (ft_err_msg("", "", "mlx_init failed", 1));
	dt->sc->main_img = mlx_new_image(dt->sc->mlx, SWIDTH, SHEIGHT);
	if (!dt->sc->main_img)
		exit (ft_err_msg("", "", "mlx_init failed", 1));
	mlx_image_to_window(dt->sc->mlx, dt->sc->main_img, 0, 0);
	ft_drawbackground(dt);
	dt->sc->walls = mlx_new_image(dt->sc->mlx, SWIDTH, SHEIGHT);
	if (!dt->sc->walls)
		exit (ft_err_msg("", "", "mlx_init failed", 1));
	if (mlx_image_to_window(dt->sc->mlx, dt->sc->walls, 0, 0) < 0)
		exit(EXIT_FAILURE);
}

/**
 * @brief run the screen, graphics and key hooks
 * 
 * @param dt 
 */
void	ft_startthegame(t_dt *dt)
{
	set_main_screen(dt);
	start_drawing(dt);
	mlx_loop_hook(dt->sc->mlx, &keys, dt);
}
