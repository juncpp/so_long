#include "so_long.h"

void    errors(int errno)
{
    if (errno <= 0)
    {
        perror("An error has occurred ");
        strerror(errno);    
        if (errno == -2)
            write(2, "Memory allocation error!\n", 25);
        if (errno == -1)
            write(2, "Map not valid!\n", 15);
        if (errno == 0)
            write(2, "File is wrong\n", 14);
    }
    exit(0);
}

int check_file(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    i--;
    if (str[i] == 'r' && str[i - 1] == 'e' && str[i - 2] == 'b' && str[i - 3] == '.')
        return (1);
    return (0);
}

void    free_map(int flag, char *map)
{
    free(map);
    if (flag < 0)
        errors(flag);
//    free_map(map);
}

void    put_map(char **map);

int mem_for_map_data(char *s)
{
    int i;
    int count;

    count = 1;
    i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
        {
            count++;
            if (s[i + 1] == '\0')
                return (count);
        }
        i++;
    }
    return (++count);
}

char    *open_file(char *str)
{
    int     fd;
    char    *map;
    int     flag;

    fd = open(str, O_RDONLY);
    map = NULL;
	if (fd != -1)
    {
        flag = get_next_line(&map, fd);
        close(fd);
        if (flag < 0)
            errors(0);
    }
    else
        errors(0);
    return (map);
}

int count_line(char *map)
{
    int i;
    int counter;

    counter = 1;
    i = 0;
    while (map[i])
    {
        if (map[i] == '\n')
        {
            if (map[i + 1] == '\0')
                return (counter);
            counter++;
        }
        i++;
    }
    return (counter);
}

int len_line(char *str, int *checkpoint)
{
    static int i;

    *checkpoint = i;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            ++i;
            return (i - 1);
        }
        i++;
    }
    return (i);
}

void    free_matrix(t_map *game, int flag, char **matrix, char *map)
{
    int j;

    j = 0;
    if (map != NULL)
        free(map);
    while (matrix[j] != NULL)
        free(matrix[j++]);
    free(matrix);
    free(game);
	if (flag == -1)
    	errors(flag);
}

void    ft_strcpy(char *dest, char *src, int start)
{
    int i;

    i = 0;
    while (src[start] != '\n' && src[start])
    {
        dest[i] = src[start];
        i++;
        start++;
    }
    dest[i] = '\0';
}

void create_matrix(t_map *game, char **str)
{
    char    **matrix;
    int     n;
    int     i;
    int     start;
    int     size;

    start = 0;
    i = 0;
    n = count_line(*str);
    matrix = (char **)malloc((n + 1) * sizeof(char *));
    if (!matrix)
        free_map(-2, *str);
    while (i < n)
    {
        size = len_line(*str , &start);
        matrix[i] = (char *)malloc(sizeof(char) * (size - start + 1));
        if (!matrix[i])
            free_matrix(game, -2, matrix, *str);
        ft_strcpy(matrix[i], *str, start);
        i++;
    }
    matrix[i] = NULL;
    free(*str);
    game->map_data = matrix;
}


t_map *all_init(char **av)
{
    t_map   *game;
    char    *map;

    game = (t_map *)malloc(sizeof(t_map));
    if (!game)
        errors(-2);
    game->game_over = 0;
    game->map_height = 0;
    game->map_width = 0;
    game->max_score = 0;
    game->player_pos_x = 0;
    game->player_pos_y = 0;
    game->steps = 0;
    game->counter_player = 0;
    map = open_file(av[1]);
    create_matrix(game, &map);
    return (game);
}

int check_border(char *line, int j)
{
    int i;

    i = 0;
    if (j == 0)
    {
        while (line[i])
        {
            if (line[i] != '1')
                return(0);
            i++;
        }
    }
    else
    {
        while (line[i + 1])
            i++;
        if (line[0] != '1' || line[i] != '1')
            return (0);
    }
    return (1);
}

void    check_rectangle(t_map *game)
{
    int i;
    int j;
    int count;

    i = 0;
    j = 0;
    while((game->map_data)[j] != NULL)
    {
        while ((game->map_data)[j][i] != '\0')
            i++;
        if (j == 0)
            count = i;
        if (count != i)
            free_matrix(game, -1, game->map_data, NULL);
        i = 0;
        j++;
        if (!check_border((game->map_data)[j - 1], j - 1))
            free_matrix(game, -1, game->map_data, NULL);
    }
    if (j < 3)
        free_matrix(game, -1, game->map_data, NULL);
    if (!check_border((game->map_data)[j - 1], 0))
            free_matrix(game, -1, game->map_data, NULL);
    game->map_height = j * 32;
    game->map_width = count * 32;
}

void	set_pole(char c, t_map *game, int i, int j)
{
	if (c == 'P')
	{
		game->player_pos_x = i;
		game->player_pos_y = j;
		game->counter_player++;
	}
	if (c == 'C')
		game->max_score++;
	if (c == 'E')
		game->game_over = 1;
}

