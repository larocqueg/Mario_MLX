/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:04:31 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef game_H
# define game_H
# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"
# include <strings.h>
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

# define SCREEN_SIZE_X 854
# define SCREEN_SIZE_Y 480
# define SCALE 2
# define SIDESCROLL true

//# define SCREEN_SIZE_X 1920
//# define SCREEN_SIZE_Y 1080
//# define SCALE 4

# define LINE_COLOR 0xFFFF00
# define MOVE_SPEED 4.0
# define TILE_SIZE 16
# define ACCEL 8
# define RUNNING_ACCEL 10
# define FRICTION 70
# define MAX_SPEED 8
# define MAX_RUNNING_SPEED 10
# define JUMP_SPEED 8.9
# define GRAVITY 30
# define ENEMY_SPEED 2.1f

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef enum	s_state
{
	WALKING,
	IDLE,
	RUNNING,
	JUMPING,
	STOPPING,
	FALLING,
	DEATH,
	CLIMBING
} t_state;

typedef enum	s_time
{
	LOOP,
	ONE_SHOT,
} t_time;

typedef enum	s_tile
{
	TOPLEFT,
	LEFT,
	TOPRIGHT,
	RIGHT
} t_tile;
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_image;

typedef enum	e_enemy_type
{
	GOOMBA,
} t_enemy_type;

typedef struct s_enemy
{
	bool		started;
	bool		left;
	t_point		pos;
	bool		stopped;
	bool		is_on_ground;
	bool		exist;
	t_point		direction;
	float		gravity;
	float		despawn;
	bool 		collision;
	bool		outofgame;

}	t_enemy;

typedef struct s_frames
{
	t_image		frames[10];
	int			frame_count;
}	t_frames;

typedef struct s_collision
{
	bool	left;
	bool	right;
	bool	down;
	bool	up;
	bool	is_colliding;
} t_collision;

typedef struct s_player
{
	t_point		pos;
	t_point		direction;
	t_point		velocity;
	t_point		hit;
	float		hit_cooldown;
	bool		hit_block;
	bool		jump;
	bool		is_on_ground;
	bool		big;
	bool		left;
	bool		running;
	bool		holding;
	bool		falling;
	bool		dying;
	t_state		animation_state;
	t_frames	walking;
	t_frames	jumping;
	t_frames	down;
	t_frames	idle;
	t_frames	stopping;
	t_frames	death;
	t_frames	climbing;
	int			current_frame;

}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			fd;
	int			map_height;
	int			map_width;
	t_image		ground;
	t_image		brick;
	t_image		background;
	t_image		powerup[3];
	t_image		stairs;
	t_image		goomba[3];
	t_image		pipe[4];
	t_image		cloud[3];
	t_image		grass[3];
	t_image		hill;
	t_image 	castle;
	t_image		title_screen;
	t_image		little_hill;
	t_image		selector;
	t_image		flag;
	t_enemy		goombas[32];
	int			goomba_count;
	long long	last_frame_time;
	float		delta;
	t_player	player;
	t_player	player2;
	float		flag_pos;
	float		castle_pos;
	float		cameraX;
	t_image		image;
	int			power_up_frames;
	bool		started;
	bool		ended_p1;
	bool		ended_p2;
	bool		multiplayer;
}	t_game;

int			free_displays(t_game *game);
void		init_window(t_game *game);

void	animation_player(t_game *game, t_frames *anim, int type);

//gameloop
int			game_loop(t_game *game);
void		calculate_Delta(t_game *game);

//init
void		game_init(t_game *game);
void		get_textures(t_game *game);
char		get_tile(t_game *game, int x, int y);

//input
int			key_pressed(int keysym, t_game *game);
int			key_released(int keysym, t_game *game);


//animations
void	animation_times(t_game *game);
//map
int			ft_load_map(char *map, t_game *game);
void		drawmap(t_game *game);
int	 		ft_load_images(t_game *game, t_image *image, char *name);

//render utils
void		drawrect(t_image *image, t_point pos, t_point size, int color);
void		ft_pixelput(t_image *data, int x, int y, int color);
void	drawplayer(t_game *game, t_point pos, t_image *text, float scale, bool left, bool flip);
void		drawtexture(t_game *game, t_point pos, t_image *text, float scale);


//struct utils
int			check_args(char *str);
void		get_player_pos(t_game *game);

//math
int			ft_abs(int num);
long long	get_time(void);
float		clamp(float value, float min, float max);
t_point		normalize(t_point point);
void		animation_player2(t_game *game, t_frames *anim, int type);
void	move_player_2(t_game *game);
float 		move_towards(float start, float goal, float step);
char		get_tile(t_game *game, int x, int y);
bool 		is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB);
//free utils;
void		ft_free_arr(char **arr);
t_point		get_mouse_position(t_game *game);

//move
void		move_camera(t_game *game);
void		move(t_game *game);
void		move_enemies(t_game *game);

//debug
void		debug_directions(t_game *game);

#endif
