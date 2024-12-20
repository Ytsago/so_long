/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2024/12/20 11:46:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "ft_printf.h"

int	clean_exit(t_data *data, int error)
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
	if (error)
		write(2, "Error\nFailed to load game", 26);
	exit(error);
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
	as.wall2.img = mlx_xpm_file_to_image(data->mlx, WALL2, &x, &y);
	data->sprite = as;
 	if (!as.c_ex.img || !as.obj.img || !as.play.img
		|| !as.tile.img || !as.wall.img || !as.wall2.img)
	{
		write (2, "Failed to load asset\n", 21);
		clean_exit(data, 1);
	}
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->exit = 0;
	if (!data->mlx)
		clean_exit(data, 1);
	data->win = mlx_new_window(data->mlx, DEFAULT_X, DEFAULT_Y, TITLE);
	if (!data->win)
		clean_exit(data, 1);
	load_asset(data);
}

void	end_game(t_data *data)
{
	clean_exit(data, 0);
}

void	check_pos(t_data *data)
{
	int	x;
	int	y;
	int	count;

	x = data->player.pos_x;
	y = data->player.pos_y;
	count = 0;
	if (data->map[y][x] == 'c')
		data->map[y][x] = 'C';
	else if (data->map[y][x] == 'e' && data->exit == 1)
		end_game(data);
	else
		return ;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
			if (data->map[y][x++] == 'c')
				count = 1;
		y++;
	}
	if (count == 0)
		data->exit = 1;
}

void	draw_tiles(t_data *data, void *img, int x, int y)
{
	if (data->map[y][x] == 'e')
		img = data->sprite.c_ex.img;
	if (data->map[y + 1])
		if (data->map[y + 1][x] == '1' && data->map[y][x] == '1')
			img = data->sprite.wall2.img;
	mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
}

void	moving(t_data *data, size_t *x, size_t *y, int dir)
{
	if (dir == 1)
	{
		draw_tiles(data, data->sprite.tile.img, *x, *y);
		*y -= 1;
		draw_tiles(data, data->sprite.play.img, *x, *y);
	}
	else if (dir == 2)
	{
		draw_tiles(data, data->sprite.tile.img, *x, *y);
		*x += 1;
		draw_tiles(data, data->sprite.play.img, *x, *y);
	}
	else if (dir == 3)
	{
		draw_tiles(data, data->sprite.tile.img, *x, *y);
		*x -= 1;
		draw_tiles(data, data->sprite.play.img, *x, *y);
	}
	else if (dir == 4)
	{
		draw_tiles(data, data->sprite.tile.img, *x, *y);
		*y += 1;
		draw_tiles(data, data->sprite.play.img, *x, *y);
	}
}

int	input(int key, void *param)
{
	char 	**map;
	t_data	*data;
	size_t	x;
	size_t	y;

	data = param;
	map = data->map;
	x = data->player.pos_x;
	y = data->player.pos_y;
	ft_printf("%d, %d", data->player.pos_y, data->player.pos_x);
	if (key == ESCAPE)
		clean_exit(param, 0);
	if (key == W_KEY && map[y - 1][x] != '1')
		moving(data, &data->player.pos_x, &data->player.pos_y, 1);
	if (key == D_KEY && map[y][x + 1] != '1')
		moving(data, &data->player.pos_x, &data->player.pos_y, 2);
	if (key == A_KEY && map[y][x - 1] != '1')
		moving(data, &data->player.pos_x, &data->player.pos_y, 3);
	if (key == S_KEY && map[y + 1][x] != '1')
		moving(data, &data->player.pos_x, &data->player.pos_y, 4);
	check_pos(data);
	return (1);
}


void	draw_world(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			write(1, &data->map[y][x], 1);
			if (data->map[y][x] == '1')
				draw_tiles(data, data->sprite.wall.img, x , y);
			if (data->map[y][x] == '2')
				draw_tiles(data, data->sprite.tile.img, x , y);
			if (data->map[y][x] == 'e')
				draw_tiles(data, data->sprite.c_ex.img, x , y);
			if (data->map[y][x] == 'c')
				draw_tiles(data, data->sprite.obj.img, x , y);
			if (data->map[y][x] == 'p')
				draw_tiles(data, data->sprite.play.img, x , y);
			x++;
		}
		y++;
	}
}

void	world_init(t_data *data)
{
	size_t	i;

	i = 0;
	while(data->map[0][i] != '\n')
		i++;
	data->w_size[0] = (int) i;
	i = 0;
	while(data->map[i])
		i++;
	data->w_size[1] = (int) i;
	draw_world(data);
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
	draw_world(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_hook(data.win, DestroyNotify, 0, clean_exit, &data);
	mlx_loop(data.mlx);
	mlx_string_put
}
