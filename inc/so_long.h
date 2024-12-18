/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:25:05 by secros            #+#    #+#             */
/*   Updated: 2024/12/18 17:26:37 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// settings
# define DEFAULT_Y 1080
# define DEFAULT_X 1920
# define TITLE "So long"

// sprite
# define WALL "./sprite/wall.xpm"
# define PLAYER "./sprite/player.xpm"
# define OBJ "./sprite/obj.xpm"
# define CEXIT "./sprite/door.xpm"
# define TILE "./sprite/tile.xpm"

// key map
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESCAPE 65307

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
 typedef struct	s_pict
{
	void	*img;
	char	*addr;
	int		bytes;
	int		l_len;
	int		endian;
}			t_pict;

typedef struct	s_sprite
{
	t_pict	wall;
	t_pict	tile;
	t_pict	obj;
	t_pict	play;
	t_pict	c_ex;
	t_pict	o_ex;
}			t_sprite;

typedef struct s_entity
{
	int				type;
	size_t			pos_x;
	size_t			pos_y;
	int				life;
	struct s_entity *next;
}				t_entity;

typedef struct s_data
{
	t_entity	player;
	void		*mlx;
	void		*win;
	t_sprite	sprite;
	int			w_size[2];
	int			pos[2];
	char		**map;
}		t_data;

//map_parsing
int	map_parsing(t_data *data, char *path);
int	check_map(char **map);
int	check_data(t_data *data, char **map);
int	all_access(t_data *data, char **map);

#endif