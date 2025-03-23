/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:34 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	merge_image(t_pict screen, t_pict *img, t_data *data, int frame)
{
	int		i;
	int		j;
	char	*pixel;
	char	*color;

	(void) data;
	i = 0;
	color = 0;
	while (i < ASSET)
	{
		j = 0;
		while (j < ASSET)
		{
			pixel = &screen.addr[i * screen.l_len + j * screen.bytes / 8];
			color = get_color(img, i, j, frame);
			if (*(int *) color == -16777216)
				color = get_asset(data, (t_vect){j, i});
			*(unsigned int *) pixel = *(unsigned int *) color;
			j++;
		}
		i++;
	}
}

static void	draw_tiles(t_data *data, int x[2], int y[2], t_vect offset_pix)
{
	t_pict	*img;

	if (data->map[y[1]][x[1]] == '\n' || data->map[y[1]][x[1]] == '\0')
		return ;
	else if (data->map[y[1]][x[1]] == '2' || data->map[y[1]][x[1]] == '0')
		img = &data->sprite.tile;
	else if (data->map[y[1]][x[1]] == 'e' && data->engine.obj > 0)
		img = &data->sprite.c_ex;
	else if (data->map[y[1]][x[1]] == 'e' && data->engine.obj == 0)
		img = &data->sprite.o_ex;
	else if (data->map[y[1]][x[1]] == 'c')
		img = &data->sprite.obj;
	else if (data->map[y[1] + 1] && data->map[y[1] + 1][x[1]] == '1'
		&& data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall2;
	else if (data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall;
	else
		img = &data->sprite.tile;
	mlx_put_image_to_window(data->mlx_info.mlx, \
		data->mlx_info.win, img->img, x[0] * ASSET - \
		offset_pix.x, y[0] * ASSET - offset_pix.y);
}

void	draw_world(t_data *data, t_vect offset, t_vect offset_pix)
{
	int	y[2];
	int	x[2];

	y[0] = 0;
	y[1] = y[0] + offset.y;
	while (y[0] <= data->mlx_info.w_size->y / ASSET + 2 && data->map[y[1]])
	{
		x[0] = 0;
		x[1] = x[0] + offset.x;
		while (x[0] <= data->mlx_info.w_size->x + 1 \
		/ ASSET && data->map[y[1]][x[1]])
		{
			draw_tiles(data, x, y, offset_pix);
			x[1]++;
			x[0]++;
		}
		y[1]++;
		y[0]++;
	}
}
