#include "../../includes/header.h"

void	field_of_view(void)
{
	g_player.player_angle = g_player.rotation_angle - (FOV / 2.0);
	g_img.count = 0;

	while (g_player.player_angle <= g_player.rotation_angle + (FOV / 2.0))
	{
		g_player.renderer_x = g_player.new_x + cos(g_player.player_angle) * INT16_MAX; // Renderer of x depending on the position of the plaer and where the player moves
		g_player.renderer_y = g_player.new_y + sin(g_player.player_angle) * INT16_MAX; // Renderer of y depending on the position of the plaer and where the player moves
		g_player.player_angle += FOV / g_resolution.width;
		g_img.count++;
		dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
	}
}

void	ft_square(float x, float y, int color, int size)
{
	// printf("LKASDJFLKJDLKJSLK\n");
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			ft_put_image(i, j, color);
			j++;
		}
		i++;
		// printf("EL FASI\n");
	}
}

void	ft_put_image(int x, int y, int color)
{
	// color = 0xFFFFFF;
	// printf("%d ||| %d\n", x, y);
	if (x < g_resolution.width && x >= 0 && y < g_resolution.height && y >= 0) {
	// printf("%d\n", g_mlx->img.data[0]);
		g_mlx->img.data[y * g_resolution.width + x] = color;
		//printf("%d	%d	%d	\n", x, y,  x * g_resolution.width + y);
	}
}
