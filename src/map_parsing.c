/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:38:55 by secros            #+#    #+#             */
/*   Updated: 2024/12/16 18:12:42 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "so_long.h"
#include "fcntl.h"

void	create_map(char *path, t_data *data)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		data->pos[0] = 50;
		data->pos[1] += 32;
		while (str[i])
		{
			if (str[i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->sprite->img1, data->pos[0] , data->pos[1]);
			if (str[i] != '1' && str[i] != ' ' && str[i] != '\n')
				mlx_put_image_to_window(data->mlx, data->win, data->sprite->img2, data->pos[0] , data->pos[1]);
			if (str[i] == 'P')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->sprite->img4, data->pos[0] , data->pos[1]);
				data->player.pos[0] = data->pos[0];
				data->player.pos[1] = data->pos[1];
			}
			if (str[i] == 'C')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->sprite->img3, data->pos[0] , data->pos[1]);
				data->obj.pos[0] = data->pos[0];
				data->obj.pos[1] = data->pos[1];
			}
			if (str[i] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->sprite->img5, data->pos[0] , data->pos[1]);
			if (str[i] != ' ')
				data->pos[0] += 32;
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
}
