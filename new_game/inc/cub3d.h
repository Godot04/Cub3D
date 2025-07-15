/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:30 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/15 17:26:00 by silpaukn         ###   ########.fr       */
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
#include <limits.h>

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307

#define DEBUG 0
#define MINIMAP 1
#define TEXTURE 1

#define PI 3.14159265359

#define WIDTH 1920
#define HEIGHT 1080
#define BLOCK_SIZE 96
#define PLAYER_SIZE 16
#define FOV 0.66

#define NORTH 0xFF00FF
#define EAST 0x00FF00
#define SOUTH 0xFFFF00
#define WEST 0x00FFFF

#define PATH_NORTH "textures/north_wall.xpm"
#define PATH_EAST "textures/east_wall.xpm"
#define PATH_SOUTH "textures/south_wall.xpm"
#define PATH_WEST "textures/west_wall.xpm"

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define MAX_MAP_WIDTH 10
#define MAX_MAP_HEIGHT 7
#define MAP_SIZE 32

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
	void			*mlx;
	void			*win;
	t_img			img;
	t_player		player;
	char			**map;
	int				crgb;
	int				frgb;
	struct timeval	last_frame;
	t_img			north;
	t_img			east;
	t_img			south;
	t_img			west;
}				t_game;

int		trgb_to_int(int t, int r, int g, int b);
void	ft_bzero(void *s, size_t n);
int		close_game(t_game *game);

void	init_player(t_player *player, char **map);
int		key_pressed(int keycode, t_game *game);
int		key_released(int keycode, t_game *game);
void	move_player(t_game *game);

void	put_pixel(t_img *img, int x, int y, int color);
void	draw_square(int x, int y, int size, int color, t_game *game);
char	**get_map(void);

void	draw_minimap(t_game *game, t_player *player);
size_t	ft_strlen(const char *s);
int		get_height(char **map);
#endif