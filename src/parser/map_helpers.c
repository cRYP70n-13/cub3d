/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:39:23 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/23 17:34:56 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"

/*
 ** NOTE: Here in this function I render the rays we have 60 deg in FOV
 ** so i start with 0deg till we achieve 60 which is the FOV
 ** Then we check if we have a wall or not, if yes we return else
 ** we keep going
*/
void dda(float X0, float Y0, float X1, float Y1)
{
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps;

	steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy);
	// calculate increment in x & y for each steps
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	int i = 0;
	while (i < steps)
	{
    // So this check here means that we found a wall then we call the ft_3d_walls function
		if (((int)X % TAIL_SIZE == 0 || (int)X % TAIL_SIZE == TAIL_SIZE - 1 || (int)Y % TAIL_SIZE == 0 || (int)Y % TAIL_SIZE == TAIL_SIZE - 1) && (is_wall(X, Y, Xinc, Yinc)))
		{
			ft_3d_walls(X, Y);
			return ;
		}
		ft_put_image(Y * RATIO, X * RATIO, 0x004800);
		X += (Xinc / 10);													 // increment in x at each step
		Y += (Yinc / 10);													 // increment in y at each step
		i++;
	}
}

void draw_map()
{
	int i = 0;
	int j;
	int x = 0;
	int y = 0;
	int color = 0;

	g_player.renderer_x = g_player.new_x + cos(g_player.rotation_angle) * 40; // Renderer of x depending on the position of the plaer and where the player moves
	g_player.renderer_y = g_player.new_y + sin(g_player.rotation_angle) * 40; // Renderer of y depending on the position of the plaer and where the player moves

	while (i < _map->height)
	{
		j = 0;
		while (j < _map->width)
		{
			x = j * TAIL_SIZE;
			y = i * TAIL_SIZE;

			if (_map->map_2d[i][j] == '1') {
				color = 0xFF0000; // RED color
			} else if (_map->map_2d[i][j] == ' ') {
				color = 0x0000ff; // BLUE color
			} else if (_map->map_2d[i][j] == '0'){
				color = 0x00FF00; // GREEN color
			} else if (_map->map_2d[i][j] == 'N'){
				// Here I should call the draw player function to set it in teh right place
			}
			ft_square(x, y, color, TAIL_SIZE);
			j++;
		}
		i++;
	}
	ft_square(g_player.x, g_player.y, 0x000000, 6);
	dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
	// field_of_view();
}

void	draw_player(int *i, int *j)
{
	// TODO: Implement it ...
	*i = 0;
	*j = 0;
}

void	field_of_view(void)
{
	player_angle = g_player.rotation_angle - (FOV / 2.0);
	g_count = 0;

	while (player_angle <= g_player.rotation_angle + (FOV / 2.0))
	{
		g_player.renderer_x = g_player.new_x + cos(player_angle) * INT16_MAX; // Renderer of x depending on the position of the plaer and where the player moves
		g_player.renderer_y = g_player.new_y + sin(player_angle) * INT16_MAX; // Renderer of y depending on the position of the plaer and where the player moves
		player_angle += FOV / resolution.width;
		g_count++;
		dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
	}
}
