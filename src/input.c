/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:00 by secros            #+#    #+#             */
/*   Updated: 2025/01/07 08:16:12 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"

static void	check_pos(t_data *data)
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

static void	moving(t_data *data, size_t *x, size_t *y, int dir)
{
	ft_printf("move :%d ", data->move++);
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
	char	**map;
	t_data	*data;
	size_t	x;
	size_t	y;

	data = param;
	map = data->map;
	x = data->player.pos_x;
	y = data->player.pos_y;
	if (key == ESCAPE)
		clean_exit(param, 0);
	if (key == W_KEY && map[y - 1][x] != '1' && data->end == 0
		&& (map[y - 1][x] != 'e' || data->exit == 1))
		moving(data, &data->player.pos_x, &data->player.pos_y, 1);
	if (key == D_KEY && map[y][x + 1] != '1' && data->end == 0
		&& (map[y][x + 1] != 'e' || data->exit == 1))
		moving(data, &data->player.pos_x, &data->player.pos_y, 2);
	if (key == A_KEY && map[y][x - 1] != '1' && data->end == 0
		&& (map[y][x - 1] != 'e' || data->exit == 1))
		moving(data, &data->player.pos_x, &data->player.pos_y, 3);
	if (key == S_KEY && map[y + 1][x] != '1' && data->end == 0
		&& (map[y + 1][x] != 'e' || data->exit == 1))
		moving(data, &data->player.pos_x, &data->player.pos_y, 4);
	check_pos(data);
	return (1);
}
