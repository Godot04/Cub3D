/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:30 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/28 14:58:28 by opopov           ###   ########.fr       */
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
#include <fcntl.h>

#define MAX_LINE_LEN 1024

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
#define COLLISION_RADIUS 0.3
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
	char			*file_path;
	int				crgb;
	int				c_r;
	int				c_g;
	int				c_b;
	int				frgb;
	int				f_r;
	int				f_g;
	int				f_b;
	struct timeval	last_frame;
	t_img			north;
	t_img			east;
	t_img			south;
	t_img			west;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
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
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_square(int x, int y, int size, int color, t_game *game);
char	**get_map(t_game *game);
void	draw_minimap(t_game *game, t_player *player);
size_t	ft_strlen(const char *s);
int		get_height(char **map);
int		cub_input_reader(t_game *game);
int		space_skip(char *str);
int		ft_cub(char *file_path);
int		open_file_check(char *file_path);
char	*read_line(int fd);
int		map_input_reader(t_game *game);
int		is_line_empty(char *line);
int		lines_counter(int fd);

#endif