void	check_game_rules(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((game->map_data)[j] != NULL)
	{
		while ((game->map_data)[j][i])
		{
			set_pole((game->map_data)[j][i], game, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	if (game->game_over == 0 || game->counter_player != 1 || game->max_score == 0)
		free_matrix(game, -1, game->map_data, NULL);
}

void	main_validation(t_map **game)
{
	check_rectangle(*game);
	check_game_rules(*game);
}

int	move_w(t_map *game, int i, int j)
{
	if ((game->map_data)[j - 1][i] != '1')
	{
		if ((game->map_data)[j - 1][i] == 'C')
			game->max_score--;
		else if ((game->map_data)[j - 1][i] == 'E')
		{
			if (!game->max_score)
				game->game_over = 0;
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j - 1][i] = 'P';
		game->player_pos_y = j - 1;
		game->steps++;
		pixels_init(game, game->libx);
	}
	return (1);
}

int	move_a(t_map *game, int i, int j)
{
	if ((game->map_data)[j][i - 1] != '1')
	{
		if ((game->map_data)[j][i - 1] == 'C')
			game->max_score--;
		else if ((game->map_data)[j][i - 1] == 'E')
		{
			if (!game->max_score)
				game->game_over = 0;
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j][i - 1] = 'P';
		game->player_pos_x = i - 1;
		game->steps++;
		pixels_init(game, game->libx);
	}
	return (1);
}

int	move_s(t_map *game, int i, int j)
{
	if ((game->map_data)[j + 1][i] != '1')
	{
		if ((game->map_data)[j + 1][i] == 'C')
			game->max_score--;
		else if ((game->map_data)[j + 1][i] == 'E')
		{
			if (!game->max_score)
				game->game_over = 0;
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j + 1][i] = 'P';
		game->player_pos_y = j + 1;
		game->steps++;
		pixels_init(game, game->libx);
	}
	return (1);
}

int	move_d(t_map *game, int i, int j)
{
	if ((game->map_data)[j][i + 1] != '1')
	{
		if ((game->map_data)[j][i + 1] == 'C')
			game->max_score--;
		else if ((game->map_data)[j][i + 1] == 'E')
		{
			if (!game->max_score)
				game->game_over = 0;
			else
				return (0);
		}
		(game->map_data)[j][i] = '0';
		(game->map_data)[j][i + 1] = 'P';
		game->player_pos_x = i + 1;
		game->steps++;
		pixels_init(game, game->libx);
	}
	return (1);
}

int	move_game(int keycode, t_map *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->libx->mlx, game->libx->win);
		free(game->libx);
		free_matrix(game, 1, game->map_data, NULL);
		exit(0);
	}
	if (keycode == 13)
		move_w(game, game->player_pos_x , game->player_pos_y);
	else if (keycode == 0)
		move_a(game, game->player_pos_x , game->player_pos_y);
	else if (keycode == 1)
		move_s(game, game->player_pos_x , game->player_pos_y);
	else if (keycode == 2)
		move_d(game, game->player_pos_x , game->player_pos_y);
	if (!game->game_over)
	{
		mlx_destroy_window(game->libx->mlx, game->libx->win);
		free(game->libx);
		free_matrix(game, 1, game->map_data, NULL);
		exit(0);
	}
	if (keycode == 12912)
		exit(0);
	printf("%lu\n", game->steps);
//	mlx_string_put(game->libx->mlx,game->libx->win, 0, 0, 0, game->steps);
	return (0);
}

void	set_pixel(t_map *game, t_render *libx)
{
	int	i;
	int	j;	

	i = 0;
	j = 0;
	while ((game->map_data)[j])
	{
		while ((game->map_data)[j][i])
		{
			if ((game->map_data)[j][i] != '1')
				mlx_put_image_to_window(libx->mlx, libx->win, game->floor, i * 32, j * 32);
			else
				mlx_put_image_to_window(libx->mlx, libx->win, game->wall, i * 32, j * 32);
			if ((game->map_data)[j][i] == 'C')
				mlx_put_image_to_window(libx->mlx, libx->win, game->items, i * 32, j * 32);
			if ((game->map_data)[j][i] == 'E')
				mlx_put_image_to_window(libx->mlx, libx->win, game->exit, i * 32, j * 32);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(libx->mlx, libx->win, game->player, game->player_pos_x * 32, game->player_pos_y * 32);
}

void	pixels_init(t_map *game, t_render *libx)
{
	game->floor = mlx_xpm_file_to_image(libx->mlx, "Texture/floor.xpm", &(game->map_width), &(game->map_height));
	game->player = mlx_xpm_file_to_image(libx->mlx, "Texture/dude.xpm", &(game->map_width), &(game->map_height));
	game->wall = mlx_xpm_file_to_image(libx->mlx, "Texture/wall.xpm", &(game->map_width), &(game->map_height));
	game->items = mlx_xpm_file_to_image(libx->mlx, "Texture/item.xpm", &(game->map_width), &(game->map_height));
	game->exit = mlx_xpm_file_to_image(libx->mlx, "Texture/exit.xpm", &(game->map_width), &(game->map_height));
	set_pixel(game, libx);
}

void	main_game_relize(t_map **game)
{
	// t_render	*libx;

	(*game)->libx = (t_render *)malloc(sizeof(t_render));
	if (!(*game)->libx)
		free_matrix(*game, -2, (*game)->map_data, NULL);
	
	(*game)->libx->mlx = mlx_init();
	(*game)->libx->win = mlx_new_window((*game)->libx->mlx, (*game)->map_width, (*game)->map_height, "LETS GO!");
	// printf ("%d\n",mlx_hook(libx->win, 2, 0, &move_game, libx));
	mlx_hook((*game)->libx->win, 2, 0, &move_game, *game);
	mlx_hook((*game)->libx->win, 17, 0, &move_game, *game);
	pixels_init(*game, (*game)->libx);
	mlx_loop((*game)->libx->mlx);
}

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
			errors(-2);
	}
	return (0);
}

// printf ("p_count = %d e = %d p_x = %d p_y = %d count_c = %d\n", (*game)->counter_player, (*game)->game_over, (*game)->player_pos_x, (*game)->player_pos_y, (*game)->max_score);