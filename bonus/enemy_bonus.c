/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:12:34 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 18:14:05 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	*create_monster(t_data *data, t_vect pos)
{
	t_entity	*monster;

	monster = ft_calloc(sizeof(t_entity), 1);
	if (!monster)
		return (NULL);
	monster->pos = (t_vect){pos.x * ASSET, pos.y * ASSET};
	monster->type = ENEMY;
	monster->life = 1;
	monster->hitbox.top = (t_vect){5, 5};
	monster->hitbox.bot = (t_vect){45, 45};
	monster->f = flying_move;
	monster->next = data->monster;
	data->monster = monster;
	return ((void *)monster);
}

void	flying_move(t_data *data, t_entity *entity)
{
	t_vect	velo;

	velo.x = E_SPEED * ((entity->pos.x - data->player.pos.x < 0) - \
	(entity->pos.x - data->player.pos.x > 0));
	velo.y = E_SPEED * ((entity->pos.y - data->player.pos.y < 0) - \
	(entity->pos.y - data->player.pos.y > 0));
	do_movement(data, entity, velo);
}
