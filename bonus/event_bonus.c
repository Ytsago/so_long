/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:25:33 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:40 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	destroy_image(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

int	close_button(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}

int	quit(t_data *data)
{
	data->mlx_info.w_size->y = 390;
	confirm(data, 0);
	return (0);
}

void	free_entity(t_entity *entity)
{
	t_entity	*tmp;

	while (entity)
	{
		tmp = entity;
		entity = entity->next;
		free(tmp);
	}
}

int	clean_exit(t_data *data, int error)
{
	if (data->mlx_info.win)
		mlx_destroy_window(data->mlx_info.mlx, data->mlx_info.win);
	free_the_mallocs(data->map);
	destroy_image(data->mlx_info.mlx, data->sprite.wall.img);
	destroy_image(data->mlx_info.mlx, data->sprite.play[FORW].img);
	destroy_image(data->mlx_info.mlx, data->sprite.play[BACK].img);
	destroy_image(data->mlx_info.mlx, data->sprite.play[IDLE].img);
	destroy_image(data->mlx_info.mlx, data->sprite.obj.img);
	destroy_image(data->mlx_info.mlx, data->sprite.c_ex.img);
	destroy_image(data->mlx_info.mlx, data->sprite.o_ex.img);
	destroy_image(data->mlx_info.mlx, data->sprite.tile.img);
	destroy_image(data->mlx_info.mlx, data->sprite.wall2.img);
	destroy_image(data->mlx_info.mlx, data->sprite.end.img);
	destroy_image(data->mlx_info.mlx, data->engine.screen.img);
	destroy_image(data->mlx_info.mlx, data->sprite.enemy.img);
	free_entity(data->monster);
	mlx_destroy_display(data->mlx_info.mlx);
	free(data->mlx_info.mlx);
	if (error)
		write(2, "Error\nFailed to load game", 26);
	exit(error);
}
