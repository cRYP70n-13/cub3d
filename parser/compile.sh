#!/bin/sh

gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c main.c ../utils/Errors/exit.c  ../utils/libft/ft_split.c ../utils/libft/ft_isdigit.c ../utils/libft/ft_isalpha.c  ../utils/libft/ft_atoi.c -DDEBUG -D BUFFER_SIZE=1024 -fsanitize=address -g