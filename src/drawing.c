/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/01/09 10:34:16 by secros           ###   ########.fr       */
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

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	t_pict	*img;
	char	*pixel;

	img = &data->sprite.play;
	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			pixel = &img->addr[i * img->l_len + j * img->bytes / 8];
			if (*(unsigned int*) pixel == 0x000000)
				*(unsigned int*) pixel = 0x00000000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img, data->player.pos_x, data->player.pos_y * 64);
}

static void	draw_tiles(t_data *data, int x[2], int y[2])
{
	void	*img;
	static char	first_draw = 0; 

	if (first_draw == 0 && data->map[y[1]][x[1]] == 'p')
	{
		img = data->sprite.play.img;
		first_draw = 1;
	}
	else
	{
		draw_player(data);
	}
	if (data->map[y[1]][x[1]] == '1')
		img = data->sprite.wall.img;
	if (data->map[y[1]][x[1]] == '2' || data->map[y[1]][x[1]] == '0')
		img = data->sprite.tile.img;
	if (data->map[y[1]][x[1]] == 'e')
		img = data->sprite.c_ex.img;
	if (data->map[y[1]][x[1]] == 'c')
		img = data->sprite.obj.img;
	if (data->map[y[1] + 1] && data->map[y[1] + 1][x[1]] == '1'
		&& data->map[y[1]][x[1]] == '1')
		img = data->sprite.wall2.img;
	mlx_put_image_to_window(data->mlx, data->win, img, x[0] * 64, y[0] * 64);
}

static void	draw_world(t_data *data, int i, int j)
{
	int			y[2];
	int			x[2];

	y[0] = 0;
	y[1] = y[0] + j;
	while (y[0]  <= data->w_size[1] / 64 && data->map[y[1]])
	{
		x[0] = 0;
		x[1] = x[0] + i;
		while (x[0] <= data->w_size[0] + 1 / 64 && data->map[y[1]][x[1]])
		{
			draw_tiles(data, x, y);
			x[1]++;
			x[0]++;
		}
		y[1]++;
		y[0]++;
	}
}

void	world_init(t_data *data)
{
	int	i;
	int	j;

	i = data->w_size[0] / 128;
	j = data->w_size[1] / 128;
	i = data->player.pos_x / 64 - i;
	if (data->player.pos_x / 64 + data->w_size[0] / 128 > (int) ft_strlen(data->map[0]) - 2 + (data->w_size[0] % 128 == 0))
	 	i = ft_strlen(data->map[0]) - 2 + (data->w_size[0] % 128 == 0) - data->w_size[0] / 64;
	if (i < 0)
		i = 0;
	j = data->player.pos_y / 64 - j;
	if (data->player.pos_y / 64 + data->w_size[1] / 128 > (int) ft_tablen(data->map) - 1)
	 	j = ft_tablen(data->map) - 1 + (data->w_size[0] % 128 != 0) + (data->w_size[1] % 128 == 112) - data->w_size[1] / 64;
	if (j < 0)
		j = 0;
	draw_world(data, i, j);
}
