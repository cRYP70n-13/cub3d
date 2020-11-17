/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:40:31 by okimdil           #+#    #+#             */
/*   Updated: 2019/11/01 15:14:53 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(str, c) + 1))))
		return (NULL);
	while (str && str[i] && str[i] != c)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strcut_c(char *str, char c)
{
	int		i;

	i = 0;
	if (!(str))
		return (NULL);
	if (is_a_c(str, c) == 0)
		return (NULL);
	while (str[i] != c)
		i++;
	i++;
	return (ft_strdup(&str[i], '\0'));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = (char*)malloc(sizeof(char) *
	((ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1)))))
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}
