#include "../../includes/header.h"

/*
 ** NOTE: Here in this function I render the rays we have 60 deg in FOV
 ** so i start with 0deg till we achieve 60 which is the FOV
 ** Then we check if we have a wall or not, if yes we return else
 ** we keep going
*/
void dda(double X0, double Y0, double X1, double Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	int steps;

	steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy);
	double Xinc = dx / (double)steps;
	double Yinc = dy / (double)steps;

	double X = X0;
	double Y = Y0;
	int i = 0;
	while (i < steps)
	{
		ft_put_image(X * RATIO, Y * RATIO, 0x004800);
		X += (Xinc);
		Y += (Yinc);
		i++;
	}
}