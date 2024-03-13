/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:02:18 by alfofern          #+#    #+#             */
/*   Updated: 2024/02/12 19:22:44 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief an instance of the data-screen dt->sc is created and allocated to 
 * avoid stack smashing. In this structure we will save all the values related
 * to the graphic side of the game.
 * it opens the 4 textures and check if they are valid 
 * 
 * @param dt 
 */
void	ft_check_txturs(t_dt *dt)
{
	int	i;

	dt->sc = ft_calloc(sizeof(t_sc), 1);
	dt->sc->txtur[0] = mlx_load_png(dt->no);
	dt->sc->txtur[1] = mlx_load_png(dt->so);
	dt->sc->txtur[2] = mlx_load_png(dt->we);
	dt->sc->txtur[3] = mlx_load_png(dt->ea);
	i = -1;
	while (++i < 4)
	{
		if (!dt->sc->txtur[i])
		{
			ft_err_msg("", "", INVALID_TEXTURE, 1);
			exit (1);
		}
	}
}
