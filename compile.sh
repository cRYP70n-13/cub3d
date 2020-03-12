#!/bin/sh

gcc -Wall -Werror -Wextra -I /usr/local/include ./main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit && ./a.out
