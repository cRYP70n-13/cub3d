#include "../../includes/header.h"

void	graphic(void)
{
	// TODO: Create new image 
	if (!(g_mlx = malloc(sizeof(t_mlx))))
		ft_error_and_quit(2);
	g_map->height += 2;
	g_map->width += 2;
	g_mlx->mlx_ptr = mlx_init();
	g_mlx->win = mlx_new_window(g_mlx->mlx_ptr, (g_resolution.width), (g_resolution.height), "cRYP70N");
	init();
	render();
	g_mlx->img.img_ptr = mlx_new_image(g_mlx->mlx_ptr, g_resolution.width, g_resolution.height);
	g_mlx->img.data = (int *)mlx_get_data_addr(g_mlx->img.img_ptr, &g_mlx->img.bpp, &g_mlx->img.size_l, &g_mlx->img.endian);
	mlx_hook(g_mlx->win, 2, 1L << 0, deal_key, (void*)0);
	mlx_loop(g_mlx->mlx_ptr);
	mlx_put_image_to_window(g_mlx->mlx_ptr, g_mlx->win, g_mlx->img.img_ptr, 0, 0);
}

void	render(void)
{
	draw_map();
	draw_player();
}

void	init(void)
{
	g_player.x = -1;
	g_player.y = -1;
	g_player.rotation_angle = PI / 2.0;
	g_player.move_speed = 4.0;
	g_player.rotation_speed = 0.1;
}

void	draw_map(void)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int color = 0;

	while (i < g_map->height)
	{
		j = 0;
		while (j < g_map->width)
		{
			x = i * TILE_SIZE;
			y = j * TILE_SIZE;
			if (g_map->map_2d[i][j] == '1') {
				color = 0xFF0000;
			} else if (g_map->map_2d[i][j] == ' ') {
				color = 0x00FF00;
			} else if (g_map->map_2d[i][j] == '0') {
				color = 0x0000FF;
			}
			ft_square(x, y, color, TILE_SIZE);
			j++;
		}
		i++;
	}
}

void	draw_player(void)
{
	// TODO: Implement the draw player function
}
