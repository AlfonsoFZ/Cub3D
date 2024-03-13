/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:53:51 by imoro-sa          #+#    #+#             */
/*   Updated: 2024/03/07 11:36:25 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
/* to check leaks
uncomment this function and include this into the main function:
	atexit(leaks);
	or run the command as: leaks --atExit-- ./cub3D Maps/bath.cub
 */
// void	leaks(void)
// {
// 	system("leaks -q cub3D");
// }

/**
 * @brief A new dt structure is declared here
 * if we have one argument, the program continues, set to 0 the dt memory area 
 * launch the check the map file,run the game, with the loop function makes
 * the screen to remain visible, with terminate it will terminate the screen 
 * instance and all the related allocated memory will be freed and with 
 * ft_free_dt, we free the rest of the allocated memory of the structure
 * if we have none or more than one argument we show an error and exit with
 * a failure value  
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_dt	dt;

	if (argc == 2)
	{
		ft_memset(&dt, 0, sizeof(t_dt));
		ft_check_mapfile(&dt, argv[1]);
		ft_startthegame(&dt);
		mlx_loop(dt.sc->mlx);
		mlx_terminate(dt.sc->mlx);
		ft_free_dt(&dt);
		return (EXIT_SUCCESS);
	}
	ft_err_msg("", "", WRONG_ARG, 1);
	return (EXIT_FAILURE);
}
