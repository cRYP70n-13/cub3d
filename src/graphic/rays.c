#include "../../includes/header.h"

void	normalize_angle(int i)
{
	g_ray[i].rayAngle = fmod(g_ray[i].rayAngle, (2 * PI));
	if (g_ray[i].rayAngle < 0) {
		g_ray[i].rayAngle = 2 * PI + g_ray[i].rayAngle;
	}
}

float	distanceBetweenPoints(x1, y1, x2, y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	cast_rays()
{
	const int num_rays = (g_map->width * TILE_SIZE) / WALL_STRIP_WIDTH;
	float xstep = 0;
	float ystep = 0;

	/**
	 * @brief -> checking for the horizontal intersections
	 * @param -> {*} the ray
	 * @return -> {*} none because everything is global
	 */
	if (!(g_ray = malloc(num_rays * sizeof(t_ray))))
		ft_error_and_quit(2);
	float ray_angle = g_player.rotation_angle - (FOV / 2);
	int i = 0;
	normalize_angle(i);
	while (i <= 1) {
		g_ray[i].rayAngle = ray_angle + (FOV / num_rays) * i;
		g_ray[i].isFacingDown = (g_ray[i].rayAngle > 0) && (g_ray[i].rayAngle < PI);
		g_ray[i].isFacingUp = !g_ray[i].isFacingDown;

		if ((g_ray[i].rayAngle < 0.5 * PI) || (g_ray[i].rayAngle > 1.5 * PI)) {
			g_ray[i].isFacingRight = 1;
		} else {
			g_ray[i].isFacingLeft = 1;
		}

		g_ray[i].y_intercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
		g_ray[i].y_intercept += g_ray[i].isFacingDown ? TILE_SIZE : 0;
		g_ray[i].x_intercept = g_player.x + (g_ray[i].y_intercept - g_player.y) / tan(g_ray[i].rayAngle);
		printf("%f\n", g_ray[i].rayAngle);

		ystep = TILE_SIZE;
		ystep *= g_ray[i].isFacingUp ? -1 : 1;

		xstep = TILE_SIZE / tan(g_ray[i].rayAngle);
		xstep *= (g_ray[i].isFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (g_ray[i].isFacingRight && xstep < 0) ? -1 : 1;

		g_ray[i].nextHorztX = g_ray[i].x_intercept;
		g_ray[i].nextHorztY = g_ray[i].y_intercept;

		while (g_ray[i].nextHorztX >= 0 && g_ray[i].nextHorztX <= (g_map->width * TILE_SIZE) && g_ray[i].nextHorztY >= 0 && g_ray[i].nextHorztY <= (g_map->height * TILE_SIZE)) {
			int isItWall = is_wall(g_ray[i].nextHorztX, g_ray[i].nextHorztY - (g_ray[i].isFacingUp ? 1 : 0)); 

			if (isItWall) {
				g_ray[i].horztWallHitX = g_ray[i].nextHorztX;
				g_ray[i].horztWallHitY = g_ray[i].nextHorztY;
				break ;
			} else {
				g_ray[i].nextHorztY += ystep;
				g_ray[i].nextHorztX += xstep;
			}
		}

		/**
		 * @brief -> checking for the vertical intersections
		 * @param -> {*} the ray
		 * @return -> {*} none because everything is global
		 */

		// ========= THE VERTICAL INTERSECTION ==========
		// Find the x-coordinate of the closest vertical grid intersenction
		g_ray[i].x_intercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
		g_ray[i].x_intercept += g_ray[i].isFacingRight ? TILE_SIZE : 0;

		// Find the y-coordinate of the closest vertical grid intersection
		g_ray[i].y_intercept = g_player.y + (g_ray[i].x_intercept - g_player.x) * tan(g_ray[i].rayAngle);

		// Calculate the increment xstep and ystep
		xstep = TILE_SIZE;
		xstep *= g_ray[i].isFacingLeft ? -1 : 1;

		ystep = TILE_SIZE * tan(g_ray[i].rayAngle);
		ystep *= (g_ray[i].isFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (g_ray[i].isFacingDown && ystep < 0) ? -1 : 1;

		g_ray[i].nextVertTouchX = g_ray[i].x_intercept;
		g_ray[i].nextVertTouchY = g_ray[i].y_intercept;

		// Increment xstep and ystep until we find a wall
		while (g_ray[i].nextVertTouchX >= 0 && g_ray[i].nextVertTouchX <= (g_map->width * TILE_SIZE) && g_ray[i].nextVertTouchY >= 0 && g_ray[i].nextVertTouchY <= (g_map->height * TILE_SIZE)) {
			int foundWall = is_wall(g_ray[i].nextVertTouchX + (g_ray[i].isFacingLeft ? -1 : 0), g_ray[i].nextVertTouchY);

		    if (foundWall != 0) {
		        g_ray[i].vertWallHitX = g_ray[i].nextVertTouchX;
		        g_ray[i].vertWallHitY = g_ray[i].nextVertTouchY;
		        break ;
		    } else {
		        g_ray[i].nextVertTouchX += xstep;
		        g_ray[i].nextVertTouchY += ystep;
		    }
		}

		dda(g_player.x + 3, g_player.y + 3, g_ray[i].horztWallHitX, g_ray[i].horztWallHitY);
		i++;
	}
}
