#include "../../includes/header.h"

int		deal_key(int keycode, void *param)
{
	(void)param;
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	g_player.walk_up = (keycode == UP_ARROW) ? 1 : 0;
	g_player.walk_down = (keycode == DOWN_ARROW) ? -1 : 0;
	g_player.turn_right = (keycode == RIGHT) ? 1 : 0;
	if(!g_player.turn_right)
		g_player.turn_right = (keycode == LEFT) ? -1 : 0;
	g_player.y = g_player.y + sin(g_player.rotation_angle) * g_player.move_speed * (g_player.walk_up ? g_player.walk_up : g_player.walk_down);
	g_player.x = g_player.x + cos(g_player.rotation_angle) * g_player.move_speed * (g_player.walk_up ? g_player.walk_up : g_player.walk_down);
	g_player.rotation_angle += g_player.rotation_speed * g_player.turn_right;
	render();
	mlx_put_image_to_window(g_mlx->mlx_ptr, g_mlx->win, g_mlx->img.img_ptr, 0, 0);
	return (0);
}
