/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:39:03 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/21 18:39:07 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include "../../includes/structs.h"
#include "../utils/libft/libft.h"

void player_init()
{
	g_player.x = (_map->width * TAIL_SIZE) / 1.40;
	g_player.y = (_map->height * TAIL_SIZE) / 2;
	g_player.rotation_angle = PI / 2.0;
	g_player.move_speed = 3.0;
	g_player.rotation_speed = 0.1;
}

int key_pressed(int keycode)
{
	if (keycode == UP_ARROW)
		g_player.walk_up = 1;
	if (keycode == DOWN_ARROW)
		g_player.walk_up= -1;
	if (keycode == RIGHT_ARROW)
		g_player.turn_right = 1;
	if (keycode == LEFT_ARROW)
		g_player.turn_right = -1;
	return (0);
}

int key_released(int keycode)
{
	if (keycode == UP_ARROW || keycode == DOWN_ARROW)
		g_player.walk_up = 0;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
		g_player.turn_right = 0;
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	g_player.new_y = 0;
	g_player.new_x = 0;
	return (0);
}

int deal_key()
{
	// The up and down keys
	g_player.new_y = g_player.y + sin(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up;
	g_player.new_x = g_player.x + cos(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up;

	if (!is_wall(g_player.new_x, g_player.new_y, 2.5, 2.5))
	{
		g_player.x = g_player.new_x;
		g_player.y = g_player.new_y;
	}
	// The left and right keys
	g_player.rotation_angle -= g_player.rotation_speed * g_player.turn_right;

	draw_map();
	return (0);
}

// TODO: Implement the arrow keys to move the direction of the player
int loop_key()
{
	mlx_hook(g_mlx->win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(g_mlx->win_ptr, 3, 0, key_released, 0);
	deal_key();
	mlx_put_image_to_window(g_mlx->mlx_ptr, g_mlx->win_ptr, g_mlx->img.img_ptr, 0, 0);
	return (0);
}
