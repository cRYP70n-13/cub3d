#include "../../includes/get_next_line.h"
#include "../../includes/structs.h"
#include "../utils/Errors/errors.h"
#include "../../includes/header.h"
#include "../utils/libft/libft.h"

int		main(int argc, char **argv)
{
    parsing(argc, argv);
    return 0;
}

int		parsing(int argc, char **argv)
{
	char					*line;
	struct t_floor			s_floor;
	struct t_celling		s_celling;
	int						i = 0;
	int						j;
	int						player = 0;

	if (!(_map = malloc(sizeof(s_map))))
		ft_error_and_quit(2);
	if (!(g_mlx = malloc(sizeof(t_mlx))))
		ft_error_and_quit(2);
	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);

	initial_structs(_map);
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
			resolution.height = atoi(splited_line[0]);
			resolution.width = atoi(splited_line[1]);
			resolution.resolution = line[0];

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
			check_map(line, _map);
			fill_line(line, _map);
		}
		if (ret == 0)
			break ;
	}

	_map->virtual_map_before = ft_split(_map->map_in_one_line, '\n');
	map_manager(_map);

	while (i <= _map->height + 1) {
		j = 0;
		printf("%s\n", _map->map_2d[i]);
		while (j <= _map->width) {
			if (_map->map_2d[i][j] == 'W' || _map->map_2d[i][j] == 'E' || \
					_map->map_2d[i][j] == 'S' || _map->map_2d[i][j] == 'N') {
				player++;
				// TODO: Here I should call the draw player function to draw my player in the exact location that he gived me
				// ft_draw_player(int x, int y);
			}
			(wall_conditions(_map, &i, &j)) ? ft_error_and_quit(4) : 0;
			j++;
		}
		i++;
	}

	if (player != 1)
		ft_error_and_quit(3);

	return (0);
}