#include "so_long.h"

int	check_valid(char c)
{
	if (c == '1' || c == '0' || c == '\n' || c == 'E' || c == 'P' || c == 'C')
		return (1);
	return (0);
}

char	*ft_strjoin(char *str, char c)
{
	int		i;
	char	*s;

	if (!check_valid(c))
		free_map(-1, str);
	i = 0;
	while (str[i] != '\0')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		free_map(-2, str);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = c;
	s[i] = '\0';
	free(str);
	return (s);
}

int	get_next_line(char **inp, int fd)
{
	int		flag;
	char	c;

	*inp = (char *)malloc(1);
	if (!*inp)
		free_map(-2, *inp);
	(*inp)[0] = '\0';
	while (1)
	{
		flag = read(fd, &c, 1);
		if (flag <= 0)
			break ;
		*inp = ft_strjoin(*inp, c);
	}
	return (flag);
}