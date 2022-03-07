/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:11:09 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:11:11 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
