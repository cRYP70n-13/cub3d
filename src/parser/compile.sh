#!/bin/sh

gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c graphic.c main_parser.c map_manager.c map_helpers.c keys.c map_parsing.c ../utils/Errors/exit.c ../utils/libft/ft_atoi.c  ../utils/libft/ft_strdup.c ../utils/libft/ft_split.c ../utils/libft/ft_isdigit.c ../utils/libft/ft_isalpha.c  -DDEBUG -D BUFFER_SIZE=1024  -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -fsanitize=address -g
