/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:00 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 10:23:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"

static void	check_pos(t_data *data)
{
	int	x;
	int	y;
	int	count;

	x = data->player.pos.x / 64;
	y = data->player.pos.y / 64;
	count = 0;
	if (data->map[y][x] == 'c')
	{
		data->map[y][x] = 'C';
		data->engine.obj--;
	}
	else if (data->map[y][x] == 'e' && data->engine.obj == 0)
		end_game(data);
}

static void	moving(t_data *data, int *x, int *y, int dir)
{
	data->engine.move++;
	data->map[*y / 64][*x / 64] = '2';
	if (ft_printf("move :%d\n", data->engine.move) == -1)
		return ((void) clean_exit(data, 1));
	if (dir == 1)
		*y -= 64;
	else if (dir == 2)
		*x += 64;
	else if (dir == 3)
		*x -= 64;
	else if (dir == 4)
		*y += 64;
	check_pos(data);
	data->map[*y / 64][*x / 64] = 'p';
}

int	input(int key, void *param)
{
	char		**map;
	t_data		*data;
	int			x;
	int			y;

	data = param;
	map = data->map;
	x = data->player.pos.x / 64;
	y = data->player.pos.y / 64;
	if (key == ESCAPE)
		clean_exit(param, 0);
	if (key == W_KEY && map[y - 1][x] != '1' && data->engine.end == 0
		&& (map[y - 1][x] != 'e' || data->engine.obj == 0))
		moving(data, &data->player.pos.x, &data->player.pos.y, 1);
	if (key == D_KEY && map[y][x + 1] != '1' && data->engine.end == 0
		&& (map[y][x + 1] != 'e' || data->engine.obj == 0))
		moving(data, &data->player.pos.x, &data->player.pos.y, 2);
	if (key == A_KEY && map[y][x - 1] != '1' && data->engine.end == 0
		&& (map[y][x - 1] != 'e' || data->engine.obj == 0))
		moving(data, &data->player.pos.x, &data->player.pos.y, 3);
	if (key == S_KEY && map[y + 1][x] != '1' && data->engine.end == 0
		&& (map[y + 1][x] != 'e' || data->engine.obj == 0))
		moving(data, &data->player.pos.x, &data->player.pos.y, 4);
	return (1);
}
