#include "../../includes/header.h"

void	parse_textures(char *line, int type)
{
	t_textrs		*ptr_textures;
	int				i;

	i = 0;
	if (!(ptr_textures = malloc(sizeof(t_textrs *))))
		return ;
	if (!(ptr_textures->textures = malloc(sizeof(char *) * 5)))
		return ;
	while (line[i] != ' ' || line[i] != '\0')
	{
		if (ft_isalpha(line[i]) || line[i] == '.')
		{
			ptr_textures->textures[type] = ft_strdup(line + i);
			break ;
		}
		i++;
	}
}

int		wall_conditions(t_map *g_map, int *i, int *j)
{
	if (g_map->map_2d[*i][*j] == '0' || g_map->map_2d[*i][*j] == '2' || \
		g_map->map_2d[*i][*j] == 'N' || g_map->map_2d[*i][*j] == 'S' || \
		g_map->map_2d[*i][*j] == 'W' || g_map->map_2d[*i][*j] == 'E')
	{
		if (g_map->map_2d[*i][*j - 1] == ' ' || g_map->map_2d[*i][*j + 1] == ' ' \
		|| g_map->map_2d[*i - 1][*j] == ' ' || g_map->map_2d[*i + 1][*j] == ' ')
			return (1);
	}
	return (0);
}

void	initial_structs(t_map *g_map)
{
	g_map->height = 0;
	g_map->width = 0;
	g_map->map_in_one_line = NULL;
	g_map->map_2d = NULL;
	g_map->virtual_map_before = NULL;
}

void	check_map(char *line, t_map *g_map)
{
	int i;

	i = 0;
	g_map->height++;
	if ((int)ft_strlen(line) > g_map->width)
		g_map->width = ft_strlen(line);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != ' ' && line[i] != '1'\
		&& line[i] != '2' && line[i] != 'N' && line[i] != 'S' \
		&& line[i] != 'W' && line[i] != 'E')
		{
			ft_error_and_quit(1);
		}
		i++;
	}
}
