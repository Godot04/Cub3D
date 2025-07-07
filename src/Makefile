NAME = Cub3D
SRC = main.c
OBJ = $(SRC:.c=.o)
CC = gcc

CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ../inc/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm

LIBFT_DIR = ../inc/Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
