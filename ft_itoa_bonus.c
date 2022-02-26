#include "so_long.h"

void	ft_sort(char *str, int count)
{
	char	c;
	int		i;

	i = 0;
	while (i <= count - i)
	{
		c = str[count - i];
		str[count - i] = str[i];
		str[i] = c;
		i++;
	}
}

int	ft_itoa(unsigned int n, t_map *game)
{
	char	x[11];
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (n != 0)
	{
		while (n != 0)
		{
			x[i] = ((n % 10) + '0');
			n = n / 10;
			i++;
		}
		x[i] = '\0';
		ft_sort(x, --i);
	}
	else
		x[0] = '0';
	mlx_string_put(game->libx->mlx, game->libx->win, 0, 0, 0x6e1800, x);
	return (0);
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