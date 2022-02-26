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
		return (write(1, "MOVES: 0\n", 9));
	// while (x[j])
	// 	write(1, &x[j++], 1);
	return (0);
//	mlx_string_put(game->libx->mlx, game->libx->win, 0, 0, 0x6e1800, x);
}
