/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:42:34 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 16:40:24 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	pixel_put_img(t_init_win *iw, int x, int y, int color)
{
	int		*tmp;

	if (point_on_screen(x, y) == 0)
		return ;
	tmp = (int *)iw->img_data;
	tmp += x + WINDOW_X * y;
	*tmp = color;
}
