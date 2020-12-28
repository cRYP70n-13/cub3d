#include "../../includes/get_next_line.h"

char	*ft_strdu(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = (char*)malloc(sizeof(char) * (ft_strle(str, c) + 1))))
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
	return (ft_strdu(&str[i], '\0'));
}

char	*ft_strjoi(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = (char*)malloc(sizeof(char) *
	((ft_strle(s1, '\0') + ft_strle(s2, '\0') + 1)))))
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