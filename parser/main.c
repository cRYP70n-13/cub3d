/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:03:47 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/07 11:03:56 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./structs.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"
#include <stdio.h>
#include <string.h>

void	parse_textures(char *line, int type)
{
	s_textrs	*ptr_textures;
	int			i;

	i = 0;
	if (!(ptr_textures = malloc(sizeof(s_textrs *))))
		return;
	if (!(ptr_textures->textures = malloc(sizeof(char *) * 5)))
		return;
	while (line[i] != ' ' || line[i] != '\0')
	{
		if (ft_isalpha(line[i]) || line[i] == '.')
		{
			ptr_textures->textures[type] = strdup(line + i);
			break;
		}
		i++;
	}
}

int		wall_conditions(s_map *map, int *i, int *j)
{
	if (map->map_2d[*i][*j] == '0' || map->map_2d[*i][*j] == '2' || map->map_2d[*i][*j] == 'N' || map->map_2d[*i][*j] == 'S' || map->map_2d[*i][*j] == 'W' || map->map_2d[*i][*j] == 'E')
	{
		if (map->map_2d[*i][*j - 1] == ' ' || map->map_2d[*i][*j + 1] == ' ' || map->map_2d[*i - 1][*j] == ' ' || map->map_2d[*i + 1][*j] == ' ')
			return (1);
	}
	return (0);
}

void    initial_structs(s_map *map)
{
	map->height = 0;
	map->width = 0;
	map->map_in_one_line = NULL;
	map->map_2d = NULL;
	map->virtual_map_before = NULL;
}

void	check_map(char *line, s_map *map)
{
	int i = 0;
	map->height++;
	if ((int)strlen(line) > map->width)
		map->width = strlen(line);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != ' ' && line[i] != '1' && line[i] != '2' && line[i] != 'N')
			ft_error_and_quit(1);
		i++;
	}
}

void    fill_line(char *line, s_map *map)
{
	if (!(map->map_in_one_line))
		map->map_in_one_line = strdup("");
	map->map_in_one_line = ft_strjoin(map->map_in_one_line, line);
	map->map_in_one_line = ft_strjoin(map->map_in_one_line, "\n");
}

// TODO: Double player No player N S W E 
void	map_manager(s_map *map)
{
	int		i;
	int		j;

	i = -1;
	map->map_2d = (char**)malloc((map->height + 3) * sizeof(char*));
	while (++i < map->height + 2)
		map->map_2d[i] = (char*)malloc((map->width + 3) * sizeof(char));
	map->map_2d[i] = NULL;

	i = -1;
	while (++i <= map->width + 1)
		map->map_2d[0][i] = ' ';
	map->map_2d[0][i] = '\0';

	i = 0;
	while (i < map->height)
	{
		j = 0;
		map->map_2d[i + 1][0] = ' ';
		while (j < map->width + 2)
		{
			if (j < (int)strlen(map->virtual_map_before[i]))
				map->map_2d[i + 1][j + 1] = map->virtual_map_before[i][j];
			else
				map->map_2d[i + 1][j + 1] = ' ';
			j++;
		}
		map->map_2d[i + 1][j] = '\0';
		i++;
	}

	i = -1;
	while (++i <= map->width + 1)
		map->map_2d[map->height + 1][i] = ' ';
	map->map_2d[map->height + 1][i] = '\0';
}

int main(int argc, char **argv)
{
	char *line;
	struct t_resolution s_resolution;
	struct t_floor s_floor;
	struct t_celling s_celling;
	s_map *map;

	if (!(map = malloc(sizeof(s_map))))
		ft_error_and_quit(2);
	if (argc != 2)
		return 0;
	int fd = open(argv[1], O_RDONLY);

	initial_structs(map);
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
			s_resolution.height = atoi(splited_line[0]);
			s_resolution.width = atoi(splited_line[1]);
			s_resolution.resolution = line[0];

			#ifdef DEBUG
				// printf("%c %d %d\n",s_resolution.resolution, s_resolution.height, s_resolution.width);
			#endif
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

			#ifdef DEBUG
				// printf("%c %d %d %d\n", s_floor.Floor, s_floor.red, s_floor.green, s_floor.blue);
			#endif
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

			#ifdef DEBUG
				// printf("%c %d %d %d\n", s_celling.celling, s_celling.red, s_celling.green, s_floor.blue);
			#endif
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
			check_map(line, map);
			fill_line(line, map);
		}
		if (ret == 0)
			break ;
	}

	map->virtual_map_before = ft_split(map->map_in_one_line, '\n');
	map_manager(map);

	int i = 0;
	int j;
	while (i <= map->height + 1) {
		j = 0;
		printf("%s\n", map->map_2d[i]);
		while (j <= map->width) {
			(wall_conditions(map, &i, &j)) ? printf("stop at: %d\n", i) : 0;
			j++;
		}
		i++;
	}

	return (0);
}
