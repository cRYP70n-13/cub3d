/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:40:45 by okimdil           #+#    #+#             */
/*   Updated: 2019/11/01 15:14:57 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include <stdio.h>

int		ft_strlen(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int		is_a_c(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		push_to_line(char **post_buffer, char **line, char sep)
{
	void *temp;

	temp = *post_buffer;
	*line = ft_strdup(*post_buffer, sep);
	*post_buffer = ft_strcut_c(*post_buffer, sep);
	free(temp);
	if (sep == '\n')
		return (1);
	else if (sep == '\0')
		return (0);
	return (0);
}

int		get_next_line_reading(int fd, char **post_buffer, char **line)
{
	int			ret_read;
	char		*buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while ((ret_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret_read == -1)
			break ;
		buf[ret_read] = '\0';
		if ((*post_buffer = ft_strjoin(*post_buffer, buf)) &&
		is_a_c(buf, '\n') == 1)
			break ;
	}
	free(buf);
	if (ret_read >= 0 && is_a_c(*post_buffer, '\n') == 1)
		return (push_to_line(post_buffer, line, '\n'));
	if (ret_read == 0 && BUFFER_SIZE > 0)
		return (push_to_line(post_buffer, line, '\0'));
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char	*post_buffer[BUFFER_SIZE];

	if (line == NULL)
		return (-1);
	if (fd >= 0 && !(post_buffer[fd]))
	{
		if (!(post_buffer[fd] = (char*)malloc(1)))
			return (0);
		post_buffer[fd][0] = '\0';
	}
	if (fd >= 0 && is_a_c(post_buffer[fd], '\n') == 1)
		return (push_to_line(&post_buffer[fd], line, '\n'));
	if (fd >= 0)
		return (get_next_line_reading(fd, &post_buffer[fd], line));
	return (-1);
}
