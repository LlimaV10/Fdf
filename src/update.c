/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:31:54 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 16:14:13 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	update(t_init_win *iw, int *change, int pl)
{
	int		i;

	if (change != 0)
		*change += pl;
	iw->v.iso = iw->v.default_iso * iw->v.scale / 10;
	mlx_clear_window(iw->init, iw->win);
	i = -1;
	while (++i < iw->map->y)
		free(iw->p[i]);
	free(iw->p);
	iw->p = get_coordinates(iw->map, &(iw->v));
	mlx_destroy_image(iw->init, iw->img_ptr);
	iw->img_ptr = mlx_new_image(iw->init, WINDOW_X, WINDOW_Y);
	iw->img_data = mlx_get_data_addr(iw->img_ptr, &(iw->v.bpp),
			&(iw->v.size_line), &(iw->v.endian));
	draw_map(iw, iw->p, iw->map->x, iw->map->y);
	mlx_put_image_to_window(iw->init, iw->win, iw->img_ptr, 0, 0);
	draw_help(iw);
}

void	update2(t_init_win *iw, float *change, float pl)
{
	int		i;

	if (change != 0)
		*change += pl;
	iw->v.iso = iw->v.default_iso * iw->v.scale / 10;
	mlx_clear_window(iw->init, iw->win);
	i = -1;
	while (++i < iw->map->y)
		free(iw->p[i]);
	free(iw->p);
	iw->p = get_coordinates(iw->map, &(iw->v));
	mlx_destroy_image(iw->init, iw->img_ptr);
	iw->img_ptr = mlx_new_image(iw->init, WINDOW_X, WINDOW_Y);
	iw->img_data = mlx_get_data_addr(iw->img_ptr, &(iw->v.bpp),
			&(iw->v.size_line), &(iw->v.endian));
	draw_map(iw, iw->p, iw->map->x, iw->map->y);
	mlx_put_image_to_window(iw->init, iw->win, iw->img_ptr, 0, 0);
	draw_help(iw);
}

void	get2d(t_3d_position p, t_view *v, int *x, int *y)
{
	int		x0;
	int		y0;

	y0 = p.y * cos(v->rx) + p.z * sin(v->rx);
	p.z = p.z * cos(v->rx) - p.y * sin(v->rx);
	x0 = p.x * cos(v->ry) - p.z * sin(v->ry);
	*x = x0 * cos(v->rz) + y0 * sin(v->rz) + v->cx;
	*y = y0 * cos(v->rz) - x0 * sin(v->rz) + v->cy;
}

void	get_width_height(t_map *m, t_view *v, t_point ***p)
{
	t_3d_position	p3d;

	v->cx = v->x;
	v->cy = v->y;
	p3d.x = m->x[m->y / 2] / 2 * v->scale;
	p3d.y = m->y / 2 * v->scale;
	p3d.z = 0;
	get2d(p3d, v, &(v->cx), &(v->cy));
	v->cx = 2 * v->x - v->cx;
	v->cy = 2 * v->y - v->cy;
	*p = (t_point **)malloc(m->y * sizeof(t_point *));
}

t_point	**get_coordinates(t_map *m, t_view *v)
{
	t_3d_position	p3d;
	t_point			**p;
	int				i;
	int				j;

	get_width_height(m, v, &p);
	i = -1;
	while (++i < m->y)
	{
		p[i] = (t_point *)malloc(m->x[i] * sizeof(t_point));
		p3d.x = 0;
		p3d.y = i * v->scale;
		p3d.z = -m->map[i][0].height * v->iso / 10;
		p[i][0].color = m->map[i][0].color;
		get2d(p3d, v, &(p[i][0].x), &(p[i][0].y));
		j = 0;
		while (++j < m->x[i])
		{
			p3d.x += v->scale;
			p3d.z = -m->map[i][j].height * v->iso / 10;
			p[i][j].color = m->map[i][j].color;
			get2d(p3d, v, &(p[i][j].x), &(p[i][j].y));
		}
	}
	return (p);
}
