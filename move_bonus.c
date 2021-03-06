/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:10:25 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:10:27 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void	check_final_img(t_map *game, int i, int j)
{
	if (!game->game_over)
		mlx_string_put(game->libx->mlx, game->libx->win, i, j, \
			0xffff00, "WINNER");
	else
		mlx_string_put(game->libx->mlx, game->libx->win, i, j, \
			0xff0000, "GAME_OVER");
}

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
	check_final_img(game, i, j);
	ft_itoa(++game->steps, game);
	mlx_hook(game->libx->win, 17, 0, &fast_close_bonus, game);
	mlx_hook(game->libx->win, 2, 0, &close_esc_bonus, game);
	mlx_loop(game->libx->mlx);
	return (0);
}
