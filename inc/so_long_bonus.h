/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:25:05 by secros            #+#    #+#             */
/*   Updated: 2025/03/23 17:57:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

// settings
# define DEFAULT_Y 1080
# define DEFAULT_X 1920
# define TITLE "So long"

// sprite
# define WALL "./sprite/wall.xpm"
# define WALL2 "./sprite/wall2.xpm"
# define PLAYER "./sprite/test.xpm"//"./sprite/play.xpm"
# define OBJ "./sprite/obj.xpm"
# define CEXIT "./sprite/door.xpm"
# define OEXIT "./sprite/door_o.xpm"
# define TILE "./sprite/tile.xpm"
# define END "./sprite/end.xpm"
# define ENEM "./sprite/enemy.xpm"

//animated sprite
# define I_PLAYER "./sprite/play_i.xpm"
# define F_PLAYER "./sprite/play_f.xpm"
# define B_PLAYER "./sprite/play_b.xpm"
# define U_PLAYER
# define D_PLAYER

// key map
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESCAPE 65307
# define ENTER 65293
# define SPACE 32
# define F_KEY 102
# define SHIFT 65505

// settings
# define MAX_VELOCITY 15
# define FRICTION 0.30
# define ASSET 64
# define FRAME_RATE 16667 // 1000000 / 60
# define FRAME_SPEED 10
# define AGGRO 640
# define E_SPEED 4
# define IMMUNE 20
# define COOLDOWN 30

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "ft_printf.h"
# include <sys/time.h>
# include <math.h>

//Use to identify the entity type;
enum e_type
{
	PLAY,
	ENEMY,
};

//Save the game size selected by the user
enum e_render
{
	LOW,
	MEDIUM,
	HIGH,
	MAX,
};

//Use to select the animation
enum e_anim
{
	IDLE,
	FORW,
	BACK,
	UP,
	DOWN,
};

//Typedef usefull stuct
typedef struct s_vect		t_vect;
typedef struct s_hitbox		t_hitbox;
typedef struct s_pict		t_pict;
typedef struct s_sprite		t_sprite;
typedef struct s_entity		t_entity;
typedef struct s_engine		t_engine;
typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;

//struct for position and movement
struct s_vect
{
	int	x;
	int	y;
};

//hitbox, effective area of entity;
struct s_hitbox
{
	t_vect	top;
	t_vect	bot;
};

//t_pict contain a img pointer and all usefull information about image;
struct s_pict
{
	void	*img;
	char	*addr;
	int		bytes;
	int		l_len;
	int		endian;
	t_vect	size;
};

//t_sprite contain all the texture of viusal element;
struct s_sprite
{
	t_pict	wall;
	t_pict	wall2;
	t_pict	tile;
	t_pict	obj;
	t_pict	play[3];
	t_pict	c_ex;
	t_pict	o_ex;
	t_pict	end;
	t_pict	enemy;
};

//t_entity, all the moving object like player and enemy;
struct s_entity
{
	t_vect		pos;
	t_vect		velo;
	t_vect		acc;
	t_hitbox	hitbox;
	size_t		move;
	int			type;
	int			life;
	t_entity	*next;
	void		(*f)(t_data *, t_entity *);
};

//essential data related to player and the game engine
struct s_engine
{
	int				fly;
	int				jump;
	int				end;
	int				obj;
	int				dodge;
	int				set;
	char			frame;
	struct timeval	time;
	t_pict			screen;
};

//Enssentiel pointer to the mlx element
struct s_mlx
{
	void	*mlx;
	void	*win;
	t_vect	w_size[2];
};

//global struct that contain every information;
struct s_data
{
	t_entity	player;
	t_entity	*monster;
	t_sprite	sprite;
	t_pict		*load;
	t_mlx		mlx_info;
	t_engine	engine;
	char		**map;
};

//settings
void	loading_screen(t_data *data, t_pict *load);
int		launch(t_data *data);
void	load_asset(t_data *data);
int		confirm(t_data *data, int error);
void	change_selection(t_data *data);
void	change_resolution(t_data *data);

//image and screen rendering
void	draw_cursor(t_pict *img, int x, int y);
void	resolution(t_data *data);
void	erease_cursor(t_pict *img, int x, int y);
char	*get_asset(t_data *data, t_vect pos_img);
char	*get_color(t_pict *img, int i, int j, int frame);

//map_parsing
int		map_parsing(t_data *data, char *path);
int		check_map(char **map);
int		check_data(t_data *data, char **map);
int		all_access(t_data *data, char **map);
int		set_data(t_data *data, t_vect pos, char c);
int		set_player(t_data *data, int x, int y);

//enemy
void	*create_monster(t_data *data, t_vect pos);
void	flying_move(t_data *data, t_entity *entity);

//input
int		input(int key, void *param);
int		key_release(int key, t_data *data);
void	end_game(t_data *data);
int		clean_exit(t_data *data, int error);
int		close_button(t_data *data);
int		quit(t_data *data);

//movement
void	movement(t_data *data);
void	do_movement(t_data *data, t_entity *entity, t_vect small_move);

//utils
int		coord_range(t_vect first, t_vect second);
int		absolute(int x);
int		is_in_range(t_hitbox hit_a, t_vect pos_a, t_vect pos_b);

//collision
int		check_collision(t_data *data, t_entity *entity, t_vect velo, char c);
int		check_ground(t_data *data, t_entity *entity, t_hitbox foot, char c);
void	check_pos(t_data *data);

//draw_player
void	select_frame(t_data *data, t_pict *sprt);
void	merge_image(t_pict screen, t_pict *img, t_data *data, int frame);

//generate world
int		game_loop(t_data *param);
void	draw_world(t_data *data, t_vect offset, t_vect offset_pix);
void	world_init(t_data *data);

#endif