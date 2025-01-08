/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/01/08 08:06:23 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	draw_tiles(t_data *data, void *img, size_t x, size_t y)
{
	if (data->map[y][x] == 'e'
		&& (data->player.pos_x != x || data->player.pos_y != y))
		img = data->sprite.c_ex.img;
	if (data->map[y + 1])
		if (data->map[y + 1][x] == '1' && data->map[y][x] == '1')
			img = data->sprite.wall2.img;
	mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
}

static void	draw_world(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_tiles(data, data->sprite.wall.img, x, y);
			if (data->map[y][x] == '2' || data->map[y][x] == '0')
				draw_tiles(data, data->sprite.tile.img, x, y);
			if (data->map[y][x] == 'e')
				draw_tiles(data, data->sprite.c_ex.img, x, y);
			if (data->map[y][x] == 'c')
				draw_tiles(data, data->sprite.obj.img, x, y);
			if (data->map[y][x] == 'p')
				draw_tiles(data, data->sprite.play.img, x, y);
			x++;
		}
		y++;
	}
}

void	world_init(t_data *data)
{
/* 	size_t	i;

	i = 0;
	while (data->map[0][i] != '\n')
		i++;
	data->w_size[0] = (int) i;
	i = 0;
	while (data->map[i])
		i++;
	data->w_size[1] = (int) i;
	if (data->w_size[0] > 60 || data->w_size[1] > 33)
	{
		write(2, "Map to large\n", 13);
		clean_exit(data, 1);
	} */
	draw_world(data);
}
