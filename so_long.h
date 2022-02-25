#ifndef SO_LONG_H
# define SO_LONG_H
//# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_render
{
	void	*mlx;
	void	*win;
}	t_render;

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
}	t_map;

int		last_img(t_map *game, int i, int j);
int		move_all(t_map *game, int x, int y);
void	set_pixel(t_map *game, t_render *libx, int i, int j);
int		close_esc(int keycode, t_map *game);
int		fast_close(t_map *game);
void	ft_sort(char *str, int count);
int		ft_itoa(unsigned int n, t_map *game);
int		move_all(t_map *game, int x, int y);
int		move_game(int keycode, t_map *game);
int		last_img(t_map *game, int i, int j);
void	check_game_rules(t_map *game);
void	main_validation(t_map **game);
void	check_game_rules(t_map *game);
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
void	pixels_init(t_map *game, t_render *libx);
void	set_pixel(t_map *game, t_render *libx, int i, int j);
int		init_window(t_map *game, t_render *libx);
void	errors(int errno);
int		get_next_line(char **inp, int fd);
char	*ft_strjoin(char *str, char c);
void	free_map(int flag, char *map);
void	free_matrix(t_map *game, int flag, char **matrix, char *map);
#endif