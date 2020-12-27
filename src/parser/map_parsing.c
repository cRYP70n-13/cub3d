/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:39:36 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/21 18:39:37 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include "../utils/libft/libft.h"
#include "../utils/Errors/errors.h"
#include "../../includes/structs.h"

void	parse_textures(char *line, int type)
{
	s_textrs		*ptr_textures;
	int				i;

	i = 0;
	if (!(ptr_textures = malloc(sizeof(s_textrs *))))
		return ;
	if (!(ptr_textures->textures = malloc(sizeof(char *) * 5)))
		return ;
	while (line[i] != ' ' || line[i] != '\0')
	{
		if (ft_isalpha(line[i]) || line[i] == '.')
		{
			ptr_textures->textures[type] = strdup(line + i);
			break ;
		}
		i++;
	}
}

int		wall_conditions(s_map *_map, int *i, int *j)
{
	if (_map->map_2d[*i][*j] == '0' || _map->map_2d[*i][*j] == '2' || \
		_map->map_2d[*i][*j] == 'N' || _map->map_2d[*i][*j] == 'S' || \
		_map->map_2d[*i][*j] == 'W' || _map->map_2d[*i][*j] == 'E')
	{
		if (_map->map_2d[*i][*j - 1] == ' ' || _map->map_2d[*i][*j + 1] == ' ' \
		|| _map->map_2d[*i - 1][*j] == ' ' || _map->map_2d[*i + 1][*j] == ' ')
			return (1);
	}
	return (0);
}

void	initial_structs(s_map *_map)
{
	_map->height = 0;
	_map->width = 0;
	_map->map_in_one_line = NULL;
	_map->map_2d = NULL;
	_map->virtual_map_before = NULL;
}

void	check_map(char *line, s_map *_map)
{
	int i;

	i = 0;
	_map->height++;
	if ((int)strlen(line) > _map->width)
		_map->width = strlen(line);
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
