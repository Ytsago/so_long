/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:41:06 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:21 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_collision(t_data *data, t_entity *entity, t_vect velo, char c)
{
	if (data->map[(entity->pos.y + entity->hitbox.top.y + velo.y) / ASSET] \
	[(entity->pos.x + entity->hitbox.top.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + entity->hitbox.bot.y + velo.y) / ASSET] \
	[(entity->pos.x + entity->hitbox.top.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + entity->hitbox.top.y + velo.y) / ASSET] \
	[(entity->pos.x + entity->hitbox.bot.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + entity->hitbox.bot.y + velo.y) / ASSET] \
	[(entity->pos.x + entity->hitbox.bot.x + velo.x) / ASSET] == c)
		return (0);
	return (1);
}

char	remove_obj(t_data *data, t_hitbox hitbox, char c)
{
	t_vect	pos;

	pos = (t_vect){data->player.pos.x, data->player.pos.y};
	if (data->map[(pos.y + hitbox.top.y) / ASSET] \
	[(pos.x + hitbox.top.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.top.y) / ASSET] \
		[(pos.x + hitbox.top.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.bot.y) / ASSET] \
	[(pos.x + hitbox.top.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.bot.y) / ASSET] \
		[(pos.x + hitbox.top.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.top.y) / ASSET] \
	[(pos.x + hitbox.bot.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.top.y) / ASSET] \
		[(pos.x + hitbox.bot.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.bot.y) / ASSET] \
	[(pos.x + hitbox.bot.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.bot.y) / ASSET] \
		[(pos.x + hitbox.bot.x) / ASSET] = c - 32);
	return (0);
}

int	enemy_col(t_data *data, t_entity *entity)
{
	if (is_in_range(entity->hitbox, entity->pos, (t_vect) \
	{data->player.pos.x + data->player.hitbox.top.x, \
	data->player.pos.y + data->player.hitbox.top.y}))
		return (1);
	if (is_in_range(entity->hitbox, entity->pos, (t_vect) \
	{data->player.pos.x + data->player.hitbox.top.x, \
	data->player.pos.y + data->player.hitbox.bot.y}))
		return (1);
	if (is_in_range(entity->hitbox, entity->pos, (t_vect) \
	{data->player.pos.x + data->player.hitbox.bot.x, \
	data->player.pos.y + data->player.hitbox.top.y}))
		return (1);
	if (is_in_range(entity->hitbox, entity->pos, (t_vect) \
	{data->player.pos.x + data->player.hitbox.bot.x, \
	data->player.pos.y + data->player.hitbox.bot.y}))
		return (1);
	return (0);
}

void	check_pos(t_data *data)
{
	t_entity	*entity;

	if (remove_obj(data, data->player.hitbox, 'c'))
		data->engine.obj--;
	if (data->engine.obj == 0 && remove_obj(data, data->player.hitbox, 'e'))
		end_game(data);
	entity = data->monster;
	while (entity)
	{
		if (enemy_col(data, entity) && data->engine.dodge == 1)
		{
			ft_printf("Too bad, you loose...");
			clean_exit(data, 0);
		}
		entity = entity->next;
	}
}

int	check_ground(t_data *data, t_entity *entity, t_hitbox foot, char c)
{
	if (data->engine.fly == -1)
		return (0);
	if (data->map[(entity->pos.y + foot.top.y) / ASSET] \
	[(entity->pos.x + foot.top.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + foot.bot.y) / ASSET] \
	[(entity->pos.x + foot.top.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + foot.top.y) / ASSET] \
	[(entity->pos.x + foot.bot.x) / ASSET] == c)
		return (0);
	if (data->map[(entity->pos.y + foot.bot.y) / ASSET] \
	[(entity->pos.x + foot.bot.x) / ASSET] == c)
		return (0);
	return (1);
}
