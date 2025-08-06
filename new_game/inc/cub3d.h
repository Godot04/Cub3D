/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:30 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/06 13:54:15 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "../../inc/Libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>

# define MAX_LINE_LEN 1024

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define DEBUG 0
# define MINIMAP 1
# define TEXTURE 1
# define VALGRIND 0

# define X 0
# define Y 1

# define ROTATION_SPEED 2.0
# define MOVE_SPEED 3.0

# define PI 3.14159265359

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK_SIZE 48
# define PLAYER_SIZE 16
# define COLLISION_RADIUS 0.25
# define FOV 0.66

# define NORTH 0xFF00FF
# define EAST 0x00FF00
# define SOUTH 0xFFFF00
# define WEST 0x00FFFF

# define MAX_MAP_WIDTH 12
# define MAX_MAP_HEIGHT 8
# define MAP_SIZE 32

typedef struct s_player
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

typedef struct s_img
{
	void	*ptr;
	int		*addr;
	int		bitsinpixel;
	int		line_bytes;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_game
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
	int				tex_w;
	int				tex_h;
	int				max_y;
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

typedef struct s_rc
{
	double	cam_x;
	double	ray[2];
	int		map[2];
	double	side[2];
	double	delta[2];
	int		step[2];
	int		face;
	double	perp_dist;
	double	hit[2];
	int		line_height;
	int		draw[2];
	double	wall_x;
	int		tex_x;
	double	start[2];
	double	end[2];
}				t_rc;

void	draw_square(int xy[2], int size, int color, t_game *game);
void	draw_map(t_game *game);
void	draw_line(t_game *game, t_rc *rc);
void	draw_ceiling_and_floor(t_game *game);
void	draw_texture(t_game *game, t_rc *rc, int x);

void	init_player(t_player *player, char **map);
int		key_pressed(int keycode, t_game *game);
int		key_released(int keycode, t_game *game);

int		open_file_check(char *file_path);
int		ft_cub(char *file_path);

int		rgb_extracter(t_game *game, char *term_input, char t);
int		path_extracter(char **dest, char *term_input);
int		cub_input_reader(t_game *game);

char	*read_line(int fd);
int		cmp_string(t_game *game, char *tmp);
int		res_check(t_game *game);
int		rgb_res_check(t_game *game, int *colors, int i, char t);
int		rgb_number_extract(char **tmp, int *colors, int i);

void	put_pixel(t_img *img, int x, int y, int color);

int		map_free(char **map);
int		is_map_correct(char **map);

int		map_skip_lines(int *fd, char **first_line, t_game *game);
char	**map_malloc(char *first_line, t_game *game);
int		map_readline(int fd_read, char **map, t_game *game);

int		wall_counter(char **map);
void	map_xy_count(char **map, int *ox, int *oy);
void	map_fill(char **map);
char	*skip_additional_lines(int fd);
int		map_input_reader(t_game *game);

int		lines_counter(int fd);
int		is_line_empty(char *line);
int		space_skip(char *str);
int		fill_v(char **map_copy, int y, int x, char **map);
int		player_spawn_search(int *y, int *x, char **map);

void	draw_minimap(t_game *game, t_player *player);

void	move_player(t_game *game);

void	ray_caster(t_game *game);

void	angles_declaration(float angles[8]);
void	clean_path(t_game *game);
void	clean_ptrs(t_game *game);
void	init_game_ptrs(t_game *game);
int		is_line_contains_digit(char *line);

int		ft_isspace(char c);
int		trgb_to_int(int t, int r, int g, int b);
int		close_game(t_game *game);
int		is_wall(t_game *data, float x, float y);

#endif
