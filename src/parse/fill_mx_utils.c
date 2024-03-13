/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:52:38 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/20 19:04:51 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief removes the empty line at the begining of the map
 * return a substring of the mapfile freeing the previous mapfile
 * @param dt 
 * @return char* 
 */
char	*ft_clean_mapstr(t_dt *dt)
{
	char	*clean;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(dt->mapfile);
	while (dt->mapfile[i] != '1')
	{
		if (dt->mapfile[i] != '1' && dt->mapfile[i]
			!= '\n' && dt->mapfile[i] != '\0' && dt->mapfile[i] != ' ')
			exit (ft_err_msg("", "", "Invalid map", 1));
		i++;
	}
	if (i == 0)
		return (dt->mapfile);
	while (i > 1 && dt->mapfile[i - (j + 1)] == ' ')
		j++;
	clean = ft_substr(dt->mapfile, i - j, len - (i - j) + 1);
	free(dt->mapfile);
	dt->mapfile = clean;
	return (clean);
}

/**
 * @brief checks the borders of the map and the presence of the player
 * first of all check the borders of the matrix to check that none of the 
 * following char are present:"02NSWE". This will let us to check 
 * that the surrounding values of a char with a value from this group is 
 * not a space.
 * if the border is correct, we will check the presence of the player
 *   
 * @param dt 
 */
void	check_border(t_dt *dt)
{
	int	i;
	int	j;

	j = -1;
	while (++j < dt->mh -1)
	{
		i = -1;
		while (++i < dt->mw - 1)
		{
			if (ft_strchr("02NSWE", dt->rmap[0][i])
				|| ft_strchr("02NSWE", dt->rmap[dt->mh - 2][i])
				|| ft_strchr("02NSWE", dt->rmap[j][0])
				|| ft_strchr("02NSWE", dt->rmap[j][dt->mw - 2])
				|| ((ft_strchr("02NSWE", dt->rmap[j][i]))
				&& (dt->rmap[j][i - 1] == ' ' || dt->rmap[j][i + 1] == ' '
				|| dt->rmap[j - 1][i - 1] == ' '
				|| dt->rmap[j + 1][i + 1] == ' '
				|| dt->rmap[j - 1][i] == ' ' || dt->rmap[j + 1][i] == ' '
				|| dt->rmap[j - 1][i + 1] == ' '
				|| dt->rmap[j + 1][i - 1] == ' ')))
				exit (ft_err_msg("", "", "Wrong borders??", 1));
			if (ft_strchr("NSWE", dt->rmap[j][i]))
				set_player(dt, dt->rmap[j][i], j, i);
		}
	}
}
