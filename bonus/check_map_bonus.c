/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:07:57 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 16:17:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

size_t	check_ex_row(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (i);
}

static size_t	check_line(char *str)
{
	size_t	i;

	i = 0;
	if (str[i++] != '1')
		return (0);
	while (str[i] != '\n')
	{
		if (str[i] == '1' || str[i] == 'P' || str[i] == 'C'
			|| str[i] == 'E' || str[i] == '0' || str[i] == 'M')
			i++;
		else
			return (0);
	}
	if (str[i - 1] != '1')
		return (0);
	return (i);
}

int	check_map(char **map)
{
	size_t	len;
	size_t	i;

	i = 1;
	len = check_ex_row(map[0]);
	if (len < 4 || len > 250 || ft_tablen(map) > 250)
		return (1);
	while (map[i] && map[i + 1])
		if (len != check_line(map[i++]))
			return (1);
	if (len != check_ex_row(map[i]))
		return (1);
	return (0);
}

int	check_data(t_data *data, char **map)
{
	size_t		i;
	size_t		j;
	int			count;

	j = 0;
	count = 0;
	data->engine.obj = 0;
	while (map[++j])
	{
		i = 0;
		while (map[j][++i])
		{
			if (map[j][i] == 'P' || map[j][i] == 'C' || map[j][i] == 'M')
				if (set_data(data, (t_vect){i, j}, map[j][i]))
					return (1);
			if (map[j][i] == 'E')
				count++;
		}
	}
	if (data->engine.obj > 0 && count == 1 && data->player.pos.x > 0 \
		&& data->player.pos.y > 0)
		return (0);
	return (1);
}
