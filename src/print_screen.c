/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:31:51 by secros            #+#    #+#             */
/*   Updated: 2025/01/07 08:18:51 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*display(t_data *data)
{
	static t_pict	img;
	void			*prev;
	int				x[2];

	x[1] = 0;
	x[0] = 0;
	prev = NULL;
	if (img.img)
		prev = img.img;
	img.img = mlx_new_image(data->mlx, DEFAULT_X, DEFAULT_Y);
	if (!img.img && prev)
		return (mlx_destroy_image(data->mlx, prev), NULL);
	else if (!img.img)
		return (NULL);
	img.addr = mlx_get_data_addr(img.img, &img.bytes, &img.l_len, &img.endian);
	
	mlx_put_image_to_window(data->mlx, data->win, img.img ,0 ,0);
	if (prev)
		mlx_destroy_image(data->mlx, prev);
}

void	print_screen(t_data *data, t_pict *img)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = data->player.pos_x / 64;
	y = data->player.pos_y / 64;
	while (data->map[1][x + i] != '\n' && data->map[1][x + i] != '/0')
		i++;
	if (i * 64 < DEFAULT_X / 2)
		x = x - (DEFAULT_X / 128 - i);
	print_background(data, img, 0, 0);
	print_wall();
	print_content();
}

void	print_background(t_data *data, t_pict *img, int x, int y)
{

}