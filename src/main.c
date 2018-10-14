/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:33:38 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/18 17:01:42 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int		key_hook2(int keycode, t_init_win *iw)
{
	if (keycode == 1)
		update2(iw, &(iw->v.rx), -0.0872665);
	else if (keycode == 14)
		update2(iw, &(iw->v.rz), 0.0872665);
	else if (keycode == 12)
		update2(iw, &(iw->v.rz), -0.0872665);
	else if (keycode == 6)
		update(iw, &(iw->v.scale), 1);
	else if (keycode == 7)
	{
		if (iw->v.scale > 0)
			update(iw, &(iw->v.scale), -1);
	}
	else if (keycode == 8)
		update(iw, &(iw->v.default_iso), 2);
	else if (keycode == 9)
		update(iw, &(iw->v.default_iso), -2);
	return (0);
}

int		key_hook(int keycode, t_init_win *iw)
{
	if (keycode == 53)
	{
		exit(0);
	}
	else if (keycode == 123)
		update(iw, &(iw->v.x), 35);
	else if (keycode == 124)
		update(iw, &(iw->v.x), -35);
	else if (keycode == 126)
		update(iw, &(iw->v.y), 35);
	else if (keycode == 125)
		update(iw, &(iw->v.y), -35);
	else if (keycode == 2)
		update2(iw, &(iw->v.ry), 0.0872665);
	else if (keycode == 0)
		update2(iw, &(iw->v.ry), -0.0872665);
	else if (keycode == 13)
		update2(iw, &(iw->v.rx), 0.0872665);
	else
		return (key_hook2(keycode, iw));
	return (0);
}

int		check4err(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		write(1, "usage: fdf map_name\n", 20);
		return (-1);
	}
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		write(1, "Error\n", 6);
	return (fd);
}

void	get_start_iw(t_init_win *iw)
{
	iw->init = mlx_init();
	iw->win = mlx_new_window(iw->init, WINDOW_X, WINDOW_Y, "fdf");
	iw->v.x = 600;
	iw->v.y = 600;
	iw->v.scale = 20;
	iw->v.default_iso = 20;
	iw->v.rx = 0.523599;
	iw->v.ry = -0.174533;
	iw->v.rz = 0;
	iw->v.iso = iw->v.default_iso * iw->v.scale / 10;
	iw->v.bpp = 8 * sizeof(int);
	iw->v.size_line = WINDOW_X * sizeof(int);
	iw->v.endian = 1;
}

int		main(int argc, char **argv)
{
	t_init_win		iw;
	t_strarr_list	*strs;
	int				fd;

	if ((fd = check4err(argc, argv)) < 0)
		return (0);
	strs = read_str_map(fd);
	close(fd);
	get_start_iw(&iw);
	iw.map = make_map(strs);
	free_str_map(&strs);
	iw.p = get_coordinates(iw.map, &(iw.v));
	iw.img_ptr = mlx_new_image(iw.init, WINDOW_X, WINDOW_Y);
	iw.img_data = mlx_get_data_addr(iw.img_ptr, &(iw.v.bpp),
			&(iw.v.size_line), &(iw.v.endian));
	draw_map(&iw, iw.p, iw.map->x, iw.map->y);
	mlx_put_image_to_window(iw.init, iw.win, iw.img_ptr, 0, 0);
	draw_help(&iw);
	mlx_hook(iw.win, 2, (1L << 0), key_hook, &iw);
	mlx_loop(iw.init);
	return (0);
}
