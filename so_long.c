#include "so_long.h"

int	main(int ag, char **av)
{
	t_map	*game;

	if (ag == 2)
	{
		if (check_file(av[1]))
		{
			game = all_init(av);
			main_validation(&game);
			main_game_relize(&game);
		}
		else
			errors(-3);
	}
	else
		errors(-4);
	return (0);
}