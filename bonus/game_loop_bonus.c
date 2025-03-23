/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:53:36 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:42 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	step_count(t_data *data)
{
	char			*str;
	char			print;
	char			*step;
	static size_t	move;

	print = 0;
	if (move != data->player.move / 64)
	{
		print = 1;
		move = data->player.move / 64;
	}
	step = ft_itoa(move);
	if (!step)
		clean_exit(data, 1);
	if (print)
		ft_printf("Step : %s\n", step);
	str = ft_strjoin("Step :", step);
	free (step);
	if (!str)
		clean_exit(data, 1);
	mlx_string_put(data->mlx_info.mlx, data->mlx_info.win, 15, 15, 0, str);
	free (str);
}

int	delta_time(t_data *data, struct timeval *time, int threshold)
{
	int				delta;
	struct timeval	new_time;

	if (gettimeofday(&new_time, NULL) == -1)
		clean_exit(data, 1);
	if (time->tv_usec < new_time.tv_usec)
		delta = new_time.tv_usec - time->tv_usec;
	else
		delta = 1000000 + new_time.tv_usec - time->tv_usec;
	if (delta >= threshold)
	{
		time->tv_usec = new_time.tv_usec;
		return (1);
	}
	return (0);
}

void	dodge_logic(t_data *data)
{
	static char	frame;

	if (frame < 0)
	{
		data->engine.dodge = 1;
		frame++;
	}
	if (data->engine.dodge == 0 && frame >= 0)
	{
		frame++;
		if (frame == IMMUNE)
		{
			frame = COOLDOWN;
			data->engine.dodge = 1;
		}
	}
}

int	game_loop(t_data *data)
{
	if (data->engine.end == 0 && delta_time(data, \
	&data->engine.time, FRAME_RATE))
	{
		movement(data);
		if (data->engine.dodge == 0)
			dodge_logic(data);
		world_init(data);
		step_count(data);
		check_pos(data);
	}
	return (1);
}
