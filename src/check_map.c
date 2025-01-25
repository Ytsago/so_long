/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:07:57 by secros            #+#    #+#             */
/*   Updated: 2025/01/26 00:29:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ex_row(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (i);
}

static int	check_line(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '1')
		return (0);
	while (str[i] != '\n')
	{
		if (str[i] == '1' || str[i] == 'P' || str[i] == 'C'
			|| str[i] == 'E' || str[i] == '0')
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
	int	len;
	int	i;

	i = 1;
	len = check_ex_row(map[0]);
	if (len < 4 || len > 1000 || ft_tablen(map) > 1000)
		return (1);
	while (map[i] && map[i + 1])
		if (len != check_line(map[i++]))
			return (1);
	if (len != check_ex_row(map[i]))
		return (1);
	return (0);
}

static int	set_player(t_data *data, int x, int y)
{
	if (data->player.pos_x == 0 && data->player.pos_y == 0)
	{
		data->player.pos_x = x * 64;
		data->player.pos_y = y * 64;
		return (0);
	}
	return (1);
}

int	check_data(t_data *data, char **map)
{
	int		i;
	int		j;
	int		count;

	j = 0;
	count = 0;
	data->obj = 0;
	while (map[++j])
	{
		i = 0;
		while (map[j][++i])
		{
			if (map[j][i] == 'P')
				if (set_player(data, i, j))
					return (1);
			if (map[j][i] == 'C')
				data->obj++;
			if (map[j][i] == 'E')
				count++;
		}
	}
	if (data->obj > 0 && count == 1)
		return (0);
	return (1);
}
