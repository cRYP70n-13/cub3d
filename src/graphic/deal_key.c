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
	g_player.new_y = g_player.y + sin(g_player.rotation_angle) * g_player.move_speed * (g_player.walk_up ? g_player.walk_up : g_player.walk_down);
	g_player.new_x = g_player.x + cos(g_player.rotation_angle) * g_player.move_speed * (g_player.walk_up ? g_player.walk_up : g_player.walk_down);
	// printf("%f ||| %f\n", g_player.new_x, g_player.new_y);
	g_player.rotation_angle += g_player.rotation_speed * g_player.turn_right;
	render();
	mlx_put_image_to_window(g_mlx->mlx_ptr, g_mlx->win, g_mlx->img.img_ptr, 0, 0);
	return (0);
}

// The graphics Part
int		is_wall(float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || y < 0)
		return (1);
	map_grid_index_x = (int)(x / TILE_SIZE);
	map_grid_index_y = (int)(y / TILE_SIZE);

	if (g_map->map_2d[map_grid_index_y][map_grid_index_x] == '1')
		return (1);
	return (0);
}