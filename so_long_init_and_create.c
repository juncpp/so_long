/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_init_and_create.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:12:35 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:12:37 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == 'r' && str[i - 1] == 'e' && str[i - 2] == 'b' && \
		str[i - 3] == '.')
		return (1);
	return (0);
}

void	create_matrix(t_map *game, char **str)
{
	char	**matrix;
	int		n;
	int		i;
	int		start;
	int		size;

	start = 0;
	i = 0;
	n = count_line(*str);
	matrix = (char **)malloc((n + 1) * sizeof(char *));
	if (!matrix)
		free_map(-2, *str);
	while (i < n)
	{
		size = len_line(*str, &start);
		matrix[i] = (char *)malloc(sizeof(char) * (size - start + 1));
		if (!matrix[i])
			free_matrix(game, -2, matrix, *str);
		ft_strcpy(matrix[i], *str, start);
		i++;
	}
	matrix[i] = NULL;
	free(*str);
	game->map_data = matrix;
}

char	*open_file(char *str)
{
	int		fd;
	char	*map;
	int		flag;

	fd = open(str, O_RDONLY);
	map = NULL;
	if (fd != -1)
	{
		flag = get_next_line(&map, fd);
		close(fd);
		if (flag < 0)
			errors(0);
	}
	else
		errors(0);
	return (map);
}

t_map	*all_init(char **av)
{
	t_map	*game;
	char	*map;

	game = (t_map *)malloc(sizeof(t_map));
	if (!game)
		errors(-2);
	game->game_over = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->max_score = 0;
	game->player_pos_x = 0;
	game->player_pos_y = 0;
	game->steps = 0;
	game->counter_player = 0;
	map = open_file(av[1]);
	create_matrix(game, &map);
	return (game);
}

void	errors(int errno)
{
	if (errno <= 0)
	{
		write(2, "Error\n", 6);
		if (errno == -2)
			write(2, "Memory allocation error!\n", 25);
		else if (errno == -1)
			write(2, "Map not valid!\n", 15);
		else if (errno == 0)
			write(2, "File is wrong!\n", 15);
		else if (errno == -3)
			write(2, "File is not ending .ber!\n", 25);
		else
			write(2, "Not argument!\n", 14);
	}
	exit(0);
}
