#include "so_long.h"

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
	ft_itoa(game->steps++, game);
	mlx_hook(game->libx->win, 17, 0, &fast_close, game);
	mlx_hook(game->libx->win, 2, 0, &close_esc, game);
	mlx_loop(game->libx->mlx);
	return (0);
}