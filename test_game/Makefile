NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L.includes/mlx -lXext -lX11 -lm -lz
includes = includes/mlx/libmlx.a
SRC =	src/main.c \
		src/player.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(includes) $(LFLAGS)

clean:
	rm -rf $(OBJ)


fclean: clean
	rm -rf $(NAME)

make re: fclean all

make reclean: fclean all
	rm -rf $(OBJ)