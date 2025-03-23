/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:23:11 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:09 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	select_direction(t_data *data, t_pict *sprt, int *frame, int dir)
{
	static int	prev_dir;

	if (prev_dir != dir)
		*frame = 0;
	merge_image(data->engine.screen, &sprt[dir], \
		data, *frame / FRAME_SPEED % 4);
	*frame += 1;
	prev_dir = dir;
}

void	select_frame(t_data *data, t_pict *sprt)
{
	static int	frame;

	frame = frame % 50;
	if (data->player.acc.x > 0)
		select_direction(data, sprt, &frame, FORW);
	else if (data->player.acc.x < 0)
		select_direction(data, sprt, &frame, BACK);
	else if (data->player.acc.x == 0)
		select_direction(data, sprt, &frame, IDLE);
}
