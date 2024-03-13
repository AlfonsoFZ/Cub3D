/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsandplayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:03:54 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/13 10:20:10 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Get the colour object
 * this function is called by the ft_fill function using a flag to indicate 
 * which colour has to be fullfilled. The value [0] is used to check if it has 
 * been already fullfilled and the next 3 values are the rgb values. 
 * once the colour is set the flag is set to 1 to avoid further changes.
 * error messages are sent if the colour is already set or if a value is 
 * out of range. (valid range 0 - 255). 
 * 
 * @param dt 
 * @param line 
 * @param i 
 * @return int 
 */
int	get_color(t_dt *dt, char *line, int i)
{
	char	**col;
	int		*tmp;

	tmp = NULL;
	if (i == 6)
		tmp = &dt->f[0];
	if (i == 7)
		tmp = &dt->c[0];
	line++;
	line = skip_spaces(line);
	col = ft_split(line, ',');
	if (tmp[0] == 0)
	{
		tmp[0] = 1;
		tmp[1] = ft_atoi(col[0]);
		tmp[2] = ft_atoi(col[1]);
		tmp[3] = ft_atoi(col[2]);
		if ((col && col[3] != 0) || (tmp[1] > 255 || tmp[2] > 255
				|| tmp[3] > 255 || tmp[1] < 0 || tmp[2] < 0 || tmp[3] < 0))
			return (ft_err_msg("", "", "wrong colour", 1));
	}
	else
		return (ft_err_msg("", "", "wrong colour", 1));
	ft_free_char_array(col);
	return (0);
}

/**
 * @brief Set the camera plane tat should be perpendicular to the direction
 * 
 * @param dt 
 * @param c 
 */
void	set_plane(t_dt *dt, char c)
{
	if (c == 'N')
		dt->plany = 0.66;
	else if (c == 'S')
		dt->plany = -0.66;
	else if (c == 'E')
		dt->planx = 0.66;
	else if (c == 'W')
		dt->planx = -0.66;
}

/**
 * @brief Set the player object checking that only one player is set
 * values iniciated with o value as it bring rubbish if not set
 * dt->player inital orientation dt->piox and dt->pioy are set adding 0.5 
 * to the x and y position to place them in the middle of the matrix square.
 * Set the player position in the matrix and the integer part of the position
 * values that will be used in the raycasting process. 
 * @param dt 
 * @param c 
 * @param x 
 * @param y 
 */
void	set_player(t_dt *dt, char c, int x, int y)
{
	if (dt->piox != 0 && dt->pioy != 0)
		exit (ft_err_msg("", "", "wrong map - too many players", 1));
	dt->piox = 0;
	dt->pioy = 0;
	dt->plany = 0;
	dt->planx = 0;
	if (c == 'N')
		dt->piox = -1.5;
	else if (c == 'S')
		dt->piox = 1.5;
	else if (c == 'E')
		dt->pioy = 1.5;
	else if (c == 'W')
		dt->pioy = -1.5;
	set_plane(dt, c);
	dt->pix = (double)x + 0.5;
	dt->piy = (double)y + 0.5;
	dt->intpix = x;
	dt->intpiy = y;
}
