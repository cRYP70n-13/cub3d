<<<<<<< HEAD
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
=======
#include "./get_next_line.h"
#include <stdio.h>

int     main(int argc, char **argv)
{
    char *line;

    int fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line))
        printf("%s\n", line);
    return (0);
>>>>>>> f9a7dc4e605698517dfc857ec5fab555c040882e
}