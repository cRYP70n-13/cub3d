#include "../../includes/header.h"

void	renderFloor()
{
	ft_square(0, 0, g_map->width * TILE_SIZE, (g_map->height * TILE_SIZE) / 2);
}

void	renderCeiling()
{
	ft_square(0, (g_map->height * TILE_SIZE) / 2, (g_map->width * TILE_SIZE), g_map->height * TILE_SIZE);
}

void	Render3DWall()
{
	int i = 0;
	t_ray ray;
	double correctWallDistance;
	double distanceProjectionPlan;
	double wallStripeHeight;

	renderFloor();
	renderCeiling();
	while (i < g_num_rays)
	{
		ray = g_ray[i];
		correctWallDistance = ray.distance * cos(ray.rayAngle - g_player.rotation_angle);
		distanceProjectionPlan = (g_map->width * TILE_SIZE) / tan(FOV / 2);
		wallStripeHeight = (TILE_SIZE / correctWallDistance) * distanceProjectionPlan;
		ft_square(
			i * wallStripeHeight,
			((g_map->height * TILE_SIZE) / 2) - (wallStripeHeight / 2),
			WALL_STRIP_WIDTH,
			wallStripeHeight);
		i++;
	}
}