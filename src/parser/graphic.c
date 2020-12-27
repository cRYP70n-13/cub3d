#include "../../includes/header.h"
#include "../../includes/structs.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"

/*
 ** This is the function that draws the 3d walls
 ** it uses the dda algorithm to draw a line then
 ** we move from the first ray to the last one drawing
 ** line by line and here we go.
*/
void    ft_3d_walls(float x, float y)
{
  float distance = sqrt(pow((x - g_player.x), 2) + pow((y - g_player.y), 2));
  float correct = distance * cos(player_angle - g_player.rotation_angle);
  float distanceProjectionPlane = (resolution.width / 2) / tan(FOV / 2);
  float stripeHeight = (TAIL_SIZE / correct) * distanceProjectionPlane;

  ft_dda(g_count, resolution.height / 2 - (stripeHeight / 2) - 1, g_count, resolution.height / 2 + (stripeHeight / 2));
}

void ft_dda(float X0, float Y0, float X1, float Y1)
{
	int dx;
	int dy;
	int steps;

	dx = X1 - X0;
	dy = Y1 - Y0;
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
		ft_put_image(Y, X, 0x004800);
		X += (Xinc);													 // increment in x at each step
		Y += (Yinc);													 // increment in y at each step
		i++;
	}
}