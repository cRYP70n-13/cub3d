/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:02:44 by okimdil           #+#    #+#             */
/*   Updated: 2020/03/12 20:34:48 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		abs(int n)
{
    return ((n > 0) ? n : (n * (-1)));
}

int		is_wall(float x, float y)
{
	float map_grid_index_x;
	float map_grid_index_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (1);
	map_grid_index_x = floor(x / TAIL_SIZE);
	map_grid_index_y = floor(y / TAIL_SIZE);
	return (map[(int)map_grid_index_x][(int)map_grid_index_y] != 0);
}

void	dda(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    // calculate steps required for generating pixels
    int		steps;

	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    // calculate increment in x & y for each steps
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    // Put pixel for each step
    float X = X0;
    float Y = Y0;
	int i = 0;
    while( i <= steps)
    {
		mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, X, Y, 0x0000FF); //  Put pixel at X and Y
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
		i++;
    }
}

void	ft_square(int x, int y, int color, int size)
{
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			mlx_pixel_put(g_mlx.mlx_ptr, g_mlx.win_ptr, j, i, color);
			j++;
		}
		i++;
	}
}

void	struct_init()
{
	g_player.x = WINDOW_WIDTH / 2;
	g_player.y = WINDOW_HEIGHT / 2;
	g_player.rotation_angle = PI / 2.0;
	g_player.move_speed = 4.0;
	g_player.rotation_speed = 0.1;
}

int		deal_key()
{
	if (g_player.walk_up == 1) // UP_ARROW
	{
		g_player.y += sin(g_player.rotation_angle) * 3;
		g_player.x += cos(g_player.rotation_angle) * 3;
	}
	if (g_player.walk_down == 1) // DOWN_ARROW
	{
		g_player.y -= sin(g_player.rotation_angle) * 3;
		g_player.x -= cos(g_player.rotation_angle) * 3;
	}
	if (g_player.turn_left == 1) // LEFT_ARROW
		g_player.rotation_angle -= g_player.rotation_speed;
	if (g_player.turn_right == 1) // RIGHT_ARROW
		g_player.rotation_angle += g_player.rotation_speed;
	draw_map();
	return (0);
}

int		key_pressed(int keycode)
{
	if (keycode == UP_ARROW)
		g_player.walk_up = 1;
	if (keycode == DOWN_ARROW)
		g_player.walk_down = 1;
	if (keycode == RIGHT_ARROW)
		g_player.turn_right = 1;
	if (keycode == LEFT_ARROW)
		g_player.turn_left = 1;
	return (0);
}

int		key_released(int keycode)
{
	if (keycode == UP_ARROW)
		g_player.walk_up = 0;
	if (keycode == DOWN_ARROW)
		g_player.walk_down = 0;
	if (keycode == RIGHT_ARROW)
		g_player.turn_right = 0;
	if (keycode == LEFT_ARROW)
		g_player.turn_left = 0;
	return (0);
}

int		loop_key()
{
    mlx_hook(g_mlx.win_ptr, 2, 0, key_pressed, 0);
    mlx_hook(g_mlx.win_ptr, 3, 0, key_released, 0);
    deal_key();
    return (0);
}

void	draw_map()
{
	g_player.renderer_x = g_player.x + cos(g_player.rotation_angle) * 40; // Renderer of x depending on the position of the plaer and where the player moves
	g_player.renderer_y = g_player.y + sin(g_player.rotation_angle) * 40; // Renderer of y depending on the position of the plaer and where the player moves
	int		i = 0;
	int		j;
	int		x = 0;
	int		y = 0;
	int		color = 0;

	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			x = j * TAIL_SIZE;
			y = i * TAIL_SIZE;
			color = map[i][j] == 1 ? 0x000000 : 0xffffff;
			ft_square(x, y, color, 50);
			j++;
		}
		i++;
	}
	ft_square(g_player.x, g_player.y, 0xff0000, 6);
	dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
	
}

int		main(void)
{
	g_mlx.mlx_ptr = mlx_init(); //Connection to the graphic server
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, (MAP_NUM_COLS * TAIL_SIZE), (MAP_NUM_ROWS * TAIL_SIZE), "cRYP70N"); //initialize the window
	struct_init();
	draw_map();
	mlx_loop_hook(g_mlx.mlx_ptr, loop_key, (void *)0);
	mlx_loop(g_mlx.mlx_ptr); //evnets loop
	return (0);
}
