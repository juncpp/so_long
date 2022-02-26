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

int	last_img(t_map *game, int i, int j)
{
	while ((game->map_data)[j])
	{
		while ((game->map_data)[j][i])
		{
			mlx_put_image_to_window(game->libx->mlx, game->libx->win, \
			game->end_img, i * 32, j * 32);
			i++;
		}
		j++;
		i = 0;
	}
	game->end_img = mlx_xpm_file_to_image(game->libx->mlx, "Texture/end1.xpm", \
		&i, &j);
	j = (game->map_height / 4);
	i = ((game->map_width / 64) * 26);
	mlx_put_image_to_window(game->libx->mlx, game->libx->win, \
		game->end_img, (game->map_width / 4), j);
	mlx_string_put(game->libx->mlx, game->libx->win, i, j, 0xffff00, "WINNER");
	mlx_hook(game->libx->win, 17, 0, &fast_close, game);
	mlx_hook(game->libx->win, 2, 0, &close_esc, game);
	mlx_loop(game->libx->mlx);
	return (0);
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