# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opopov <opopov@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 10:40:02 by opopov            #+#    #+#              #
#    Updated: 2024/11/27 11:44:17 by opopov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := libft.a
SRC_DIR := srcs
INC_DIR := includes
SRC     := ft_isalpha.c ft_isdigit.c \
		ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c \
		ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c \
		ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c \
		ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c \
		ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_split.c

OBJ     := $(SRC:.c=.o)
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: $(SRC_DIR)/%.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
