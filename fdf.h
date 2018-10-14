/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:05:58 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 16:58:15 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H

# include <mlx.h>
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# define WINDOW_X 1300
# define WINDOW_Y 1300

typedef struct	s_draw_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_draw_line;

typedef struct	s_strarr_list
{
	struct s_strarr_list	*next;
	char					**s;
}				t_strarr_list;

typedef struct	s_map_point
{
	int		height;
	int		color;
}				t_map_point;

typedef struct	s_map
{
	int				y;
	int				*x;
	t_map_point		**map;
}				t_map;

typedef struct	s_3d_position
{
	int		x;
	int		y;
	int		z;
}				t_3d_position;

typedef struct	s_point
{
	int		x;
	int		y;
	int		color;
}				t_point;

typedef struct	s_view
{
	int			x;
	int			y;
	int			scale;
	int			default_iso;
	int			iso;
	float		rx;
	float		ry;
	float		rz;
	int			cx;
	int			cy;
	int			bpp;
	int			size_line;
	int			endian;
}				t_view;

typedef struct	s_init_win
{
	void		*init;
	void		*win;
	void		*img_ptr;
	char		*img_data;
	t_view		v;
	t_map		*map;
	t_point		**p;
}				t_init_win;

typedef struct	s_brez
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			k;
	int			color;
	t_init_win	*iw;
}				t_brez;

typedef struct	s_make_map
{
	t_map	*m;
	int		i;
	int		j;
	char	**tmp;
	char	*tmp2;
}				t_make_map;

int				get_count_elem(char **s);
int				ft_lstsize(t_strarr_list *lst);
void			ft_add_newstrarr(t_strarr_list **start, char **s);
int				atoi_16(char *s);
void			free_str_map(t_strarr_list **strs);
void			print_brez(t_brez *b, int d, int d1, int d2);
void			brez_line(t_init_win *iw, t_draw_line line, int color);
void			draw_map1(t_init_win *iw, int *x, int i);
void			draw_map(t_init_win *iw, t_point **p, int *x, int y);
void			draw_help(t_init_win *iw);
t_strarr_list	*read_str_map(int fd);
void			get_colnheight(t_make_map *z);
t_map			*make_map(t_strarr_list *strs);
int				point_on_screen(int x, int y);
void			if_need_draw_line(t_init_win *iw, t_draw_line line, int col);
void			update(t_init_win *iw, int *change, int pl);
void			update2(t_init_win *iw, float *change, float pl);
void			get2d(t_3d_position p, t_view *v, int *x, int *y);
void			get_width_height(t_map *m, t_view *v, t_point ***p);
t_point			**get_coordinates(t_map *m, t_view *v);
int				key_hook2(int keycode, t_init_win *iw);
int				key_hook(int keycode, t_init_win *iw);
int				check4err(int argc, char **argv);
void			get_start_iw(t_init_win *iw);
void			pixel_put_img(t_init_win *iw, int x, int y, int color);

#endif
