/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2024/12/18 19:30:10 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "ft_printf.h"

void	clean_exit(t_data *data)
{
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
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
}

void	load_asset(t_data *data)
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
	data->sprite = as;
 	if (!as.c_ex.img || !as.obj.img || !as.play.img
		|| !as.tile.img || !as.wall.img)
	{
		write (2, "failed to load asset\n", 21);
		clean_exit(data);
	}
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(0);
	data->win = mlx_new_window(data->mlx, DEFAULT_X, DEFAULT_Y, TITLE);
	if (!data->win)
		clean_exit(data);
	load_asset(data);
}

int	input(int key, void *param)
{
	char 	**map;
	t_data	*data;

	data = param;
	map = data->map;
	ft_printf("%d, %d", data->player.pos_y, data->player.pos_x);
	if (key == ESCAPE)
		clean_exit(param);
	if (key == W_KEY && map[data->player.pos_y - 1][data->player.pos_x] != '1')
	{
		data->player.pos_y -= 1;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite.tile.img,
			(int)data->player.pos_x * 32, (int)data->player.pos_y * 32);
	}
	if (key == D_KEY && map[data->player.pos_y][data->player.pos_x + 1] != '1')
	{
		data->player.pos_x += 1;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite.tile.img,
			(int)data->player.pos_x * 32, (int)data->player.pos_y * 32);
	}
	if (key == A_KEY && map[data->player.pos_y][data->player.pos_x - 1] != '1')
	{
		data->player.pos_x -= 1;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite.tile.img,
			(int)data->player.pos_x * 32, (int)data->player.pos_y * 32);
	}
	if (key == S_KEY && map[data->player.pos_y + 1][data->player.pos_x] != '1')
	{
		data->player.pos_y += 1;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite.tile.img,
			(int)data->player.pos_x * 32, (int)data->player.pos_y * 32);
	}
	return (1);
}

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
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_loop(data.mlx);
}
