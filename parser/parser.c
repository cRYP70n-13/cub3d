#include "get_next_line.h"
#include "structs.h"
// #include "../utils/libft/libft.h"

int		main(int argc, char **argv)
{
	char *line;

	int fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line)) {
		int i = 0;
		while ((char)&line[i] != '\n') {
			char **splited_line = ft_split(line, ' ');
			printf("%s\n", splited_line);
			if ((char)&line[i] == 'R')
				printf("Founds an R \n");
			else
				break;
		}
		printf("%s\n", line);
	}
	printf("%s", line);
	return (0);
}