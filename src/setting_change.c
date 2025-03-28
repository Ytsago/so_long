/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:43:52 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 10:47:44 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_resolution(t_data *data)
{
	if (data->engine.set == LOW)
		data->mlx_info.w_size[1] = 66;
	else if (data->engine.set == MEDIUM)
		data->mlx_info.w_size[1] = 166;
	else if (data->engine.set == HIGH)
		data->mlx_info.w_size[1] = 266;
	else if (data->engine.set == MAX)
		data->mlx_info.w_size[1] = 366;
	else
		data->mlx_info.w_size[1] = 66;
}

void	change_selection(t_data *data)
{
	draw_cursor(data->load, data->mlx_info.w_size[0], \
	data->mlx_info.w_size[1]);
	mlx_put_image_to_window(data->mlx_info.mlx, \
	data->mlx_info.win, data->load->img, 0, 0);
}
