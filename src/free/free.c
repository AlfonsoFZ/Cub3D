/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:43:09 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/14 12:37:04 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_free_char_array(char **pointer)
{
	int	i;

	i = 0;
	while (pointer && pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

/**
 * @brief free all the memory allocated for the dt structure after all
 * if an error occurs.
 * 
 * Memory allocated for graphic purposes are freed when the screen or img 
 * instances are terminated or while exit.
 * 
 * @param dt 
 */
void	ft_free_dt(t_dt *dt)
{
	if (dt->mapfd != -1)
		close(dt->mapfd);
	if (dt->mapfile && dt->mapfile[0])
	{
		free(dt->no);
		free(dt->so);
		free(dt->we);
		free(dt->ea);
		free(dt->mapfile);
		ft_free_char_array(dt->rmap);
	}
	exit (EXIT_SUCCESS);
}
