/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2024/12/16 18:35:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "ft_printf.h"

void	clean_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->sprite->img1);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
}

void	data_init(t_data *data)
{
	data->w_size[0] = DEFAULT_Y;
	data->w_size[1] = DEFAULT_X;
	data->pos[0] = 50;
	data->pos[1] = 50;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, DEFAULT_X, DEFAULT_Y, "so long");
}

void	move_player(t_data *data, int key)
{
	if (key == 119)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img2, data->player.pos[0] , data->player.pos[1]);
		data->player.pos[1] -= 32;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img4, data->player.pos[0] , data->player.pos[1]);
	}
	else if (key == 97)
	{	
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img2, data->player.pos[0] , data->player.pos[1]);
		data->player.pos[0] -= 32;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img4, data->player.pos[0] , data->player.pos[1]);
	}
	else if (key == 115)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img2, data->player.pos[0] , data->player.pos[1]);
		data->player.pos[1] += 32;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img4, data->player.pos[0] , data->player.pos[1]);
	}
	else if (key == 100)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img2, data->player.pos[0] , data->player.pos[1]);
		data->player.pos[0] += 32;
		mlx_put_image_to_window(data->mlx, data->win, data->sprite->img4, data->player.pos[0] , data->player.pos[1]);
	}
}

int	input(int key, void *param)
{
	t_data	*data;

	data = param;

	if (key == 65307)
	{
		mlx_loop_end(data->mlx);
		clean_exit(param);
	}
	else
		move_player(data, key);
	return (1);
}

int	quit(void *param)
{
	t_data	*data;

	data = param;
	mlx_loop_end(data->mlx);
	clean_exit(param);
	return (1);
}

int main ()
{
	t_data		data;
	t_sprite	img;

	int x = 0;
	int y = 0;
	data_init(&data);
	data.sprite = &img;
	img.img1 = mlx_xpm_file_to_image(data.mlx, "./sprite/wall.xpm", &x, &y);
	img.img2 = mlx_xpm_file_to_image(data.mlx, "./sprite/floor.xpm", &x, &y);
	img.img3 = mlx_xpm_file_to_image(data.mlx, "./sprite/collect.xpm", &x, &y);
	img.img4 = mlx_xpm_file_to_image(data.mlx, "./sprite/player2.xpm", &x, &y);
	img.img5 = mlx_xpm_file_to_image(data.mlx, "./sprite/door.xpm", &x, &y);
	create_map("./test.ber", &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, quit, &data);
	mlx_loop(data.mlx);
}