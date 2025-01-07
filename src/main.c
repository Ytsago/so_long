/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2025/01/07 11:55:09 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	clean_exit(t_data *data, int error)
{
	if (error == 371)
		error = 0;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	 free_the_mallocs(data->map);
	if (data->sprite.wall.img)
		mlx_destroy_image(data->mlx, data->sprite.wall.img);
	if (data->sprite.play.img)
		mlx_destroy_image(data->mlx, data->sprite.play.img);
	if (data->sprite.obj.img)
		mlx_destroy_image(data->mlx, data->sprite.obj.img);
	if (data->sprite.c_ex.img)
		mlx_destroy_image(data->mlx, data->sprite.c_ex.img);
	if (data->sprite.tile.img)
		mlx_destroy_image(data->mlx, data->sprite.tile.img);
	if (data->sprite.wall2.img)
		mlx_destroy_image(data->mlx, data->sprite.wall2.img);
/* 	if (data->sprite.gato.img)
		mlx_destroy_image(data->mlx, data->sprite.gato.img); */
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (error)
		write(2, "Error\nFailed to load game", 26);
	exit(error);
}

static void	load_asset(t_data *data)
{
	t_sprite	as;
	int			x;
	int			y;

	x = 0;
	y = 0;
	as.wall.img = mlx_xpm_file_to_image(data->mlx, WALL, &x, &y);
	as.play.img = mlx_xpm_file_to_image(data->mlx, PLAYER, &x, &y);
	as.tile.img = mlx_xpm_file_to_image(data->mlx, TILE, &x, &y);
	as.obj.img = mlx_xpm_file_to_image(data->mlx, OBJ, &x, &y);
	as.c_ex.img = mlx_xpm_file_to_image(data->mlx, CEXIT, &x, &y);
	as.wall2.img = mlx_xpm_file_to_image(data->mlx, WALL2, &x, &y);
	//as.gato.img = mlx_xpm_file_to_image(data->mlx, GATO, &x, &y);
	data->sprite = as;
	if (!as.c_ex.img || !as.obj.img || !as.play.img
		|| !as.tile.img || !as.wall.img || !as.wall2.img)
	{
		write (2, "Failed to load asset\n", 21);
		clean_exit(data, 1);
	}
}

static void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->exit = 0;
	data->move = 1;
	data->end = 0;
	if (data->set == 0)
	{
		data->w_size[0] = 1080;
		data->w_size[1] = 720;
	}
	if (data->set == 1)
	{
		data->w_size[0] = 1920;
		data->w_size[1] = 1080;
	}
	if (data->set == 2)
	{
		data->w_size[0] = 2560;
		data->w_size[1] = 1440;
	}
	if (data->set == 3)
	{
		data->w_size[0] = 3840;
		data->w_size[1] = 2160;
	}
	if (!data->mlx)
		clean_exit(data, 1);
	data->win = mlx_new_window(data->mlx, data->w_size[0], data->w_size[1], TITLE);
	if (!data->win)
		clean_exit(data, 1);
	load_asset(data);
}

void	end_game(t_data *data)
{
	int		x;
	int		y;
	void	*pt[3];

	x = 0;
	y = 0;
	pt[0] = data->mlx;
	pt[1] = data->win;
	pt[2] = data->sprite.gato.img;
	data->end = 1;
//	mlx_put_image_to_window(pt[0], pt[1], pt[2], x, y);
}
/*
int	main(int ac, char **av)
{
	t_data		data;
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (ac != 2)
		return (1);
	if (map_parsing(&data, av[1]))
		return (1);
	data_init(&data);
	world_init(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_hook(data.win, DestroyNotify, 0, clean_exit, &data);
	mlx_loop(data.mlx);
}
*/ 
int	launch(t_data *data)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (map_parsing(data, data->path))
		return (1);
	data_init(data);
	world_init(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, input, data);
	mlx_hook(data->win, DestroyNotify, 0, clean_exit, data);
	mlx_loop(data->mlx);
	return (0);
}

void	draw_cursor(t_pict *img, int x, int y)
{
	int		i;
	int		j;
	char	*pixel;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while ((j < 2 * i && i <= 15) || (i > 15 && j < 60 - i * 2))
		{
			pixel = &img->addr[(y + i) * img->l_len + (x + j) * img->bytes / 8];
			*(unsigned int *) pixel = 0x00FF0000;
			j++;
		}
		i++;
	}
}

void	erease_cursor(t_pict *img, int x, int y)
{
	int		i;
	int		j;
	char	*pixel;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while ((j < 2 * i && i <= 15) || (i > 15 && j < 60 - i * 2))
		{
			pixel = &img->addr[(y + i) * img->l_len + (x + j) * img->bytes / 8];
			*(unsigned int *) pixel = 0x432a73;
			j++;
		}
		i++;
	}
}

void	setting(t_data *data, t_pict *load);

int	confirm(t_data *data, int key)
{
	if (data->w_size[1] == 390 || key == 371)
	{
		mlx_destroy_image(data->mlx, data->load->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
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

int	load_input(int key, t_data *data)
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

void	loading_screen(t_data *data, t_pict *load);

int	set_input(int key, t_data *data)
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

void	setting(t_data *data, t_pict *load)
{
	int		x[2];
	mlx_destroy_image(data->mlx, data->load->img);
	load->img = mlx_xpm_file_to_image(data->mlx, "./sprite/settings.xpm", &x[1], &x[0]);
	load->addr = mlx_get_data_addr(load->img, &load->bytes, &load->l_len, &load->endian);
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
	data->load = load;
	mlx_put_image_to_window(data->mlx, data->win, load->img, 0, 0);
	mlx_hook(data->win, DestroyNotify, 0, confirm, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, set_input, data);
}

void	loading_screen(t_data *data, t_pict *load)
{
	int		x[2];

	load->img = mlx_xpm_file_to_image(data->mlx, "./sprite/loading.xpm", &x[1], &x[0]);
	load->addr = mlx_get_data_addr(load->img, &load->bytes, &load->l_len, &load->endian);
	draw_cursor(load, 30, 110);
	data->w_size[0] = 30;
	data->w_size[1] = 110;
	data->load = load;
	mlx_put_image_to_window(data->mlx, data->win, load->img, 0, 0);
	mlx_hook(data->win, DestroyNotify, 0, confirm, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, load_input, data);
	mlx_loop(data->mlx);
}

int main (int ac, char **av)
{
	t_data	data;
	t_pict	load;

	if (ac != 2)
	{
		write (2, "Error\nNot the right number of arguments", 40);
		return (1);
	}
	data.path = av[1];
	load.img = NULL;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 400, 500, "Squirrel Revenge");
	data.set = 0;
	loading_screen(&data, &load);
}