/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:25:05 by secros            #+#    #+#             */
/*   Updated: 2024/12/16 18:11:44 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define DEFAULT_Y 1080
# define DEFAULT_X 1920

# include "mlx.h"
# include "mlx_int.h"

/* typedef struct	s_pict
{
	void	*img;
	char	*addr;
	int		bytes;
	int		l_len;
	int		endian;
}			t_pict;
 */
typedef struct	s_sprite
{
	void	*img1;
	void	*img2;
	void	*img3;
	void	*img4;
	void	*img5;
}			t_sprite;

typedef struct s_entity
{
	int				type;
	int				pos[2];
	int				life;
	struct s_entity *next;
}				t_entity;

typedef struct s_data
{
	t_entity	player;
	t_entity	obj;
	void		*mlx;
	void		*win;
	t_sprite	*sprite;
	int			w_size[2];
	int			pos[2];
}		t_data;

void	create_map(char *path, t_data *data);

#endif