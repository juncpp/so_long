#include "so_long_bonus.h"

void	check_image(t_render *libx, t_map *game, int i, int j)
{
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
	if ((game->map_data)[j][i] == 'N')
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
				(game->map_data)[j][i] = 'N';
				game->game_b->k_enemy++;
				return (1);
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
	if (game->game_b->k_enemy == 0)
	{
		while ((game->map_data)[j])
		{
			while ((game->map_data)[j][i])
			{
				if ((game->map_data)[j][i] == '0')
				{
					(game->map_data)[j][i] = 'N';
					game->game_b->k_enemy++;
					while ((game->map_data)[j][i])
						i++;
					return (last_pos(game, i, 1));
				}
				i++;
			}
			i = 0;
			j++;
		}
	}
	return (0);
}

void	set_pixel(t_map *game, t_render *libx, int i, int j)
{
	put_enemy(game, 0, 1);
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
	if (game->game_b->pos == 0)
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude1.xpm", \
			&x, &y);
		game->game_b->pos = 1;
	}
	else
	{
		game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude2.xpm", \
			&x, &y);
		game->game_b->pos = 0;
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
	game_b->pos = 0;
	game_b->k_enemy = 0;
}

int	move_game_bonus(int keycode, t_map *game)
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

void	main_game_relize(t_map **game)
{
	(*game)->libx = (t_render *)malloc(sizeof(t_render));
	if (!(*game)->libx)
		free_matrix(*game, -2, (*game)->map_data, NULL);
	(*game)->game_b = (t_bonus *)malloc(sizeof(t_bonus));
	if (!(*game)->game_b)
	{
		free((*game)->libx);
		free_matrix(*game, -2, (*game)->map_data, NULL);
	}
	mini_init((*game)->game_b);
	(*game)->libx->mlx = mlx_init();
	(*game)->libx->win = mlx_new_window((*game)->libx->mlx, (*game)->map_width, \
		(*game)->map_height, "./so_long");
	mlx_hook((*game)->libx->win, 2, 0, &move_game_bonus, *game);
	mlx_hook((*game)->libx->win, 17, 0, &fast_close, *game);
	pixels_init(*game, (*game)->libx);
	ft_itoa((*game)->steps, *game);
	mlx_loop((*game)->libx->mlx);
}