#include "../../includes/header.h"

void	field_of_view(void)
{
	player_angle = g_player.rotation_angle - (FOV / 2.0);
	g_count = 0;

	while (player_angle <= g_player.rotation_angle + (FOV / 2.0))
	{
		g_player.renderer_x = g_player.new_x + cos(player_angle) * INT16_MAX; // Renderer of x depending on the position of the plaer and where the player moves
		g_player.renderer_y = g_player.new_y + sin(player_angle) * INT16_MAX; // Renderer of y depending on the position of the plaer and where the player moves
		player_angle += FOV / resolution.width;
		g_count++;
		dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
	}
}

void	ft_square(float x, float y, int color, int size)
{
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			ft_put_image(i * RATIO, j * RATIO, color);
			j++;
		}
		i++;
	}
}

void	ft_put_image(int x, int y, int color)
{
	if (x < resolution.width && x >= 0 && y < resolution.height && y >= 0) {
    	g_mlx->img.data[x * resolution.width + y] = color;
	}
}
