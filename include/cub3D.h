/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:06:51 by alfofern          #+#    #+#             */
/*   Updated: 2024/03/07 10:19:17 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# define WRONG_ARG "Please include a \".cub map\" after the programm name."
# define W_RONGCHARPOR "Invalid or missing field or wrong map position"
# define EXT_ACCESS "inaccessible file."
# define OPEN_ERR "The map cannot be opened."
# define CHANGE_TABS "Tabs in map section, replace with spaces and try again."
# define MAP_BORDER "The map is not valid, borders aren't closed."
# define INVALID_CHAR "invalid characters in map found."
# define INVALID_NITEMS "Wrong ammount of players."
# define INVALID_TEXTURE "Wrong texture."
# define SWIDTH 1920
# define SHEIGHT 1024
# define R_VEL	0.05
# define M_VEL	0.1

/* in Linux (at least in my case)
# define R_VEL	0.05
# define M_VEL	0.1
*/

typedef struct sc
{
	mlx_t			*mlx;
	mlx_image_t		*main_img;
	mlx_image_t		*walls;
	struct s_dt		*dt;
	mlx_texture_t	*txtur[4];
	int				txtur_x;
}	t_sc;

/**
 * pix, piy - player posisiton (double)
 * piox, pioy - player orientation (double)
 * intpix, intpiy - map position (int)
 * planx, plany - camera plane (double)
 * raydirx, raydiry - ray direction (double)
 */
typedef struct s_dt
{
	char		*mapfile;
	int			mapfd;
	char		**rmap;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f[4];
	int			c[4];
	int			mw;
	int			mh;
	double		pix;
	int			intpix;
	double		piy;
	int			intpiy;
	double		piox;
	double		pioy;
	double		planx;
	double		plany;
	double		raydirx;
	double		raydiry;
	double		sd_dist_x;
	double		sd_dist_y;
	double		delta_x;
	double		delta_y;
	double		perp_wll_dist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			ln_hght;
	int			draw_st;
	int			draw_end;
	int			i;
	t_sc		*sc;
}	t_dt;

/*utils/ft_strcmp.c*/
int		ft_strcmp(char *s1, char *s2);
/*parse/checkmap.c*/
void	ft_check_mapfile(t_dt *dt, char *map);
/*parse/read_and_fill.c*/
void	ft_read(t_dt *dt);
int		ft_fill(t_dt *dt, char *line, int i);
int		check_line(t_dt *dt, char *line);
int		ft_getmap(t_dt *dt);
void	ft_read(t_dt *dt);

/*free/free.c*/
void	ft_free_dt(t_dt *dt);
void	ft_free_char_array(char **pointer);

/*utils/utils.c*/
int		ft_err_msg(char *str1, char *str2, char *str3, int ernb);

// char	*ft_strjoinandfree(char *s1, char *s2, t_dt *dt);
char	*ft_free_join(char *s1, char *s2, int strtofree);
void	ft_print_matrix(char **matrix);
char	*skip_spaces(char *str);
int		avoid_if_is_last(char *s, int *i);

/*src/parse/fill_mx.c*/
void	fill_mx_line(t_dt *dt, int *j, int *i, int *k);
void	fill_mx(t_dt *dt);
char	**change_to_mx(t_dt *dt);
void	set_dt_mw(t_dt *dt);
void	set_dt_mh(t_dt *dt);

/*src/parse/checkmapcontent.c*/
int		checkmap(t_dt *dt);
int		check_char_and_lines(t_dt *dt);
int		is_valid_char(char c);

/*src/parse/colorsandplayer.c*/
int		get_color(t_dt *dt, char *line, int i);
void	set_player(t_dt *dt, char c, int x, int y);

/*src/parse/fill_mx_utils.c*/
char	*ft_clean_mapstr(t_dt *dt);
void	check_border(t_dt *dt);

/*src/parse/checktextures.c*/
void	ft_check_txturs(t_dt *dt);

/*/src/drawings/startdrawing.c*/
void	ft_startthegame(t_dt *dt);
void	start_drawing(t_dt *dt);
void	draw_walls(t_dt *dt);

/*src/drawings/drawing_numbers.c*/
void	delta(t_dt *dt);
void	init_step_sidedist(t_dt *dt);
void	run_dda(t_dt *dt);
void	set_drawing_limits(t_dt *dt);

/*src/keys/keys.c*/
void	keys(void *param);

/*initscreen*/
void	ft_drawbackground(t_dt *dt);

#endif
