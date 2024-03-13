/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:00:58 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/12 12:16:19 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief this function use the lenth of ".cub" to check if we have enough 
 * caracteres in the filename char * to compare the last caracters of the 
 * filename with the string ".cub". It will return 1 if they don't match.
 * 
 * @param filename 
 * @param ext 
 * @return int 
 */
int	ft_checkext(char *filename, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(filename);
	j = ft_strlen(ext);
	if (i < 5)
		return (1);
	while (j > 0)
		if (filename[--i] != ext[--j])
			return (1);
	return (0);
}

/**
 * @brief check the string that should be the file name.
 * if no map is received. It should not happend as it has a condition before.
 * with a temporary char * we get the trimmed value of argv[1] 
 * check the .cub extension and if it is not a .cub or we cannot access it
 * it frees the trimmed char*,* show an error and exit the program.
 * if it is ok we return the char *.
 * @param map 
 * @return char* 
 */
char	*ft_checkfile(char *map)
{
	char	*filename;

	if (!map)
	{
		ft_err_msg("", "", WRONG_ARG, 1);
		exit (1);
	}
	filename = ft_strtrim(map, " ");
	if (ft_checkext(filename, ".cub"))
	{
		free(filename);
		ft_err_msg("", "", WRONG_ARG, 1);
		exit (1);
	}
	else if (access(filename, R_OK) == -1)
	{
		free(filename);
		ft_err_msg("", "", EXT_ACCESS, 2);
		exit(2);
	}
	return (filename);
}

/**
 * @brief check if the argv[1] is a valid mapfile
 * 
 * launch the checkfile(map) function to get the name of the file 
 * open the file received and show and error if cannot be opened
 * or launch the read function if it has benn opened correctly
 * @param dt 
 * @param map 
 */
void	ft_check_mapfile(t_dt *dt, char *map)
{
	dt->mapfile = ft_checkfile(map);
	dt->mapfd = open(dt->mapfile, O_RDONLY);
	if (dt->mapfd == -1)
		ft_err_msg("", "", OPEN_ERR, 3);
	else
		ft_read(dt);
}
