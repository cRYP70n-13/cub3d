#include "../../includes/header.h"
#include "../utils/libft/libft.h"
#include "../../includes/structs.h"

void	fill_line(char *line, t_map *g_map)
{
	if (!(g_map->map_in_one_line))
		g_map->map_in_one_line = strdup("");
	g_map->map_in_one_line = ft_strjoin(g_map->map_in_one_line, line);
	g_map->map_in_one_line = ft_strjoin(g_map->map_in_one_line, "\n");
}

void	map_manager(t_map *g_map)
{
	int		i;
	int		j;

	i = -1;
	g_map->map_2d = (char**)malloc((g_map->height + 3) * sizeof(char*));
	while (++i < g_map->height + 2)
		g_map->map_2d[i] = (char*)malloc((g_map->width + 3) * sizeof(char));
	g_map->map_2d[i] = NULL;
	i = -1;
	while (++i <= g_map->width + 1)
		g_map->map_2d[0][i] = ' ';
	g_map->map_2d[0][i] = '\0';
	i = 0;
	while (i < g_map->height)
	{
		j = 0;
		g_map->map_2d[i + 1][0] = ' ';
		while (j < g_map->width + 2)
		{
			if (j < (int)strlen(g_map->virtual_map_before[i]))
				g_map->map_2d[i + 1][j + 1] = g_map->virtual_map_before[i][j];
			else
				g_map->map_2d[i + 1][j + 1] = ' ';
			j++;
		}
		g_map->map_2d[i + 1][j] = '\0';
		i++;
	}
	i = -1;
	while (++i <= g_map->width + 1)
		g_map->map_2d[g_map->height + 1][i] = ' ';
	g_map->map_2d[g_map->height + 1][i] = '\0';
}


// The graphics Part
int		is_wall(float x, float y, float Xinc, float Yinc)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x > (g_map->width * TAIL_SIZE) || y < 0 || y > (g_map->height * TAIL_SIZE))
		return (1);
	map_grid_index_x = (int)(x / TAIL_SIZE);
	map_grid_index_y = (int)(y / TAIL_SIZE);

	if (g_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || g_map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);

	map_grid_index_x = (int)((x + Xinc) / TAIL_SIZE);
	map_grid_index_y = (int)(y / TAIL_SIZE);

	if (g_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || g_map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);

	map_grid_index_x = (int)(x / TAIL_SIZE);
	map_grid_index_y = (int)((y + Yinc) / TAIL_SIZE);

	if (g_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || g_map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);
	return (0);
}