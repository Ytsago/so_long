/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:22:16 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:13 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

t_vect	compute_offset_x(t_data *data)
{
	t_vect	offset;

	offset.x = data->mlx_info.w_size->x / (2 * ASSET);
	offset.x = data->player.pos.x / ASSET - offset.x;
	offset.y = data->player.pos.x % ASSET;
	if (data->player.pos.x / ASSET + (offset.y > 0) + data->mlx_info.w_size->x \
	/ (2 * ASSET) > (int) ft_strlen(data->map[0]) - 2 + \
	(data->mlx_info.w_size->x % (2 * ASSET) == 0))
	{
		offset.x = ft_strlen(data->map[0]) - 2 + (data->mlx_info.w_size->x \
		% (2 * ASSET) == 0) - data->mlx_info.w_size->x / ASSET;
		offset.y = 0;
	}
	if (((offset.x * ASSET - offset.y) / ASSET) < 0)
	{
		offset.x = 0;
		offset.y = 0;
	}
	return (offset);
}

t_vect	compute_offset_y(t_data *data)
{
	t_vect	offset;

	offset.x = data->mlx_info.w_size->y / (2 * ASSET);
	offset.x = data->player.pos.y / ASSET - offset.x;
	offset.y = data->player.pos.y % ASSET;
	if (data->player.pos.y / ASSET + (offset.y > 0) + data->mlx_info.w_size->y \
	/ (2 * ASSET) > (int) ft_tablen(data->map) - 1)
	{
		offset.x = ft_tablen(data->map) - 1 + (data->mlx_info.w_size->x \
		% (2 * ASSET) != 0) + (data->mlx_info.w_size->y % (2 * ASSET) == 112) \
		- data->mlx_info.w_size->y / ASSET;
		offset.y = 0;
	}
	if (offset.x * ASSET + offset.y < 0)
	{
		offset.x = 0;
		offset.y = 0;
	}
	return (offset);
}

void	draw_entity(t_data *data, t_entity *entity, t_vect offset, \
	t_vect offset_pix)
{
	while (entity)
	{
		mlx_put_image_to_window(data->mlx_info.mlx, data->mlx_info.win, \
		data->sprite.enemy.img, entity->pos.x - offset.x * ASSET - \
		offset_pix.x, entity->pos.y - offset.y * ASSET - offset_pix.y);
		entity = entity->next;
	}
}

void	world_init(t_data *data)
{
	t_vect	offset;
	t_vect	temp;
	t_vect	offset_pix;

	temp = compute_offset_x(data);
	offset.x = temp.x;
	offset_pix.x = temp.y;
	temp = compute_offset_y(data);
	offset.y = temp.x;
	offset_pix.y = temp.y;
	draw_world(data, offset, offset_pix);
	select_frame(data, data->sprite.play);
	mlx_put_image_to_window(data->mlx_info.mlx, data->mlx_info.win, \
	data->engine.screen.img, data->player.pos.x - offset.x * ASSET - \
	offset_pix.x, data->player.pos.y - offset.y * ASSET - offset_pix.y);
	draw_entity(data, data->monster, offset, offset_pix);
}
