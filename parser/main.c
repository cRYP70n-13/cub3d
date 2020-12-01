#include "get_next_line.h"
#include "./structs.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"
#include <stdio.h>
#include <string.h>

void parse_textures(char *line, int type)
{
	s_textrs *ptr_textures;
	int i;

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
            #ifdef DEBUG
                printf("%s\n", ptr_textures->textures[type]);
            #endif
			break;
		}
		i++;
	}
}

/**
 * @param {*} The Map DataStructure
 *         *i => which is the I cordinate in our map
 *         *j => which is the J cordinate in the map
 * @return {int} Check if our given line in the map is valid or not
 */
// int		wall_conditions(s_map *map, int *i, int *j)
// {
// 	if (MAP2D[*i][*j] == '0' || MAP2D[*i][*j] == '2' || MAP2D[*i][*j] == 'N' || MAP2D[*i][*j] == 'S' || MAP2D[*i][*j] == 'W' || MAP2D[*i][*j] == 'E')
// 	{
// 		if (MAP2D[*i][*j - 1] == ' ' || MAP2D[*i][*j + 1] == ' ' || MAP2D[*i - 1][*j] == ' ' || MAP2D[*i + 1][*j] == ' ')
// 			return (1);
// 	}
// 	return (0);
// }

// Bring the Width and Heigth of the map
void check_map(char *line, s_map *map)
{
	int i = 0;
	map->height++;
	if (strlen(line) > map->width)
		map->width = strlen(line);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != ' ' && line[i] != '1' && line[i] != '2' && line[i] != 'N')
            ft_error_and_quit(1);
        // Here I should call the function wall_conditions(params);
		i++;
	}

	printf("Width: %zu - Height: %zu\n", map->width, map->height);
}


// TODO: Integrate this function into my main function to get the map shit DONE
// Also I have to surrounde my map with '0' So I can handle all the errors at once
int main(int argc, char **argv)
{
	char *line;
	struct t_resolution s_resolution;
	struct t_floor s_floor;
	struct t_celling s_celling;
	int cnt;
	struct map s_map;

	if (argc != 2)
		return 0;
	int fd = open(argv[1], O_RDONLY);
	cnt = 0;
	s_map.width = 0;
	s_map.height = 0;
	while (get_next_line(fd, &line))
	{
		// printf("%s\n", line);
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
                printf("%c %d %d\n",s_resolution.resolution, s_resolution.height, s_resolution.width);
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
                printf("%c %d %d %d\n", s_floor.Floor, s_floor.red, s_floor.green, s_floor.blue);
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
                printf("%c %d %d %d\n", s_celling.celling, s_celling.red, s_celling.green, s_floor.blue);
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
		if (line[0] == ' ' || line[0] == '1')
			check_map(line, &s_map);
	}
	return (0);
}
