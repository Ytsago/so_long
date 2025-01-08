/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/01/08 15:29:10 by secros           ###   ########.fr       */
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

void	draw_tiles(t_data *data, void *img, int x, int y)
{
/* 	if (data->map[y][x] == 'e'
		&& (data->player.pos_x != x || data->player.pos_y != y))
		img = data->sprite.c_ex.img;
	if (data->map[y + 1])
		if (data->map[y + 1][x] == '1' && data->map[y][x] == '1')
			img = data->sprite.wall2.img; */
	mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
}

static void	draw_world(t_data *data, int i, int j)
{
	int	y;
	int	x;

	y = 0;
	while (y  < data->w_size[1] + 1 / 64 && data->map[y + j])
	{
		x = 0;
		while (x < data->w_size[0] + 1 / 64 && data->map[j + y][i + x])
		{
			if (data->map[j + y][i + x] == '1')
				draw_tiles(data, data->sprite.wall.img, x, y);
			if (data->map[j + y][i + x] == '2' || data->map[j + y][i + x] == '0')
				draw_tiles(data, data->sprite.tile.img, x, y);
			if (data->map[j + y][i + x] == 'e')
				draw_tiles(data, data->sprite.c_ex.img, x, y);
			if (data->map[j + y][i + x] == 'c')
				draw_tiles(data, data->sprite.obj.img, x, y);
			if (data->map[j + y][i + x] == 'p')
				draw_tiles(data, data->sprite.play.img, x, y);
			x++;
		}
		y++;
	}
}

void	world_init(t_data *data)
{
	int	i;
	int	j;

	i = data->w_size[0] / 128;
	j = data->w_size[1] / 128;
	ft_printf("%d", ft_tablen(data->map));
	if (data->player.pos_x + i > (int)ft_strlen(data->map[0]))
		i -= (ft_strlen(data->map[0])) - (i + data->player.pos_x - 2);
	if (data->player.pos_x - i < 0)
		i = 0;
	//ft_printf("%d %d", i,data->player.pos_x);
	draw_world(data, i, 0);
}
