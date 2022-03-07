NAME = so_long

NAME_B = so_long_bonus

SRC = so_long.c so_long_game_relize.c get_next_line.c so_long_init_and_create.c so_long_main_validation.c so_long_memory_map.c \
		so_long_move_and_close.c move_shell.c

SRC_B = so_long_bonus.c so_long_game_relize_bonus.c get_next_line.c so_long_init_and_create.c so_long_main_validation.c so_long_memory_map.c \
		move_bonus.c so_long_enemy_anim_bonus.c so_long_enemy_utils.c

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

HDR = so_long.h

HDR_B = so_long_bonus.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

FSA = -fsanitize=address

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FSA) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
%.o:	%.c	$(HDR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

bonus:
	@make SRC="$(SRC_B)" NAME="$(NAME_B)" HDR="$(HDR_B)" all

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus