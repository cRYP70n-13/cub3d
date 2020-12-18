/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:03:47 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/16 16:43:11 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./structs.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"
#include <stdio.h>
#include <string.h>
#include "header.h"

// The parser part So now it's easy to split the functions to multiple files
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

// The Atoi function I hope I don't miss it up
int		ft_atoi(const char *str)
{
	int i;
	int number;
	int signe;

	signe = 1;
	i = 0;
	number = 0;
	while (*str > 0 && *str <= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + i) >= 48 && *(str + i) <= 57)
		number = number * 10 + *(str + i++) - '0';
	return (number * signe);
}

// The graphics Part
int is_wall(float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x > (_map->width * TAIL_SIZE) || y < 0 || y > (_map->height * TAIL_SIZE))
		return (0);
	map_grid_index_x = (int)(x / TAIL_SIZE);
	map_grid_index_y = (int)(y / TAIL_SIZE);
	if (_map->map_2d[map_grid_index_y][map_grid_index_x] != '1')
		return (0);
	printf("%d | %d | %d\n", map_grid_index_x, map_grid_index_y, _map->map_2d[(int)map_grid_index_y][(int)map_grid_index_x]);
	return (1);
	// return (atoi(&_map->map_2d[map_grid_index_y][map_grid_index_x]));
}

void	ft_put_image(int x, int y, int color)
{
	g_mlx->img.data[x * TAIL_SIZE * _map->width + y] = color;
}

void ft_square(int x, int y, int color, int size)
{
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			ft_put_image(i, j, color);
			j++;
		}
		i++;
	}
}

void dda(int X0, int Y0, int X1, int Y1)
{
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps;

	steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy);
	// calculate increment in x & y for each steps
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	int i = 0;
	while (i <= steps)
	{
		ft_put_image(Y, X, 0x00FF00);
		X += Xinc;													 // increment in x at each step
		Y += Yinc;													 // increment in y at each step
		i++;
	}
}

void struct_init()
{
	g_player.x = (_map->width * TAIL_SIZE) / 2;
	g_player.y = (_map->height * TAIL_SIZE) / 2;
	g_player.rotation_angle = PI / 2.0;
	g_player.move_speed = 5.0;
	g_player.rotation_speed = 0.1;
}

int key_pressed(int keycode)
{
	if (keycode == UP_ARROW)
		g_player.walk_up = 1;
	if (keycode == DOWN_ARROW)
		g_player.walk_up= -1;
	if (keycode == RIGHT_ARROW)
		g_player.turn_right = 1;
	if (keycode == LEFT_ARROW)
		g_player.turn_right = -1;
	return (0);
}

int key_released(int keycode)
{
	if (keycode == UP_ARROW || keycode == DOWN_ARROW)
		g_player.walk_up = 0;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
		g_player.turn_right = 0;
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	g_player.new_y = 0;
	g_player.new_x = 0;
	return (0);
}

int deal_key()
{
	// The up and down keys
	g_player.new_y = g_player.y + sin(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up;
	g_player.new_x = g_player.x + cos(g_player.rotation_angle) * g_player.move_speed * g_player.walk_up ;

	if (!is_wall(g_player.new_x, g_player.y))
		g_player.x = g_player.new_x;
	if (!is_wall(g_player.x, g_player.new_y))
		g_player.y = g_player.new_y;
	// printf("\n\n\n\n\n\n\n%f", g_player.move_speed);

	// The left and right keys
	g_player.rotation_angle -= g_player.rotation_speed * g_player.turn_right;

	draw_map();
	return (0);
}

int loop_key()
{
	mlx_hook(g_mlx->win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(g_mlx->win_ptr, 3, 0, key_released, 0);
	deal_key();
	mlx_put_image_to_window(g_mlx->mlx_ptr, g_mlx->win_ptr, g_mlx->img.img_ptr, 0, 0);
	return (0);
}

void draw_map()
{
	g_player.renderer_x = g_player.new_x + cos(g_player.rotation_angle) * 40; // Renderer of x depending on the position of the plaer and where the player moves
	g_player.renderer_y = g_player.new_y + sin(g_player.rotation_angle) * 40; // Renderer of y depending on the position of the plaer and where the player moves
	int i = 1;
	int j;
	int x = 0;
	int y = 0;
	int color = 0;

	while (i < _map->height - 1)
	{
		// FIXME
		j = 1;
		while (j < _map->width - 1)
		{
			x = j * TAIL_SIZE;
			y = i * TAIL_SIZE;

			if (_map->map_2d[i][j] == '1') {
				// printf(" 1 = TOSAWI %d\n", _map->map_2d[i][j]);
				color = 0xFF0000; // RED color
			} else if (_map->map_2d[i][j] == ' ') {
				color = 0x0000ff; // BLUE color
			} else if (_map->map_2d[i][j] == '0'){
				color = 0x00FF00; // GREEN color
			} else {
				// DO nothing just continue
			}
			ft_square(x, y, color, TAIL_SIZE);
			j++;
		}
		i++;
	}

	ft_square(g_player.x, g_player.y, 0x000000, 6);
	dda(g_player.x + 3, g_player.y + 3, g_player.renderer_x, g_player.renderer_y);
}

int		main(int argc, char **argv)
{
	char					*line;
	struct t_resolution		s_resolution;
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
			s_resolution.height = atoi(splited_line[0]);
			s_resolution.width = atoi(splited_line[1]);
			s_resolution.resolution = line[0];

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
			}
			(wall_conditions(_map, &i, &j)) ? printf("stop at: %d\n", i) : 0;
			j++;
		}
		i++;
	}

	if (player != 1)
		ft_error_and_quit(3);

	// Graphic part
	g_mlx->mlx_ptr = mlx_init();																						  //Connection to the graphic server
	g_mlx->win_ptr = mlx_new_window(g_mlx->mlx_ptr, (_map->width * TAIL_SIZE), (_map->height * TAIL_SIZE), "cRYP70N"); //initialize the window
	// Here I initialized a new image
	g_mlx->img.img_ptr = mlx_new_image(g_mlx->mlx_ptr, (_map->width * TAIL_SIZE), (_map->height * TAIL_SIZE));
	struct_init();
	g_mlx->img.data = (int *)mlx_get_data_addr(g_mlx->img.img_ptr, &g_mlx->img.bpp, &g_mlx->img.size_l, &g_mlx->img.endian);

	// TODO: I need to make this shit working with images I have set up all the structure I will need its time
	draw_map();
	mlx_loop_hook(g_mlx->mlx_ptr, loop_key, (void *)0);
	mlx_loop(g_mlx->mlx_ptr); //evnets loop

	return (0);
}
