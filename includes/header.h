/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:03:19 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/09 13:22:37 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../../../../Documents/dev/cub3d_DONE/mlxopengl/mlx.h"

# define TAIL_SIZE 21
# define PI 3.14159265358979323846

// The keys datastructures
# define UP_ARROW 13
# define DOWN_ARROW 1
# define LEFT_ARROW 0
# define RIGHT_ARROW 2
# define ESCAPE 53

// The raycasting data structures
# define FOV 60 * (PI / 180)


// Just the absolute value to run as fast as possible
# define ABS(N) ((N<0)?(-N):(N))

void	draw_map();
void	dda(int X0, int Y0, int X1, int Y1);
void	ft_square(int x, int y, int color, int size);
void	player_init();
int		deal_key();
int		key_pressed(int keycode);
int		key_released(int keycode);
int		loop_key();
void	field_of_view(void);
int		is_wall(float x, float y, float Xinc, float Yinc);
void	parse_textures(char *line, int type);
int		wall_conditions(s_map *_map, int *i, int *j);
void	initial_structs(s_map *_map);
void	check_map(char *line, s_map *_map);
void	fill_line(char *line, s_map *_map);
void	map_manager(s_map *_map);
void	ft_put_image(int x, int y, int color);

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
}				t_img;

/*
 ** Here is my main struct containing every variables needed by the MLX.
 ** - mlx_ptr stores the return value of mlx_init
 ** - win stores the return value of mlx_new_window
 ** - img will store everything we need for the image part, the struct is described above.
*/
typedef struct	s_mlx
{
	void	*win_ptr;
	void	*mlx_ptr;
	t_img	img;
}				t_mlx;

typedef struct s_player
{
	float	x;
	float	y;
	float	new_x;
	float	new_y;
	float	renderer_x;
	float 	renderer_y;
	int		walk_up;
	int		walk_down;
	int		turn_left;
	int		turn_right;
	float	rotation_angle; // the rotation angle is PI / 2;
	float	move_speed; // by def to 3.0
	float	rotation_speed; // the rot speed is 3 * (PI / 180);
}			t_player;

t_mlx	*g_mlx;
t_player g_player;
s_map *_map;
s_resolution resolution;

#endif