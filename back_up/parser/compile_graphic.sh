#!/bin/sh

# Dar
#gcc -Wall -Werror -Wextra -I ~/Downloads/minilibx_opengl_20191021/ ./main.c -L ~/Downloads/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit && ./a.out

# Cluster
gcc -Wall -Werror -Wextra -I /usr/local/include ./main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit && ./a.out
