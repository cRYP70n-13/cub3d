#ifndef _GET_NEXT_LINE_H_
# define _GET_NEXT_LINE_H_

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define BUFFER_SIZE 1024

int		ft_strle(char *str, char c);
char	*ft_strjoi(char *s1, char *s);
char	*ft_strcut_c(char *post_buffer, char c);
char	*ft_strdu(char *str, char c);
int		is_a_c(char *str, char c);
int		get_next_line(int fd, char **line);

#endif