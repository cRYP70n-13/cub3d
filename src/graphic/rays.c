#include "../../includes/header.h"

double	distanceBetweenPoints(x1, y1, x2, y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double	rad(double angle)
{
	return (M_PI * angle / 180);
}

double	deg(double angle)
{
	return (180 * angle / M_PI);
}

double  normalize_angle(double angle)
{
	if (fabs(deg(angle)) >= 360)
		angle = (angle < 0 ? -1 : 1) * fmod(fabs(angle), rad(360));
    if (deg(angle) < 0)
		angle += rad(360);
	return (angle);
}

int		vertical(int i)
{
	double xstep = 0;
	double ystep = 0;
	int foundWall = 0;

	g_ray[i].x_intercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	g_ray[i].x_intercept += g_ray[i].isFacingRight ? TILE_SIZE : 0;

	g_ray[i].y_intercept = g_player.y + (g_ray[i].x_intercept - g_player.x) * tan(g_ray[i].rayAngle);

	xstep = TILE_SIZE;
	xstep *= g_ray[i].isFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(g_ray[i].rayAngle);
	ystep *= (g_ray[i].isFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (g_ray[i].isFacingDown && ystep < 0) ? -1 : 1;

	g_ray[i].nextVertTouchX = g_ray[i].x_intercept;
	g_ray[i].nextVertTouchY = g_ray[i].y_intercept;

	// Increment xstep and ystep until we find a wall
	while (g_ray[i].nextVertTouchX >= 0 && g_ray[i].nextVertTouchX <= (g_map->width * TILE_SIZE) && g_ray[i].nextVertTouchY >= 0 && g_ray[i].nextVertTouchY <= (g_map->height * TILE_SIZE)) {
		foundWall = is_wall(g_ray[i].nextVertTouchX + (g_ray[i].isFacingLeft ? -1 : 0), g_ray[i].nextVertTouchY);

		if (foundWall != 0) {
			g_ray[i].vertWallHitX = g_ray[i].nextVertTouchX;
			g_ray[i].vertWallHitY = g_ray[i].nextVertTouchY;
			break ;
		} else {
			g_ray[i].nextVertTouchX += xstep;
			g_ray[i].nextVertTouchY += ystep;
		}
	}
	g_vertHitDistance = (foundWall)
	? distanceBetweenPoints(g_player.x, g_player.y, g_ray[i].vertWallHitX, g_ray[i].vertWallHitY)
	: MAXFLOAT;
	return (foundWall * HIT_V);
}

int		horizontal(int i)
{
	double xstep = 0;
	double ystep = 0;
	int foundWall = 0;
	// ray_angle = fmod(ray_angle, 2 * PI);

	// g_ray[i].rayAngle = g_player.player_angle;
	// g_ray[i].isFacingDown = (g_ray[i].rayAngle >= 0) && (g_ray[i].rayAngle <= PI);
	g_ray[i].isFacingDown = sin(g_ray[i].rayAngle) > 0;
	g_ray[i].isFacingUp = !(g_ray[i].isFacingDown);
	//if ((g_ray[i].rayAngle <= 0.5 * PI) || (g_ray[i].rayAngle >= 1.5 * PI)) {
		g_ray[i].isFacingRight = cos(g_ray[i].rayAngle) > 0;
	//}
	g_ray[i].isFacingLeft = !g_ray[i].isFacingRight;
	g_ray[i].y_intercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	g_ray[i].y_intercept += g_ray[i].isFacingDown ? TILE_SIZE : 0;
	g_ray[i].x_intercept = g_player.x + (g_ray[i].y_intercept - g_player.y) / tan(g_ray[i].rayAngle);
	ystep = TILE_SIZE;
	ystep *= g_ray[i].isFacingUp ? -1 : 1;
	xstep = TILE_SIZE / tan(g_ray[i].rayAngle);
	xstep *= (g_ray[i].isFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (g_ray[i].isFacingRight && xstep < 0) ? -1 : 1;
	g_ray[i].nextHorztX = g_ray[i].x_intercept;
	g_ray[i].nextHorztY = g_ray[i].y_intercept;

	while (g_ray[i].nextHorztX >= 0 && g_ray[i].nextHorztX <= (g_map->width * TILE_SIZE) && g_ray[i].nextHorztY >= 0 && g_ray[i].nextHorztY <= (g_map->height * TILE_SIZE)) {
		foundWall = is_wall(g_ray[i].nextHorztX, g_ray[i].nextHorztY + (g_ray[i].isFacingUp ? -1 : 0));

		if (foundWall != 0) {
			g_ray[i].horztWallHitX = g_ray[i].nextHorztX;
			g_ray[i].horztWallHitY = g_ray[i].nextHorztY;
			break ;
		} else {
			g_ray[i].nextHorztX += xstep;
			g_ray[i].nextHorztY += ystep;
		}
	}

	// Calculate both horizontal and vertical distances and choose the smallest value
	g_horzHitDistance = (foundWall)
		? distanceBetweenPoints(g_player.x, g_player.y, g_ray[i].horztWallHitX, g_ray[i].horztWallHitY)
		: MAXFLOAT;
	return (HIT_H * foundWall);
}

void	cast_rays()
{
	int i = 0;
	int hit;

	g_ray_angle = g_player.player_angle - (FOV / 2);
	g_num_rays = g_map->width * TILE_SIZE;
	g_ray_angle = normalize_angle(g_ray_angle);
	if (!(g_ray = malloc((g_num_rays + 1) * sizeof(t_ray))))
		ft_error_and_quit(2);
	while (i < g_num_rays) {
		g_ray[i].rayAngle = g_ray_angle + (FOV / g_num_rays) * i;
		printf("%lf\n", deg(g_player.player_angle));
		hit = horizontal(i) | vertical(i);
		if ((hit == HIT_HV && g_vertHitDistance < g_horzHitDistance) || hit == HIT_V) {
				g_ray[i].wallHitX = g_ray[i].vertWallHitX;
				g_ray[i].wallHitY = g_ray[i].vertWallHitY;
				g_ray[i].distance = g_vertHitDistance;
		} else {
				g_ray[i].wallHitX = g_ray[i].horztWallHitX;
				g_ray[i].wallHitY = g_ray[i].horztWallHitY;
				g_ray[i].distance = g_horzHitDistance;
		}
		dda(g_player.x + 3, g_player.y + 3, g_ray[i].wallHitX, g_ray[i].wallHitY);
		i++;
	}
}
