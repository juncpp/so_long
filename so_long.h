#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
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

// typedef struct s_valid
// {
//     int exit;
//     int item;
//     int start;
// }   t_valid;

void	pixels_init(t_map *game, t_render *libx);
void	set_pixel(t_map *game, t_render *libx);
int		init_window(t_map *game, t_render *libx);
void	errors(int errno);
int		get_next_line(char **inp, int fd);
char	*ft_strjoin(char *str, char c);
void	free_map(int flag, char *map);
#endif