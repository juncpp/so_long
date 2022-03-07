/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:11:40 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:11:41 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	fast_close_bonus(t_map *game)
{
	free(game->libx);
	free(game->game_b);
	free_matrix(game, 1, game->map_data, NULL);
	exit(0);
}

int	close_esc_bonus(int keycode, t_map *game)
{
	(void) game;
	if (keycode == 53)
	{
		mlx_destroy_window(game->libx->mlx, game->libx->win);
		free(game->libx);
		free(game->game_b);
		free_matrix(game, 1, game->map_data, NULL);
		exit(0);
	}
	return (0);
}

int	last_pos(t_map *game, int i, int j)
{
	int	x;

	x = --i;
	while ((game->map_data)[j])
	{
		while (i != -1)
		{
			if ((game->map_data)[j][i] == '0')
			{
				if (game->game_b->enemy_arr[0].pos_x != i || \
						game->game_b->enemy_arr[0].pos_y != j)
				{
					game->game_b->k_enemy++;
					game->game_b->enemy_arr[1].flag = 1;
					game->game_b->enemy_arr[1].pos_x = i;
					game->game_b->enemy_arr[1].pos_y = j;
					return (1);
				}
			}
			i--;
		}
		i = x;
		j++;
	}
	return (0);
}

int	put_enemy(t_map *game, int i, int j)
{
	while ((game->map_data)[j])
	{
		while ((game->map_data)[j][i])
		{
			if ((game->map_data)[j][i] == '0')
			{
				game->game_b->k_enemy++;
				game->game_b->enemy_arr[0].flag = 1;
				game->game_b->enemy_arr[0].pos_x = i;
				game->game_b->enemy_arr[0].pos_y = j;
				while ((game->map_data)[j][i])
					i++;
				return (last_pos(game, i, 1));
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

void	mini_init(t_bonus *game_b)
{
	game_b->enemy_arr[0].flag = 0;
	game_b->enemy_arr[0].pos_x = -1;
	game_b->enemy_arr[0].pos_y = -1;
	game_b->enemy_arr[0].right = 1;
	game_b->enemy_arr[0].left = 0;
	game_b->enemy_arr[1].flag = 0;
	game_b->enemy_arr[1].pos_x = -1;
	game_b->enemy_arr[1].pos_y = -1;
	game_b->enemy_arr[1].up = 0;
	game_b->enemy_arr[1].down = 1;
	game_b->anim = 0;
	game_b->k_enemy = 0;
}
