NAME = cub3d
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L.inc/mlx -lXext -lX11 -lm -lz
includes = inc/mlx/libmlx.a
SRC =	src/main.c \
		src/utils.c \
		src/player.c \

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