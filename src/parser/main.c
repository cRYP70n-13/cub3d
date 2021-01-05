#include "../../includes/header.h"

int		main(int argc, char **argv)
{
	if (argc != 2)
		ft_error_and_quit(5);
    parsing(argv);
	graphic();
    return 0;
}

int		parsing(char **argv)
{
	char					*line;
	t_floor					s_floor;
	t_celling				s_celling;
	int						i = 0;
	int						j;
	int						player = 0;

	if (!(g_map = malloc(sizeof(t_map))))
		ft_error_and_quit(2);

	int fd = open(argv[1], O_RDONLY);

	initial_structs(g_map);
	while (1)
	{
		// printf("%s\n", line);
		int ret = get_next_line(fd, &line);
		if (line[0] == 'R' && line[1] == ' ')
		{
			char **splited_line = ft_split(line + 2, ' ');

			int i = 0;
			while ((*splited_line)[i])
			{
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else
					ft_error_and_quit(1);
			}
			g_resolution.height = ft_atoi(splited_line[0]);
			g_resolution.width = ft_atoi(splited_line[1]);
			g_resolution.resolution = line[0];

		}
		if (line[0] == 'F' && line[1] == ' ')
		{
			char **splited_line = ft_split(line + 2, ',');

			int i = 0;
			while ((*splited_line)[i])
			{
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else
					ft_error_and_quit(1);
			}
			s_floor.Floor = line[0];
			s_floor.red = ft_atoi(splited_line[0]);
			s_floor.green = ft_atoi(splited_line[1]);
			s_floor.blue = ft_atoi(splited_line[2]);
		}
		if (line[0] == 'C' && line[1] == ' ')
		{
			char **splited_line = ft_split(line + 2, ',');

			int i = 0;
			while ((*splited_line)[i])
			{
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else
					ft_error_and_quit(1);
			}
			s_celling.celling = line[0];
			s_celling.red = ft_atoi(splited_line[0]);
			s_celling.green = ft_atoi(splited_line[1]);
			s_celling.blue = ft_atoi(splited_line[2]);
		}
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			parse_textures(line + 2, NO);
		if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			parse_textures(line + 2, SO);
		if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			parse_textures(line + 2, WE);
		if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			parse_textures(line + 2, EA);
		if (line[0] == 'S' && line[1] == ' ')
			parse_textures(line + 2, S);
		if (line[0] == ' ' || line[0] == '1') {
			check_map(line, g_map);
			fill_line(line, g_map);
		}
		if (ret == 0)
			break ;
	}

	g_map->virtual_map_before = ft_split(g_map->map_in_one_line, '\n');
	map_manager(g_map);

	while (i <= g_map->height + 1) {
		j = 0;
		printf("%s\n", g_map->map_2d[i]);
		while (j <= g_map->width) {
			if (g_map->map_2d[i][j] == 'W' || g_map->map_2d[i][j] == 'E' || \
					g_map->map_2d[i][j] == 'S' || g_map->map_2d[i][j] == 'N') {
				player++;
			}
			(wall_conditions(g_map, &i, &j)) ? ft_error_and_quit(4) : 0;
			j++;
		}
		i++;
	}

	if (player != 1)
		ft_error_and_quit(3);

	return (0);
}
