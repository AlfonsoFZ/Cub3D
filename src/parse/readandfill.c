/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readandfill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:27:04 by alfofern          #+#    #+#             */
/*   Updated: 2024/03/06 15:19:16 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Get the value objectyhis funtion save in a char * the value of the
 * caracters after the spaces after every key word removing the ending "\n"
 * 
 * @param line 
 * @return char* 
 */
char	*get_value(char *line)
{
	char	*tmp;

	tmp = NULL;
	line += 2;
	line = skip_spaces(line);
	tmp = ft_strtrim(line, "\t \n");
	return (tmp);
}

/**
 * @brief save the char *value of the texture paths in the data structure
 * using the get_value function.
 * it can be replaced by a single function that open the textures directly,
 * but it would need more changes as some of the conditional statements use 
 * this info to modify the behaviour of the code. i leave it as it is for now
 * it also launches the get color function to fill the color fields
 * @param dt 
 * @param line 
 * @param i 
 * @return int 
 */
int	ft_fill(t_dt *dt, char *line, int i)
{
	if (i == 1 && !dt->no)
		return (dt->no = get_value(line), 0);
	else if (i == 2 && !dt->so)
		return (dt->so = get_value(line), 0);
	else if (i == 3 && !dt->we)
		return (dt->we = get_value(line), 0);
	else if (i == 4 && !dt->ea)
		return (dt->ea = get_value(line), 0);
	else if (i == 6 && dt->f[0] == 0)
		return (get_color(dt, line, i));
	else if (i == 7 && dt->c[0] == 0)
		return (get_color(dt, line, i));
	return (1);
}

/**
 * @brief it compare the first word of the line and fill the mandatory fields
 *  * 
 * @param dt 
 * @param line 
 * @return int 
 */
int	check_line(t_dt *dt, char *line)
{
	(void)dt;
	if (!ft_strncmp(line, "NO ", 3))
		return (ft_fill(dt, line, 1));
	else if (!ft_strncmp(line, "SO ", 3))
		return (ft_fill(dt, line, 2));
	else if (!ft_strncmp(line, "WE ", 3))
		return (ft_fill(dt, line, 3));
	else if (!ft_strncmp(line, "EA ", 3))
		return (ft_fill(dt, line, 4));
	else if (!ft_strncmp(line, "F ", 2))
		return (ft_fill(dt, line, 6));
	else if (!ft_strncmp(line, "C ", 2))
		return (ft_fill(dt, line, 7));
	else if (line[0] == '\n')
		return (0);
	return (0);
}

/**
 * @brief this funtion will read the map file using get_next_line and save it
 * the while loop stops when the line is 0, that means that the file has ended
 * we use the same field used for the map file to save the map in a char *
 * @param dt 
 * @return int 
 */
int	ft_getmap(t_dt *dt)
{
	char	*line;
	char	*read;

	line = "";
	read = ft_strdup("");
	while (1 && line != 0)
	{
		line = get_next_line(dt->mapfd);
		if (line == 0)
			break ;
		read = ft_free_join(read, line, 3);
	}
	free(dt->mapfile);
	dt->mapfile = read;
	checkmap(dt);
	return (0);
}

/**
 * @brief it will read using get_next_line, the filename untill 
 * all the mandatory fields have been fullfilled. N,S, E, W F and C
 * avoid the spaces before the first non empty caracter,
 * check if the sentence start with a valid caracter that should be 
 * one of NSWEFC\n" and checkline return 1. That would mean that start with a
 * valid character but the line is not correct, an error will be shown during
 * the check, so no error is shown while exiting. 
 * if the first character is not valid, we show an error and exit.
 * if everyting is ok, we launch che check textures and get map function 
 * before closing the map file
 * @param dt 
 */
void	ft_read(t_dt *dt)
{
	char	*line;
	char	*tmpline;

	line = "";
	while (1 && (!dt->no || !dt->so || !dt->we || !dt->ea
			|| dt->f[0] == 0 || dt->c[0] == 0))
	{
		line = get_next_line(dt->mapfd);
		if (line == 0)
			break ;
		tmpline = line;
		tmpline = skip_spaces(tmpline);
		if (ft_strchr("NSWEFC\n", *tmpline) && check_line(dt, tmpline))
			exit (1);
		else if (!ft_strchr("NSWEFC\n", *tmpline))
			exit (ft_err_msg("", "", W_RONGCHARPOR, 1));
		free(line);
	}
	ft_check_txturs(dt);
	ft_getmap(dt);
	close(dt->mapfd);
}
