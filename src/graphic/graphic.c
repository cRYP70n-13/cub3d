#include "../../includes/header.h"

void	graphic(void)
{
	// TODO: Create new image 
	if (!(g_mlx = malloc(sizeof(t_mlx))))
		ft_error_and_quit(2);
	g_mlx->mlx_ptr = mlx_init();
	g_mlx->win = mlx_new_window(g_mlx->mlx_ptr, (g_resolution.width), (g_resolution.height), "cRYP70N");
	init();
	render();
	mlx_hook(g_mlx->win, 2, 1L << 0, deal_key, (void*)0);
	mlx_loop(g_mlx->mlx_ptr);
}

void	render(void)
{
	draw_map();
	draw_player();
}

	// g_mlx.mlx_ptr = mlx_init();																						  //Connection to the graphic server
	// g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, (MAP_NUM_COLS * TAIL_SIZE), (MAP_NUM_ROWS * TAIL_SIZE), "cRYP70N"); //initialize the window
	// struct_init();
	// draw_map();
	// mlx_loop_hook(g_mlx.mlx_ptr, loop_key, (void *)0);
	// mlx_loop(g_mlx.mlx_ptr); //evnets loop
