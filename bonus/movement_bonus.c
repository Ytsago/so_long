/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:24:29 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:18:02 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	handle_velocity(t_data *data)
{
	data->player.velo.x += data->player.acc.x;
	data->player.velo.y += data->player.acc.y;
	if (data->player.velo.x > MAX_VELOCITY)
		data->player.velo.x = MAX_VELOCITY;
	if (data->player.velo.x < -MAX_VELOCITY)
		data->player.velo.x = -MAX_VELOCITY;
	if (data->player.velo.y > MAX_VELOCITY)
		data->player.velo.y = MAX_VELOCITY;
	if (data->player.velo.y < -MAX_VELOCITY)
		data->player.velo.y = -MAX_VELOCITY;
	if (data->player.acc.x == 0 && data->engine.jump == 0)
		data->player.velo.x *= FRICTION;
	data->player.acc.y += (data->player.acc.y <= 0);
}

void	do_movement(t_data *data, t_entity *entity, t_vect small_move)
{
	while (small_move.x || small_move.y)
	{
		if (check_collision(data, entity, (t_vect){small_move.x, 0}, '1'))
		{
			entity->pos.x += small_move.x;
			entity->move += absolute(small_move.x);
			small_move.x = 0;
		}
		else
		{
			small_move.x += - (small_move.x > 0) + (small_move.x < 0);
			entity->velo.x = 0;
		}
		if (check_collision(data, entity, (t_vect){0, small_move.y}, '1'))
		{
			entity->pos.y += small_move.y;
			entity->move += absolute(small_move.y);
			small_move.y = 0;
		}
		else
		{
			small_move.y += - (small_move.y > 0) + (small_move.y < 0);
			entity->velo.y = 0;
		}
	}
}

void	do_entity_move(t_data *data, t_entity *entity)
{
	while (entity)
	{
		if (coord_range(data->player.pos, entity->pos) < AGGRO)
			entity->f(data, entity);
		entity = entity->next;
	}
}

// Movement function that checks for collisions before applying movement
void	movement(t_data *data)
{
	t_vect		small_move;
	t_hitbox	foot;

	handle_velocity(data);
	small_move = (t_vect){data->player.velo.x, data->player.velo.y};
	do_movement(data, &data->player, small_move);
	foot.top = (t_vect){15, 58};
	foot.bot = (t_vect){45, 58};
	if (!check_ground(data, &data->player, foot, '1'))
		data->engine.jump = 0;
	else if (data->engine.jump == 0)
		data->engine.jump = 1;
	do_entity_move(data, data->monster);
}
