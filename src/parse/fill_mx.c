/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:13:31 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/12 21:46:09 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Set the matrix width (dt->mw) object.
 * we iterate through the mapfile and count the number of 1's
 * if we found an space we avoid it it is the last space of the line 
 * (before the next \n).
 * we check using flag to gat the maximum width of the map.
 * @param dt 
 */
void	set_dt_mw(t_dt *dt)
{
	int	i;
	int	j;
	int	w;

	i = -1;
	j = 0;
	w = 0;
	while (dt->mapfile[++i])
	{
		if (dt->mapfile[i] == '1')
			w++;
		j++;
		if (dt->mapfile[i] == ' ')
			avoid_if_is_last(dt->mapfile, &i);
		if (dt->mapfile[i] == '\n')
		{
			if (j > dt->mw && w != 0)
				dt->mw = j;
			j = 0;
			w = 0;
		}
	}
}

/**
 * @brief Set the dt matrix height dt->mh object
 * as the mapfile arrive with no empty line at the begining
 * we use flag to detect when a 1 is found and advance untill a \n or \0
 * then we check the flag and if it is 1 we increment the height of the map
 * finally we add 1 to the height to account for the last line and 
 * send an error if the map is too small mh < 3 as no place for the player  
 * @param dt 
 */
void	set_dt_mh(t_dt *dt)
{
	int		i;
	char	*tmp;
	char	wall;

	i = 0;
	tmp = &(dt->mapfile[i]);
	while (*tmp != '\0')
	{
		wall = '0';
		if (*tmp == '1')
		{
			wall = '1';
			while (*tmp != '\n' && *tmp != '\0')
				tmp++;
		}
		else
			tmp++;
		if (wall == '1')
			dt->mh++;
	}
	dt->mh++;
	if (dt->mh < 3)
		exit (ft_err_msg("", "", "Invalid map", 1));
}

/**
 * @brief allocates the memory for each char * of the matrix
 * it asign the value of the mapfile to the matrix and fill each line
 * avoiding the spaces that are at the end of each line but filling 
 * with spaces until the maximum width of the map is reached
 * and adding a NULL value to the last row.
 * 
 * params like the k has been passed from other function to follow the norm
 * maybe it cab be declared here and initialized to 0.
 * @param dt 
 * @param j 
 * @param i 
 * @param k 
 */
void	fill_mx_line(t_dt *dt, int *j, int *i, int *k)
{
	dt->rmap[*j] = (char *)malloc(sizeof(char) * (dt->mw) + 1);
	while (dt->mapfile && dt->mapfile[*i] != '\n'
		&& dt->mapfile[*i] != '\0' && *k < dt->mw - 1)
	{
		dt->rmap[*j][*k] = dt->mapfile[*i];
		(*i)++;
		(*k)++;
	}
	if (dt->mapfile[*i] == ' ')
		avoid_if_is_last(dt->mapfile, i);
	if (*k < dt->mw)
	{
		while (*k < dt->mw -1)
		{
			dt->rmap[*j][*k] = ' ';
			(*k)++;
		}
	}
	dt->rmap[*j][*k] = '\0';
	*k = 0;
	(*i)++;
}

/**
 * @brief check that no valid chars are present before the map starts
 * allocate memory for the lines and launch the fill function 
 * to complete the matrix adding a NULL value to the last row.
 * 
 * @param dt 
 */
void	fill_mx(t_dt *dt)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	k = 0;
	while (dt->mapfile[i] != '1')
	{
		if (dt->mapfile[i] != ' ' && dt->mapfile[i] != '\n')
			ft_err_msg("", "", "Invalid map", 1);
		i++;
	}
	i = 0;
	dt->rmap = (char **)ft_calloc(sizeof(char *), (dt->mh));
	while (++j < dt->mh - 1)
		fill_mx_line(dt, &j, &i, &k);
	dt->rmap[j] = NULL;
}

/**
 * @brief clean the map string and set the map height and width
 * fullfill the matrix with the map and check the borders
 * @param dt 
 * @return char** 
 */
char	**change_to_mx(t_dt *dt)
{
	ft_clean_mapstr(dt);
	set_dt_mh(dt);
	set_dt_mw(dt);
	fill_mx(dt);
	check_border(dt);
	return (NULL);
}
