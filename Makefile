NAME = so_long

SRC = main.c get_next_line.c so_long_init_and_create.c so_long_main_validation.c so_long_memory_map.c \
		so_long_move_and_close.c so_long_last_count_move.c

OBJ = $(SRC:.c=.o)

HDR = so_long.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

FSA = -fsanitize=address

all:	$(NAME)

$(NAME): $(OBJ) $(HDR)
	$(CC) $(FSA) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
%.o:	%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus