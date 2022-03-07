/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy_anim_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:11:31 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:11:33 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_game_over(t_map *game, int x, int y, char c)
{
	if (c != '1' && c != 'E')
	{
		if (game->game_b->enemy_arr[0].right == 1)
		{
			if (game->map_data[y][x + 1] == 'P' || game->map_data[y][x] == 'P')
				game->game_over = -1;
		}
		else
		{
			if (game->map_data[y][x - 1] == 'P' || game->map_data[y][x] == 'P')
				game->game_over = -1;
		}
		if (game->game_over == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_game_over2(t_map *game, int x, int y, char c)
{
	if (c != '1' && c != 'E')
	{
		if (game->game_b->enemy_arr[1].down == 1)
		{
			if (game->map_data[y + 1][x] == 'P' || game->map_data[y][x] == 'P')
			{
				game->game_over = -1;
				return (0);
			}
		}
		else
		{
			if (game->map_data[y - 1][x] == 'P' || game->map_data[y][x] == 'P')
			{
				game->game_over = -1;
				return (0);
			}
		}
	}
	else
		return (0);
	return (1);
}

void	move_second_enemy(t_map *game, t_enemy *enemy_arr, int x, int y)
{
	if (enemy_arr[1].down == 1)
	{
		enemy_arr[1].up = 0;
		if (check_game_over2(game, x, y, game->map_data[y + 1][x]))
			enemy_arr[1].pos_y = y + 1;
		else if (game->map_data[y + 1][x] == '1' || \
					game->map_data[y + 1][x] == 'E')
			enemy_arr[1].up = 1;
	}
	if (enemy_arr[1].up == 1)
	{
		enemy_arr[1].down = 0;
		if (check_game_over2(game, x, y, game->map_data[y - 1][x]))
			enemy_arr[1].pos_y = y - 1;
		else if (game->map_data[y - 1][x] == '1' || \
					game->map_data[y - 1][x] == 'E')
		{
			enemy_arr[1].down = 1;
			if (check_game_over2(game, x, y, game->map_data[y + 1][x]))
				enemy_arr[1].pos_y = y + 1;
		}
	}
}

void	move_first_enemy(t_map *game, t_enemy *enemy_arr, int x, int y)
{
	if (enemy_arr[0].right == 1)
	{
		enemy_arr[0].left = 0;
		if (check_game_over(game, x, y, game->map_data[y][x + 1]))
			enemy_arr[0].pos_x = x + 1;
		else if (game->map_data[y][x + 1] == '1' || \
					game->map_data[y][x + 1] == 'E')
			enemy_arr[0].left = 1;
	}
	if (enemy_arr[0].left == 1)
	{
		enemy_arr[0].right = 0;
		if (check_game_over(game, x, y, game->map_data[y][x - 1]))
			enemy_arr[0].pos_x = x - 1;
		else if (game->map_data[y][x - 1] == '1' || \
					game->map_data[y][x - 1] == 'E')
		{
			enemy_arr[0].right = 1;
			if (check_game_over(game, x, y, game->map_data[y][x + 1]))
				enemy_arr[0].pos_x = x + 1;
		}
	}
}

int	move_enemy(t_map *game, t_enemy *enemy_arr)
{
	int	x;
	int	y;

	x = enemy_arr[0].pos_x;
	y = enemy_arr[0].pos_y;
	if (enemy_arr[0].flag == 1)
	{
		move_first_enemy(game, enemy_arr, x, y);
		if (enemy_arr[1].flag == 1)
		{
			x = enemy_arr[1].pos_x;
			y = enemy_arr[1].pos_y;
			move_second_enemy(game, enemy_arr, x, y);
		}
	}
	else
		return (0);
	return (1);
}
