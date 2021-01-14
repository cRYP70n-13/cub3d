#ifndef _HEADER_H
# define _HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "structs.h"
# include "get_next_line.h"
# include "../src/utils/Errors/errors.h"
# include "../src/utils/libft/libft.h"
// # include "../../../../Documents/dev/cub3d_DONE/mlxopengl/mlx.h"
# include <mlx.h>

# define TILE_SIZE 32
# define PI M_PI

# define UP_ARROW 13
# define DOWN_ARROW 1
# define LEFT_ARROW 0
# define RIGHT_ARROW 2
# define RIGHT 124
# define LEFT 123
# define ESCAPE 53

# define FOV 60 * (PI / 180)
# define WALL_STRIP_WIDTH 1
# define RATIO 0.5
# define HIT_V 1
# define HIT_H 2
# define HIT_HV 3

# define ABS(N) ((N<0)?(-N):(N))

void	draw_map(void);
void	draw_player(void);
void	dda(double X0, double Y0, double X1, double Y1);
void	ft_square(double x, double y, int color, int size);
void	player_init(void);
int		deal_key(int keycode, void *);
int		key_pressed(int keycode);
int		key_released(int keycode);
int		loop_key(void);
int		is_wall(double x, double y);
void	parse_textures(char *line, int type);
int		wall_conditions(t_map *g_map, int *i, int *j);
void	initial_structs(t_map *g_map);
void	check_map(char *line, t_map *g_map);
void	fill_line(char *line, t_map *g_map);
void	map_manager(t_map *g_map);
void	ft_put_image(int x, int y, int color);
void  	ft_dda(double X, double Y, double X1, double Y1);
void  	ft_3d_walls(double x, double y);
int		parsing(char **argv);
void	graphic(void);
void	render(void);
void	init(void);
void	cast_rays();
void renderFloor();
void renderCeiling();
void Render3DWall();
double	normalize_angle(double angle);

/*
 ** Here I built a struct of the MLX image :
 ** It contains everything I need.
 ** - img_ptr to store the return value of mlx_new_image
 ** - data to store the return value of mlx_get_data_addr
 ** - the 3 other variables are pretty much useless, but I'll need
 ** them in the prototype of mlx_get_data_addr (man page says so)
*/
typedef struct s_img
{
	void	*img_ptr;
	int 	*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		count;
}				t_img;

/*
 ** Here is my main struct containing every variables needed by the MLX.
 ** - mlx_ptr stores the return value of mlx_init
 ** - win stores the return value of mlx_new_window
 ** - img will store everything we need for the image part, the struct is described above.
*/
typedef struct	s_mlx
{
	void	*win;
	void	*mlx_ptr;
	t_img	img;
}				t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	double	new_x;
	double	new_y;
	double	renderer_x;
	double 	renderer_y;
	int		walk_up;
	int		walk_down;
	int		turn_right;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
	double	player_angle;
}			t_player;

typedef struct s_ray
{
	double x_intercept;
	double y_intercept;
	int		isFacingDown;
	int		isFacingUp;
	int		isFacingLeft;
	int		isFacingRight;
	double	rayAngle;
	double	nextHorztY;
	double	nextHorztX;
	double	horztWallHitX;
	double	horztWallHitY;
	double	vertWallHitX;
	double	vertWallHitY;
	double	nextVertTouchX;
	double	nextVertTouchY;
	double	wallHitX;
	double	wallHitY;
	double	distance;
}				t_ray;

t_mlx	*g_mlx;
t_player g_player;
t_map *g_map;
t_resolution g_resolution;
t_img	g_img;
t_ray	*g_ray;
double g_num_rays;
double g_vertHitDistance;
double g_horzHitDistance;
double g_ray_angle;

#endif
