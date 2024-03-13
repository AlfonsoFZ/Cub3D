/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmapcontent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:51:29 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/12 19:50:02 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief checks the valid char for the map and detects if tabs are detected
 * return 0 if is a valid char
 * @param c 
 * @return int 
 */
int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (c);
	else if (c == ' ')
		return (c);
	else if (c == '\n')
		return (c);
	else if (c == '\t')
	{
		ft_err_msg("", "", CHANGE_TABS, 1);
		exit (1);
	}
	return (0);
}

/**
 * @brief using flag to indicate whe a map has begun and when it has ended.
 * this flags are used to check if we have empty lines within the map and 
 * to ensure that the map is not empty.
 * @param dt 
 * @return int 
 */
int	check_char_and_lines(t_dt *dt)
{
	size_t	i;
	int		map_start;
	int		map_end;

	map_start = 0;
	map_end = 0;
	i = 0;
	while (dt->mapfile[i] != '\0')
	{
		if (!is_valid_char(dt->mapfile[i]))
			exit (ft_err_msg("", "", "wrong map", 1));
		else if (dt->mapfile[i] == '0' || dt->mapfile[i] == '1')
		{
			map_start = 1;
			if (map_end == 1)
				exit (ft_err_msg("", "", "wrong map", 1));
		}
		else if (dt->mapfile[i] == '\n' && dt->mapfile[i + 1] == '\n')
			map_end = map_start | map_end;
		i++;
	}
	if (map_start == 0)
		exit (ft_err_msg("", "", "Empty map", 1));
	return (0);
}

/**
 * @brief check if the values of the map are correct and we can create
 * a valid matrix, first of all we check all the characters and the lines
 * and then we change the map to a matrix and check that we have found a 
 * proper player
 * 
 * @param dt 
 * @return int 
 */
int	checkmap(t_dt *dt)
{
	check_char_and_lines(dt);
	change_to_mx(dt);
	if (!dt->piox && !dt->pioy)
		exit (ft_err_msg("", "", "Player not found", 1));
	return (0);
}
