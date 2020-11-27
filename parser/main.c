#include "get_next_line.h"
#include "./structs.h"
#include <stdio.h>
#include <string.h>


static int			is_split(char str, char c)
{
	if (str == c || str == '\t' || str == '\n')
		return (1);
	else
		return (0);
}

static int			word_count(const char *str, char c)
{
	int i;
	int output;

	i = 0;
	output = 0;
	while (str[i])
	{
		if (!is_split(str[i], c) && (i == 0 || is_split(str[i - 1], c)))
		{
			output++;
			i++;
		}
		else
			i++;
	}
	return (output);
}

static int			letter_count(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (!is_split(str[i], c) && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char			*get_word(const char *str, char a, char **arr, int k)
{
	int			i;
	char		*c;

	i = 0;
	if (!(c = malloc(letter_count(str, a) + 1)))
	{
		while (i < k)
		{
			free(*(arr + i));
			i++;
		}
		free(arr);
	}
	while (!is_split(str[i], a) && *(str + i) != '\0')
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char				**ft_split(char const *str, char c)
{
	char		**array;
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (!str)
		return (0);
	if (!(array = malloc(sizeof(char*) * (word_count(str, c) + 1))))
		return (0);
	while (str[i])
	{
		if (!is_split(str[i], c) && (i == 0 || is_split(str[i - 1], c)))
		{
			if (!(array[k] = get_word(&str[i], c, array, k)))
				return (0);
			k++;
		}
		i++;
	}
	array[word_count(str, c)] = 0;
	return (array);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

void	parse_textures(char *line, int type)
{
	s_textrs *ptr_textures;
	int i;

	i = 0;
	if (!(ptr_textures = malloc(sizeof(s_textrs*))))
		return ;
	if (!(ptr_textures->textures = malloc(sizeof(char *) * 5)))
		return ;
	while (line[i] != ' ' || line[i] != '\0') {
		if (ft_isalpha(line[i]) || line[i] == '.') {
			ptr_textures->textures[type] = strdup(line + i);
			// printf("%s\n", ptr_textures->textures[type]);
			break;
		}
		i++;
	}
	// printf("%s\n", textures->textures[0]);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	else
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}

int		main(int argc, char **argv)
{
	char *line;
	struct t_resolution s_resolution;
	struct t_floor s_floor;
	struct t_celling s_celling;
	int width;
	int height = 0;
	int cnt;
	// char *valid_chars = "012NSEW";

	if (argc != 2)
		return 0;
	int fd = open(argv[1], O_RDONLY);
	cnt = 0;
	while (get_next_line(fd, &line)) {
		// printf("%s\n", line);
		if (line[0] == 'R') {
			char **splited_line = ft_split(line + 2, ' ');

			int i = 0;
			while ((*splited_line)[i]) {
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else {
					printf("Invalid Map !!!");
					return -1;
				}
			}
			s_resolution.height = atoi(splited_line[0]);
			s_resolution.width = atoi(splited_line[1]);
			s_resolution.resolution = line[0];
			// printf("%c %d %d\n",s_resolution.resolution, s_resolution.height, s_resolution.width); 
		}
		if (line[0] == 'F') {
			char **splited_line = ft_split(line + 2, ',');

			int i = 0;
			while ((*splited_line)[i]) {
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else {
					printf("Invalid Map !!!");
					return -1;
				}
			}
			s_floor.Floor = line[0];
			s_floor.red = atoi(splited_line[0]);
			s_floor.green = atoi(splited_line[1]);
			s_floor.blue = atoi(splited_line[2]);
			// printf("%c %d %d %d\n", s_floor.Floor, s_floor.red, s_floor.green, s_floor.blue); 
		}
		if (line[0] == 'C') {
			char **splited_line = ft_split(line + 2, ',');

			int i = 0;
			while ((*splited_line)[i]) {
				if (ft_isdigit((*splited_line)[i]))
					i++;
				else {
					printf("Invalid Map !!!");
					return -1;
				}
			}
			s_celling.celling = line[0];
			s_celling.red = atoi(splited_line[0]);
			s_celling.green = atoi(splited_line[1]);
			s_celling.blue = atoi(splited_line[2]);
			// printf("%c %d %d %d\n", s_celling.celling, s_celling.red, s_celling.green, s_floor.blue); 
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
			width = strlen(line);
			height++;
			int i = 0;

			while (line[i]) {
				if (line[i] != '0' && line[i] != ' ' && line[i] != '1' && line[i] != '2' && line[i] != 'N')
					printf("NOT A VALID MAP %s\n", line);
				i++;
			}
			// printf("I Found the MAP !!\n");
			printf("%d Width - %d Height\n", width, height);
		}
	}
	// printf("%s\n%d", line, ++cnt);
	return (0);
}
