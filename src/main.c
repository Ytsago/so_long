/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2025/02/10 10:36:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		write (2, "Error\nSomething went wrong", 26);
		free_the_mallocs(data->map);
		exit(1);
	}
	data->move = 0;
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
	size_t		x;
	size_t		y;
	void		*pt[4];

	x = data->w_size[0] / 2 - 450;
	y = data->w_size[1] / 2 - 350;
	pt[0] = data->mlx;
	pt[1] = data->win;
	pt[2] = data->sprite.end.img;
	mlx_clear_window(data->mlx, data->win);
	data->end = 1;
	mlx_put_image_to_window(pt[0], pt[1], pt[2], x, y);
}

void	asset_init(t_sprite *sprt)
{
	sprt->c_ex.img = NULL;
	sprt->o_ex.img = NULL;
	sprt->obj.img = NULL;
	sprt->play.img = NULL;
	sprt->tile.img = NULL;
	sprt->wall.img = NULL;
	sprt->wall2.img = NULL;
	sprt->end.img = NULL;
}

int	launch(t_data *data)
{
	asset_init(&data->sprite);
	data_init(data);
	world_init(data);
	mlx_loop_hook(data->mlx, rendering, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, input, data);
	mlx_hook(data->win, DestroyNotify, 0, close_button, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_pict	load;

	if (ac != 2 || map_parsing(&data, av[1]))
	{
		if (ac != 2)
			write (2, "Error\nNot the right number of arguments", 40);
		return (1);
	}
	load.img = NULL;
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		write (2, "Error\n failed to create mlx_ptr", 31);
		return (1);
	}
	data.win = mlx_new_window(data.mlx, 400, 500, TITLE);
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free (data.mlx);
		return ((void) write (2, "Error\nCan't create window", 25), 1);
	}
	data.set = 0;
	loading_screen(&data, &load);
}
