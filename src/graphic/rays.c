#include "../../includes/header.h"

void	cast_rays()
{
	const int num_rays = (g_map->width * TILE_SIZE) / WALL_STRIP_WIDTH;

	if (!(g_ray = malloc(num_rays * sizeof(t_ray))))
		ft_error_and_quit(2);

	int i = 0;
	while (i <= 1) {
		g_ray[i].rayAngle = g_player.rotation_angle - (FOV / 2);
		g_ray[i].isFacingDown = g_ray[i].rayAngle > 0 && g_ray[i].rayAngle < PI;
		g_ray[i].isFacingUp = !g_ray[i].isFacingDown;
		printf("Facing Up || %d\n", g_ray[i].isFacingUp);

		if ((g_ray[i].rayAngle < 0.5 * PI) || (g_ray[i].rayAngle > 1.5 * PI)) {
			g_ray[i].isFacingRight = 1;
		} else {
			g_ray[i].isFacingLeft = 1;
		}
		printf("Facing Left ||%d\n", g_ray[i].isFacingLeft);

		g_ray[i].y_intercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
		g_ray[i].y_intercept += g_ray[i].isFacingDown ? TILE_SIZE : 0;
		g_ray[i].x_intercept = g_player.x + (g_ray[i].y_intercept - g_player.y) / tan(g_ray[i].rayAngle);
		g_ray[i].rayAngle += FOV / num_rays;
		dda(g_player.x, g_player.y, g_ray[i].x_intercept, g_ray[i].y_intercept);
		i++;
	}
}
