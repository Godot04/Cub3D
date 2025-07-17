/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:30 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/17 13:11:09 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include "../../inc/Libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307

#define DEBUG 0
#define MINIMAP 1
#define PI 3.14159265359

#define WIDTH 1920
#define HEIGHT 1080
#define BLOCK_SIZE 96
#define PLAYER_SIZE 16
#define COLLISION_RADIUS 0.3
#define FOV 0.66

#define NORTH 0xFF00FF
#define EAST 0x00FF00
#define SOUTH 0xFFFF00
#define WEST 0x00FFFF

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

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
	int			map_width;
	int			map_height;
	int			crgb;
	int			frgb;
	struct timeval	last_frame;
}				t_game;

int		trgb_to_int(int t, int r, int g, int b);
void	ft_bzero(void *s, size_t n);
int		close_game(t_game *game);

void	init_player(t_player *player, char **map);
int		key_pressed(int keycode, t_game *game);
int		key_released(int keycode, t_game *game);
void	move_player(t_game *game);
int		is_wall(t_game *data, float x, float y);
int		ft_isspace(char c);
void	map_fill(char **map);
void	map_xy_count(char **map, int *ox, int *oy);
int		wall_counter(char **map);
int		is_map_correct(char **map);
int		player_spawn_search(int *y, int *x, char **map);
int		fill_v(char **map_copy, int y, int x, int width, int height);
int		wall_search(int *ox, int *oy, char **map);

#endif
