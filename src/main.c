/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2025/01/07 11:51:30 by secros           ###   ########.fr       */
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
	if (data->sprite.gato.img)
		mlx_destroy_image(data->mlx, data->sprite.gato.img);
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
	as.gato.img = mlx_xpm_file_to_image(data->mlx, GATO, &x, &y);
	data->sprite = as;
	if (!as.c_ex.img || !as.obj.img || !as.play.img || !as.gato.img
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
	if (!data->mlx)
		clean_exit(data, 1);
	data->win = mlx_new_window(data->mlx, DEFAULT_X, DEFAULT_Y, TITLE);
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
	mlx_put_image_to_window(pt[0], pt[1], pt[2], x, y);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (ac != 2)
	{
		write (2, "Error\nNot the right number of arguments", 40);
		return (1);
	}
	if (map_parsing(&data, av[1]))
		return (1);
	data_init(&data);
	world_init(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_hook(data.win, DestroyNotify, 0, clean_exit, &data);
	mlx_loop(data.mlx);
}
