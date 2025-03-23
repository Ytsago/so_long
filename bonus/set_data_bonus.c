/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:11:42 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:18:07 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	set_player(t_data *data, int x, int y)
{
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
	{
		data->player.pos.x = x * ASSET;
		data->player.pos.y = y * ASSET;
		data->player.hitbox.top = (t_vect){10, 15};
		data->player.hitbox.bot = (t_vect){49, 57};
		return (0);
	}
	return (1);
}

int	set_data(t_data *data, t_vect pos, char c)
{
	if (c == 'P')
		if (set_player(data, pos.x, pos.y))
			return (1);
	if (c == 'C')
		data->engine.obj++;
	if (c == 'M')
		if (!create_monster(data, pos))
			return (1);
	return (0);
}
