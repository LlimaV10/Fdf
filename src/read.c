/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:29:10 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 16:45:43 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_strarr_list	*read_str_map(int fd)
{
	t_strarr_list	*strs;
	char			*s;
	char			**now;

	strs = 0;
	while (get_next_line(fd, &s) > 0)
	{
		now = ft_strsplit(s, ' ');
		free(s);
		ft_add_newstrarr(&strs, now);
	}
	free(s);
	return (strs);
}

void			get_colnheight(t_make_map *z)
{
	if ((!ft_isdigit(**((*z).tmp))) && (**((*z).tmp) != '-')
			&& (**((*z).tmp) != '+'))
	{
		write(1, "Error\n", 6);
		exit(0);
	}
	if (((*z).tmp2 = ft_strchr(*((*z).tmp), ',')) != 0)
		(*z).m->map[(*z).i][(*z).j].color = atoi_16((*z).tmp2 + 1);
	else
		(*z).m->map[(*z).i][(*z).j].color = 0xFFFF50;
	(*z).m->map[(*z).i][(*z).j].height = ft_atoi(*((*z).tmp++));
}

t_map			*make_map(t_strarr_list *strs)
{
	t_make_map	z;

	z.m = (t_map *)malloc(sizeof(t_map));
	z.m->y = ft_lstsize(strs);
	z.m->map = (t_map_point **)malloc(z.m->y * sizeof(t_map_point *));
	z.m->x = (int *)malloc(z.m->y * sizeof(int));
	z.i = z.m->y;
	while (--z.i >= 0)
	{
		z.m->x[z.i] = get_count_elem(strs->s);
		z.m->map[z.i] = (t_map_point *)malloc(z.m->x[z.i]
				* sizeof(t_map_point));
		z.j = -1;
		z.tmp = (strs->s);
		while (++z.j < z.m->x[z.i])
			get_colnheight(&z);
		strs = strs->next;
	}
	return (z.m);
}

int				point_on_screen(int x, int y)
{
	if ((x <= 0 || x >= WINDOW_X) || (y <= 0 || y >= WINDOW_Y))
		return (0);
	return (1);
}

void			if_need_draw_line(t_init_win *iw, t_draw_line line, int col)
{
	if ((point_on_screen(line.x0, line.y0) == 0)
			&& (point_on_screen(line.x1, line.y1) == 0))
		return ;
	brez_line(iw, line, col);
}
