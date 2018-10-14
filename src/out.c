/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:35:01 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 17:02:09 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_brez(t_brez *b, int d, int d1, int d2)
{
	int i;

	if (b->k <= 0)
		b->dx = b->dy;
	i = 0;
	while (++i <= b->dx)
	{
		if (d > 0)
		{
			d += d2;
			b->y += b->sy;
		}
		else
			d += d1;
		if (b->k > 0)
			pixel_put_img(b->iw, b->x, b->y, b->color);
		else
			pixel_put_img(b->iw, b->y, b->x, b->color);
		b->x += b->sx;
	}
}

void	brez_line(t_init_win *iw, t_draw_line line, int color)
{
	t_brez	b;

	pixel_put_img(iw, line.x0, line.y0, color);
	b.iw = iw;
	b.color = color;
	b.sx = (line.x1 >= line.x0) ? (1) : (-1);
	b.sy = (line.y1 >= line.y0) ? (1) : (-1);
	b.dx = (line.x1 > line.x0) ? (line.x1 - line.x0) : (line.x0 - line.x1);
	b.dy = (line.y1 > line.y0) ? (line.y1 - line.y0) : (line.y0 - line.y1);
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		b.x = line.x0 + b.sx;
		b.y = line.y0;
		b.k = 1;
		print_brez(&b, (b.dy * 2) - b.dx, b.dy * 2, (b.dy - b.dx) * 2);
	}
	else
	{
		b.x = line.y0 + b.sy;
		b.y = line.x0;
		b.sy = (line.x1 >= line.x0) ? (1) : (-1);
		b.sx = (line.y1 >= line.y0) ? (1) : (-1);
		b.k = 0;
		print_brez(&b, (b.dx * 2) - b.dy, b.dx * 2, (b.dx - b.dy) * 2);
	}
}

void	draw_map1(t_init_win *iw, int *x, int i)
{
	t_draw_line	line;
	int			j;

	line.x0 = iw->p[i][0].x;
	line.y0 = iw->p[i][0].y;
	j = 0;
	while (++j < x[i])
	{
		line.x1 = iw->p[i][j].x;
		line.y1 = iw->p[i][j].y;
		if_need_draw_line(iw, line, (iw->p[i][j - 1].color / 2
					+ iw->p[i][j].color / 2));
		line.x0 = line.x1;
		line.y0 = line.y1;
		if (j < x[i + 1])
		{
			line.x1 = iw->p[i + 1][j].x;
			line.y1 = iw->p[i + 1][j].y;
			if_need_draw_line(iw, line, (iw->p[i][j].color / 2
						+ iw->p[i + 1][j].color / 2));
		}
	}
}

void	draw_map(t_init_win *iw, t_point **p, int *x, int y)
{
	t_draw_line	line;
	int			i;
	int			j;

	i = -1;
	while (++i < y - 1)
	{
		line.x0 = p[i][0].x;
		line.y0 = p[i][0].y;
		line.x1 = p[i + 1][0].x;
		line.y1 = p[i + 1][0].y;
		if_need_draw_line(iw, line, p[i][0].color / 2 + p[i + 1][0].color / 2);
		draw_map1(iw, x, i);
	}
	line.x0 = p[i][0].x;
	line.y0 = p[i][0].y;
	j = 0;
	while (++j < x[i])
	{
		line.x1 = p[i][j].x;
		line.y1 = p[i][j].y;
		if_need_draw_line(iw, line, p[i][j - 1].color / 2 + p[i][j].color / 2);
		line.x0 = line.x1;
		line.y0 = line.y1;
	}
}

void	draw_help(t_init_win *iw)
{
	int		x;
	int		y;

	x = WINDOW_X - 500;
	y = 1;
	mlx_string_put(iw->init, iw->win, x, (y++ * 20), 0xFFFFFF,
			"Use arrows to move left, right, up and down");
	mlx_string_put(iw->init, iw->win, x, (y++ * 20), 0xFFFFFF,
			"Use A, D, W, S, Q, E to rotate model");
	mlx_string_put(iw->init, iw->win, x, (y++ * 20), 0xFFFFFF,
			"Use Z, X to increase and decrease model");
	mlx_string_put(iw->init, iw->win, x, (y++ * 20), 0xFFFFFF,
			"Use C, V to increase and decrease height factor");
}
