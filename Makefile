NAME = so_long

SRC = main.c get_next_line.c

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