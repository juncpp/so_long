/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:11:14 by mmeredit          #+#    #+#             */
/*   Updated: 2022/03/07 18:11:23 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_render
{
	void	*mlx;
	void	*win;
}	t_render;

typedef struct s_enemy
{
	int	flag;
	int	pos_x;
	int	pos_y;
	int	up;
	int	down;
	int	right;
	int	left;
}	t_enemy;

typedef struct s_bonus
{
	int		anim;
	int		k_enemy;
	void	*enemy;
	t_enemy	*enemy_arr;
}	t_bonus;

typedef struct s_basic
{
	char				**map_data;
	int					map_height;
	int					map_width;
	int					player_pos_x;
	int					player_pos_y;
	int					max_score;
	int					game_over;
	unsigned long int	steps;
	int					counter_player;
	void				*end_img;
	void				*wall;
	void				*exit;
	void				*player;
	void				*items;
	void				*floor;
	t_render			*libx;
	t_bonus				*game_b;
}	t_map;

void	check_image(t_render *libx, t_map *game, int i, int j);
void	mini_init(t_bonus *game_b);
int		put_enemy(t_map *game, int i, int j);
int		last_pos(t_map *game, int i, int j);
int		move_enemy(t_map *game, t_enemy *enemy_arr);
void	move_first_enemy(t_map *game, t_enemy *enemy_arr, int x, int y);
void	move_second_enemy(t_map *game, t_enemy *enemy_arr, int x, int y);
int		check_game_over2(t_map *game, int x, int y, char c);
int		check_game_over(t_map *game, int x, int y, char c);
void	main_game_relize(t_map **game);
int		last_img(t_map *game, int i, int j);
int		move_all_bonus(t_map *game, int x, int y);
void	set_pixel(t_map *game, t_render *libx, int i, int j);
int		close_esc_bonus(int keycode, t_map *game);
int		fast_close_bonus(t_map *game);
void	ft_sort(char *str, int count);
int		ft_itoa(unsigned int n, t_map *game);
int		move_all(t_map *game, int x, int y);
int		move_game_bonus(int keycode, t_map *game);
int		last_img(t_map *game, int i, int j);
void	check_game_rules(t_map *game);
void	main_validation(t_map **game);
int		check_border(char *line, int j);
void	check_rectangle(t_map *game);
void	free_matrix(t_map *game, int flag, char **matrix, char *map);
void	ft_strcpy(char *dest, char *src, int start);
int		len_line(char *str, int *checkpoint);
int		count_line(char *map);
void	create_matrix(t_map *game, char **str);
char	*open_file(char *str);
t_map	*all_init(char **av);
int		check_file(char *str);
void	pixels_init(t_map *game, t_render *libx, int x, int y);
void	set_pixel(t_map *game, t_render *libx, int i, int j);
int		init_window(t_map *game, t_render *libx);
void	errors(int errno);
int		get_next_line(char **inp, int fd);
char	*ft_strjoin(char *str, char c);
void	free_map(int flag, char *map);
void	free_matrix(t_map *game, int flag, char **matrix, char *map);
#endif
