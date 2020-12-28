#include "../../includes/header.h"
#include "../utils/libft/libft.h"
#include "../../includes/structs.h"

void	fill_line(char *line, s_map *_map)
{
	if (!(_map->map_in_one_line))
		_map->map_in_one_line = strdup("");
	_map->map_in_one_line = ft_strjoin(_map->map_in_one_line, line);
	_map->map_in_one_line = ft_strjoin(_map->map_in_one_line, "\n");
}

void	map_manager(s_map *_map)
{
	int		i;
	int		j;

	i = -1;
	_map->map_2d = (char**)malloc((_map->height + 3) * sizeof(char*));
	while (++i < _map->height + 2)
		_map->map_2d[i] = (char*)malloc((_map->width + 3) * sizeof(char));
	_map->map_2d[i] = NULL;
	i = -1;
	while (++i <= _map->width + 1)
		_map->map_2d[0][i] = ' ';
	_map->map_2d[0][i] = '\0';
	i = 0;
	while (i < _map->height)
	{
		j = 0;
		_map->map_2d[i + 1][0] = ' ';
		while (j < _map->width + 2)
		{
			if (j < (int)strlen(_map->virtual_map_before[i]))
				_map->map_2d[i + 1][j + 1] = _map->virtual_map_before[i][j];
			else
				_map->map_2d[i + 1][j + 1] = ' ';
			j++;
		}
		_map->map_2d[i + 1][j] = '\0';
		i++;
	}
	i = -1;
	while (++i <= _map->width + 1)
		_map->map_2d[_map->height + 1][i] = ' ';
	_map->map_2d[_map->height + 1][i] = '\0';
}


// The graphics Part
int		is_wall(float x, float y, float Xinc, float Yinc)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x > (_map->width * TAIL_SIZE) || y < 0 || y > (_map->height * TAIL_SIZE))
		return (1);
	map_grid_index_x = (int)(x / TAIL_SIZE);
	map_grid_index_y = (int)(y / TAIL_SIZE);

	if (_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || _map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);

	map_grid_index_x = (int)((x + Xinc) / TAIL_SIZE);
	map_grid_index_y = (int)(y / TAIL_SIZE);

	if (_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || _map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);

	map_grid_index_x = (int)(x / TAIL_SIZE);
	map_grid_index_y = (int)((y + Yinc) / TAIL_SIZE);

	if (_map->map_2d[map_grid_index_y][map_grid_index_x] == '1' || _map->map_2d[map_grid_index_y][map_grid_index_x] == ' ')
		return (1);
	return (0);
}