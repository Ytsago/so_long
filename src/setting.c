/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:01:12 by secros            #+#    #+#             */
/*   Updated: 2025/01/20 13:32:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	set_input(int key, t_data *data)
{
	erease_cursor(data->load, data->w_size[0], data->w_size[1]);
	if (key == W_KEY)
		if (data->w_size[1] > 66)
			data->w_size[1] -= 100;
	if (key == S_KEY)
		if (data->w_size[1] < 366)
			data->w_size[1] += 100;
	draw_cursor(data->load, data->w_size[0], data->w_size[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->load->img, 0, 0);
	if (key == ENTER)
	{
		data->set = data->w_size[1] / 100;
		mlx_destroy_image(data->mlx, data->load->img);
		loading_screen(data, data->load);
	}
	if (key == ESCAPE)
	{
		mlx_destroy_image(data->mlx, data->load->img);
		loading_screen(data, data->load);
	}
	return (0);
}

static void	setting(t_data *data, t_pict *load)
{
	int		x[2];

	data->load = load;
	mlx_destroy_image(data->mlx, data->load->img);
	load->img = mlx_xpm_file_to_image(data->mlx, \
	"./sprite/settings.xpm", &x[1], &x[0]);
	if (!load->img)
		confirm(data, 371);
	load->addr = mlx_get_data_addr(load->img, &load->bytes, \
	&load->l_len, &load->endian);
	data->w_size[0] = 30;
	if (data->set == 0)
		data->w_size[1] = 66;
	else if (data->set == 1)
		data->w_size[1] = 166;
	else if (data->set == 2)
		data->w_size[1] = 266;
	else if (data->set == 3)
		data->w_size[1] = 366;
	else
		data->w_size[1] = 66;
	draw_cursor(load, 30, data->w_size[1]);
	mlx_put_image_to_window(data->mlx, data->win, load->img, 0, 0);
	mlx_hook(data->win, DestroyNotify, 0, quit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, set_input, data);
}

int	confirm(t_data *data, int error)
{
	if (data->w_size[1] == 390)
	{
		if (data->load->img)
			mlx_destroy_image(data->mlx, data->load->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_the_mallocs(data->map);
		exit(error);
	}
	if (data->w_size[1] == 265)
		setting(data, data->load);
	if (data->w_size[1] == 110)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_image(data->mlx, data->load->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		launch(data);
	}
	return (0);
}

static int	load_input(int key, t_data *data)
{
	erease_cursor(data->load, data->w_size[0], data->w_size[1]);
	if (key == W_KEY)
	{
		if (data->w_size[1] == 390)
			data->w_size[1] = 265;
		else if (data->w_size[1] == 265)
			data->w_size[1] = 110;
	}
	if (key == S_KEY)
	{
		if (data->w_size[1] == 110)
			data->w_size[1] = 265;
		else if (data->w_size[1] == 265)
			data->w_size[1] = 390;
	}
	draw_cursor(data->load, data->w_size[0], data->w_size[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->load->img, 0, 0);
	if (key == ENTER)
		confirm(data, 0);
	if (key == ESCAPE)
	{
		data->w_size[1] = 390;
		confirm(data, 0);
	}
	return (0);
}

void	loading_screen(t_data *data, t_pict *load)
{
	int		x[2];

	data->load = load;
	load->img = mlx_xpm_file_to_image(data->mlx, \
	"./sprite/loading.xpm", &x[1], &x[0]);
	if (!load->img)
		confirm(data, 371);
	load->addr = mlx_get_data_addr(load->img, \
	&load->bytes, &load->l_len, &load->endian);
	draw_cursor(load, 30, 110);
	data->w_size[0] = 30;
	data->w_size[1] = 110;
	mlx_put_image_to_window(data->mlx, data->win, load->img, 0, 0);
	mlx_hook(data->win, DestroyNotify, 0, quit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, load_input, data);
	mlx_loop(data->mlx);
}
