/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:12:43 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:12:45 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_border(char *line, int j)
{
	int	i;

	i = 0;
	if (j == 0)
	{
		while (line[i])
		{
			if (line[i] != '1')
				return (0);
			i++;
		}
	}
	else
	{
		while (line[i + 1])
			i++;
		if (line[0] != '1' || line[i] != '1')
			return (0);
	}
	return (1);
}

void	check_rectangle(t_map *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while ((game->map_data)[j] != NULL)
	{
		while ((game->map_data)[j][i] != '\0')
			i++;
		if (j == 0)
			count = i;
		if (count != i)
			free_matrix(game, -1, game->map_data, NULL);
		i = 0;
		j++;
		if (!check_border((game->map_data)[j - 1], j - 1))
			free_matrix(game, -1, game->map_data, NULL);
	}
	if (j < 3)
		free_matrix(game, -1, game->map_data, NULL);
	if (!check_border((game->map_data)[j - 1], 0))
		free_matrix(game, -1, game->map_data, NULL);
	game->map_height = j * 32;
	game->map_width = count * 32;
}

void	set_pole(char c, t_map *game, int i, int j)
{
	if (c == 'P')
	{
		game->player_pos_x = i;
		game->player_pos_y = j;
		game->counter_player++;
	}
	if (c == 'C')
		game->max_score++;
	if (c == 'E')
		game->game_over = 1;
}

void	check_game_rules(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((game->map_data)[j] != NULL)
	{
		while ((game->map_data)[j][i])
		{
			set_pole((game->map_data)[j][i], game, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	if (game->game_over == 0 || game->counter_player != 1 || \
		game->max_score == 0)
		free_matrix(game, -1, game->map_data, NULL);
}

void	main_validation(t_map **game)
{
	check_rectangle(*game);
	check_game_rules(*game);
}
