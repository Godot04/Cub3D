/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:30 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/11 16:55:51 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307

#define PI 3.14159265359

#define WIDTH 1280
#define HEIGHT 720
#define BLOCK_SIZE 64

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}				t_player;

typedef struct	s_img
{
	void	*ptr;
	int		*addr;
	int		bitsinpixel;
	int		line_bytes;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	char		**map;
}				t_game;

int		trgb_to_int(int t, int r, int g, int b);
void	ft_bzero(void *s, size_t n);

void	init_player(t_player *player, char **map);
int		key_pressed(int keycode, t_player *player);
int		key_released(int keycode, t_player *player);
void	move_player(t_game *game);
#endif