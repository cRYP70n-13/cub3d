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

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "structs.h"
# include "mlx.h"

# define TAIL_SIZE 42
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15
# define PI 3.14159265358979323846
# define WINDOW_WIDTH (MAP_NUM_COLS * TAIL_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TAIL_SIZE)
# define UP_ARROW 13
# define DOWN_ARROW 1
# define LEFT_ARROW 0
# define RIGHT_ARROW 2
# define ESCAPE 53
# define ABS(N) ((N<0)?(-N):(N))

s_map *my_map;

void	draw_map();
void	dda(int X0, int Y0, int X1, int Y1);
void	ft_square(int x, int y, int color, int size);
void	struct_init();
int		deal_key();
int		key_pressed(int keycode);
int		key_released(int keycode);
int		loop_key();


// TODO: and this structures is noow useless I have to bring it from my parser return
int		map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		};


// The MLX structure to make it up and running
typedef struct	s_mlx
{
	void	*win_ptr;
	void	*mlx_ptr;
}				t_mlx;

typedef struct s_player
{
	float x;
	float y;
	float new_x;
	float new_y;
	float renderer_x;
	float renderer_y;
	int		walk_up;
	int		walk_down;
	int		turn_left;
	int		turn_right;
	float rotation_angle; // the rotation angle is PI / 2;
	float move_speed; // by def to 3.0
	float rotation_speed; // the rot speed is 3 * (PI / 180);
}			t_player;

// TODO: Those are global structures I need to make them pointers of structures for sake of performance
t_mlx	g_mlx;
t_player g_player;

#endif
