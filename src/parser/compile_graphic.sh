#!/bin/sh

# Dar
gcc -Wall -Werror -Wextra -I ../../mlxopengl  *.c ../../src/utils/libft/ft_atoi.c ../../src/utils/libft/ft_isalpha.c ../../src/utils/libft/ft_isdigit.c ../../src/utils/libft/ft_split.c ../../src/utils/Errors/exit.c  -L ../../mlxopengl/  -lmlx -framework OpenGL -framework AppKit -D BUFFER_SIZE=1024

# Cluster
# gcc -Wall -Werror -Wextra -I /usr/local/include ./main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -DDEBUG=true && ./a.out
