#include "so_long_bonus.h"

void	check_image(t_render *libx, t_map *game, int i, int j)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = game->game_b->enemy_arr[0].pos_x;
	y1 = game->game_b->enemy_arr[0].pos_y;
	x2 = game->game_b->enemy_arr[1].pos_x;
	y2 = game->game_b->enemy_arr[1].pos_y;
	if ((game->map_data)[j][i] != '1')
		mlx_put_image_to_window(libx->mlx, libx->win, game->floor, \
			i * 32, j * 32);
	else
		mlx_put_image_to_window(libx->mlx, libx->win, game->wall, \
			i * 32, j * 32);
	if ((game->map_data)[j][i] == 'C')
		mlx_put_image_to_window(libx->mlx, libx->win, game->items, \
			i * 32, j * 32);
	if ((game->map_data)[j][i] == 'E')
		mlx_put_image_to_window(libx->mlx, libx->win, game->exit, \
			i * 32, j * 32);
	if ((i == x1 && j == y1) || (i == x2 && j == y2))
		mlx_put_image_to_window(libx->mlx, libx->win, game->game_b->enemy, \
			i * 32, j * 32);
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

void	pixels_init(t_map *game, t_render *libx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->floor = mlx_xpm_file_to_image(libx->mlx, "Texture/floor.xpm", &x, &y);
	if (game->game_b->anim == 0)
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude1.xpm", \
			&x, &y);
		game->game_b->anim = 1;
	}
	else
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude2.xpm", \
			&x, &y);
		game->game_b->anim = 0;
	}
	game->wall = mlx_xpm_file_to_image(libx->mlx, "Texture/wall.xpm", &x, &y);
	game->items = mlx_xpm_file_to_image(libx->mlx, "Texture/item.xpm", &x, &y);
	game->exit = mlx_xpm_file_to_image(libx->mlx, "Texture/exit.xpm", &x, &y);
	game->end_img = mlx_xpm_file_to_image(libx->mlx, "Texture/win.xpm", &x, &y);
	game->game_b->enemy = mlx_xpm_file_to_image(libx->mlx, "Texture/enemy.xpm", \
		&x, &y);
	set_pixel(game, libx, 0, 0);
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
					game->map_data[y + 1][x] == 'E')
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
					game->map_data[y][x + 1] == 'E')
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
		pixels_init(game, game->libx);
		ft_itoa(++(game->steps), game);
	}
	return (1);
}

int	move_game_bonus(int keycode, t_map *game)
{
	close_esc(keycode, game);
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
		free(game->game_b);
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
	mlx_hook((*game)->libx->win, 17, 0, &fast_close, *game);
	pixels_init(*game, (*game)->libx);
	ft_itoa((*game)->steps, *game);
	mlx_loop((*game)->libx->mlx);
}