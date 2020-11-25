#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	char *line;

	int fd = open(argv[1], O_RDONLY);
	// int fd = open("/Users/mac/Documents/dev/cub3d/map.rt", O_RDONLY);
	while (get_next_line(fd, &line)) {
		printf("%s\n", line);
	}
	printf("%s", line);
	return (0);
}