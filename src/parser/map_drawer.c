#include "../../includes/header.h"

void	ft_square(double x, double y, int color, int size)
{
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			ft_put_image(j, i, color);
			j++;
		}
		i++;
	}
}

void	ft_put_image(int x, int y, int color)
{
	x *= RATIO;
	y *= RATIO;

	if (x < g_resolution.width && x >= 0 && y < g_resolution.height && y >= 0)
	{
		g_mlx->img.data[y * g_resolution.width + x] = color;
	}
}
