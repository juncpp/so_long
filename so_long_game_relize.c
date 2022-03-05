#include "so_long.h"

void	set_pixel(t_map *game, t_render *libx, int i, int j)
{
	while ((game->map_data)[j])
	{
		while ((game->map_data)[j][i])
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
	game->floor = mlx_xpm_file_to_image(libx->mlx, "Texture/floor.xpm", \
		&x, &y);
	game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude1.xpm", \
		&x, &y);
	game->wall = mlx_xpm_file_to_image(libx->mlx, "Texture/wall.xpm", \
		&x, &y);
	game->items = mlx_xpm_file_to_image(libx->mlx, "Texture/item.xpm", \
		&x, &y);
	game->exit = mlx_xpm_file_to_image(libx->mlx, "Texture/exit.xpm", \
		&x, &y);
	game->end_img = mlx_xpm_file_to_image(libx->mlx, "Texture/win.xpm", \
		&x, &y);
	set_pixel(game, libx, 0, 0);
}

void	main_game_relize(t_map **game)
{
	(*game)->libx = (t_render *)malloc(sizeof(t_render));
	if (!(*game)->libx)
		free_matrix(*game, -2, (*game)->map_data, NULL);
	(*game)->libx->mlx = mlx_init();
	(*game)->libx->win = mlx_new_window((*game)->libx->mlx, (*game)->map_width, \
		(*game)->map_height, "LETS GO!");
	mlx_hook((*game)->libx->win, 2, 0, &move_game, *game);
	mlx_hook((*game)->libx->win, 17, 0, &fast_close, *game);
	pixels_init(*game, (*game)->libx);
	ft_itoa((*game)->steps, *game);
	mlx_loop((*game)->libx->mlx);
}