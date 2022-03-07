/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_move_and_close.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:12:56 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:13:02 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_esc(int keycode, t_map *game)
{
	(void) game;
	if (keycode == 53)
	{
		mlx_destroy_window(game->libx->mlx, game->libx->win);
		free(game->libx);
		free_matrix(game, 1, game->map_data, NULL);
		exit(0);
	}
	return (0);
}

int	fast_close(t_map *game)
{
	free(game->libx);
	free_matrix(game, 1, game->map_data, NULL);
	exit(0);
}

int	move_all(t_map *game, int x, int y)
{
	int	i;
	int	j;

	i = game->player_pos_x;
	j = game->player_pos_y;
	if ((game->map_data)[j + y][i + x] != '1')
	{
		if ((game->map_data)[j + y][i + x] == 'C')
			game->max_score--;
		else if ((game->map_data)[j + y][i + x] == 'E')
		{
			if (!game->max_score)
				game->game_over = 0;
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j + y][i + x] = 'P';
		game->player_pos_x = i + x;
		game->player_pos_y = j + y;
		game->steps++;
		pixels_init(game, game->libx);
		ft_itoa(game->steps, game);
	}
	return (1);
}

int	move_game(int keycode, t_map *game)
{
	close_esc(keycode, game);
	if (keycode == 13)
		move_all(game, 0, -1);
	else if (keycode == 0)
		move_all(game, -1, 0);
	else if (keycode == 1)
		move_all(game, 0, 1);
	else if (keycode == 2)
		move_all(game, 1, 0);
	if (!game->game_over)
	{
		mlx_clear_window(game->libx->mlx, game->libx->win);
		last_img(game, 0, 0);
	}
	return (0);
}
