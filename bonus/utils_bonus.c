/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:44:01 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:18:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	absolute(int x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

int	coord_range(t_vect first, t_vect second)
{
	long	x;
	long	y;

	x = absolute(first.x - second.x);
	y = absolute(first.y - second.y);
	return ((int) sqrt((x * x) + (y * y)));
}

int	is_in_range(t_hitbox hit_a, t_vect pos_a, t_vect pos_b)
{
	if (pos_b.x >= (pos_a.x + hit_a.top.x)
		&& pos_b.x <= (pos_a.x + hit_a.bot.x))
		if (pos_b.y >= (pos_a.y + hit_a.top.y)
			&& pos_b.y <= (pos_a.y + hit_a.bot.y))
			return (1);
	return (0);
}
