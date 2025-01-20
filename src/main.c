/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2025/01/20 13:44:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, 1);
	data->move = 1;
	data->end = 0;
	resolution(data);
	data->win = mlx_new_window(data->mlx, data->w_size[0], \
		data->w_size[1], TITLE);
	if (!data->win)
		clean_exit(data, 1);
	load_asset(data);
}

void	end_game(t_data *data)
{
	int		x;
	int		y;
	void	*pt[4];

	x = data->w_size[0] / 2 - 450;
	y = data->w_size[1] / 2 - 350;
	pt[0] = data->mlx;
	pt[1] = data->win;
	pt[2] = data->sprite.end.img;
	pt[3] = mlx_new_image(pt[0], data->w_size[0], data->w_size[1]);
	if (pt[3])
	{
		mlx_put_image_to_window(pt[0], pt[1], pt[3], 0, 0);
		mlx_destroy_image(pt[0], pt[3]);
	}
	data->end = 1;
	mlx_put_image_to_window(pt[0], pt[1], pt[2], x, y);
}

int	launch(t_data *data)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	data_init(data);
	world_init(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, input, data);
	mlx_hook(data->win, DestroyNotify, 0, close_button, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_pict	load;

	if (ac != 2 && map_parsing(&data, av[1]))
	{
		write (2, "Error\nNot the right number of arguments", 40);
		return (1);
	}
	load.img = NULL;
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		write (2, "Error\nFailed to create mlx_ptr", 30);
		return (1);
	}
	data.win = mlx_new_window(data.mlx, 400, 500, TITLE);
	if (!data.win)
	{
		write (2, "Error\nFailed to create window", 29);
		return (1);
	}
	data.set = 0;
	loading_screen(&data, &load);
}
