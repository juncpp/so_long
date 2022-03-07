/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_relize_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:12:03 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:12:04 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_pixel(t_map *game, t_render *libx, int i, int j)
{
	while ((game->map_data)[j])
	{
		while ((game->map_data)[j][i])
		{
			check_image(libx, game, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(libx->mlx, libx->win, game->player, \
		game->player_pos_x * 32, game->player_pos_y * 32);
}

void	pixels_init(t_map *game, t_render *libx, int x, int y)
{
	game->floor = mlx_xpm_file_to_image(libx->mlx, "Texture/floor.xpm", &x, &y);
	if (game->game_b->anim == 0)
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude1.xpm", \
			&x, &y);
		game->game_b->enemy = mlx_xpm_file_to_image(libx->mlx, \
			"Texture/enemy1.xpm", &x, &y);
		game->game_b->anim = 1;
	}
	else
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude2.xpm", \
			&x, &y);
			game->game_b->enemy = mlx_xpm_file_to_image(libx->mlx, \
			"Texture/enemy2.xpm", &x, &y);
		game->game_b->anim = 0;
	}
	game->wall = mlx_xpm_file_to_image(libx->mlx, "Texture/wall.xpm", &x, &y);
	game->items = mlx_xpm_file_to_image(libx->mlx, "Texture/item.xpm", &x, &y);
	game->exit = mlx_xpm_file_to_image(libx->mlx, "Texture/exit.xpm", &x, &y);
	game->end_img = mlx_xpm_file_to_image(libx->mlx, "Texture/win.xpm", &x, &y);
	set_pixel(game, libx, 0, 0);
}

int	move_all_bonus(t_map *game, int x, int y)
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
				return (--game->game_over);
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j + y][i + x] = 'P';
		game->player_pos_x = i + x;
		game->player_pos_y = j + y;
		move_enemy(game, game->game_b->enemy_arr);
		pixels_init(game, game->libx, 0, 0);
		ft_itoa(++(game->steps), game);
	}
	return (1);
}

int	move_game_bonus(int keycode, t_map *game)
{
	close_esc_bonus(keycode, game);
	if (keycode == 13)
		move_all_bonus(game, 0, -1);
	else if (keycode == 0)
		move_all_bonus(game, -1, 0);
	else if (keycode == 1)
		move_all_bonus(game, 0, 1);
	else if (keycode == 2)
		move_all_bonus(game, 1, 0);
	if (!game->game_over || game->game_over == -1)
	{
		mlx_clear_window(game->libx->mlx, game->libx->win);
		last_img(game, 0, 0);
	}
	return (0);
}

void	main_game_relize(t_map **game)
{
	t_enemy	enemy_arr[2];

	(*game)->libx = (t_render *)malloc(sizeof(t_render));
	if (!(*game)->libx)
		free_matrix(*game, -2, (*game)->map_data, NULL);
	(*game)->game_b = (t_bonus *)malloc(sizeof(t_bonus));
	if (!(*game)->game_b)
	{
		free((*game)->libx);
		free_matrix(*game, -2, (*game)->map_data, NULL);
	}
	(*game)->game_b->enemy_arr = enemy_arr;
	mini_init((*game)->game_b);
	put_enemy(*game, 0, 1);
	(*game)->libx->mlx = mlx_init();
	(*game)->libx->win = mlx_new_window((*game)->libx->mlx, (*game)->map_width, \
		(*game)->map_height, "./so_long");
	mlx_hook((*game)->libx->win, 2, 0, &move_game_bonus, *game);
	mlx_hook((*game)->libx->win, 17, 0, &fast_close_bonus, *game);
	pixels_init(*game, (*game)->libx, 0, 0);
	ft_itoa((*game)->steps, *game);
	mlx_loop((*game)->libx->mlx);
}
