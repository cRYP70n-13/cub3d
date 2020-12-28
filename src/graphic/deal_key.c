#include "../includes/header.h"

void	deal_key(int keycode, void *fasi)
{
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	g_player.walk_up = (keycode == UP_ARROW) ? 1 : 0;
	g_player.walk_up = (keycode == DOWN_ARROW) ? -1 : 0;
	g_player.turn_right = (keycode == RIGHT_ARROW) ? 1 : 0;
	g_player.turn_right = (keycode == LEFT_ARROW) ? -1 : 0;
	g_player.new_y = g_player.y + sin(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up;
	g_player.new_x = g_player.x + cos(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up ;
	g_player.rotation_angle -= g_player.rotation_speed * g_player.turn_right;
}