/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_memory_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:12:50 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:12:51 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_line(char *map)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			if (map[i + 1] == '\0')
				return (counter);
			counter++;
		}
		i++;
	}
	return (counter);
}

int	len_line(char *str, int *checkpoint)
{
	static int	i;

	*checkpoint = i;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			++i;
			return (i - 1);
		}
		i++;
	}
	return (i);
}

void	ft_strcpy(char *dest, char *src, int start)
{
	int	i;

	i = 0;
	while (src[start] != '\n' && src[start])
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = '\0';
}

void	free_map(int flag, char *map)
{
	free(map);
	if (flag < 0)
		errors(flag);
}

void	free_matrix(t_map *game, int flag, char **matrix, char *map)
{
	int	j;

	j = 0;
	if (map != NULL)
		free(map);
	while (matrix[j] != NULL)
		free(matrix[j++]);
	free(matrix);
	free(game);
	if (flag == -1)
		errors(flag);
}
