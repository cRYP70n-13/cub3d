#include "../../includes/header.h"

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
		// if (i == 0) {
		// 	printf("%f || %f", X * RATIO, Y * RATIO);
		// 	exit(EXIT_FAILURE);
		// }
		ft_put_image(X * RATIO, Y * RATIO, 0x004800);
		X += (Xinc);													 // increment in x at each step
		Y += (Yinc);													 // increment in y at each step
		i++;
	}
}