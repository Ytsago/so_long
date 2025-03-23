/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:00 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:45 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "ft_printf.h"

int	input(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == SPACE && data->engine.jump < 2)
	{
		data->player.acc.y = -8;
		data->engine.jump += 1;
		return (1);
	}
	if (key == D_KEY)
		data->player.acc.x = +1;
	if (key == S_KEY)
	{
		data->player.velo.x = 0;
		data->player.velo.y = 0;
	}
	if (key == A_KEY)
		data->player.acc.x = -1;
	if (key == F_KEY)
		data->engine.fly *= -1;
	if (key == SHIFT && data->engine.dodge == 1)
		data->engine.dodge = 0;
	if (key == ESCAPE)
		clean_exit(data, 0);
	return (1);
}

int	key_release(int key, t_data *data)
{
	if (key == SPACE || data->player.acc.y < 0)
		data->player.acc.y = 0;
	if (key == D_KEY)
		data->player.acc.x = 0;
	if (key == S_KEY)
		data->player.acc.y = 0;
	if (key == A_KEY)
		data->player.acc.x = 0;
	return (1);
}
