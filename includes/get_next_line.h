/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:41:05 by okimdil           #+#    #+#             */
/*   Updated: 2019/10/31 15:41:14 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

int		ft_strlen(char *str, char c);
char	*ft_strjoin(char *s1, char *s);
char	*ft_strcut_c(char *post_buffer, char c);
char	*ft_strdup(char *str, char c);
int		is_a_c(char *str, char c);
int		get_next_line(int fd, char **line);

#endif
