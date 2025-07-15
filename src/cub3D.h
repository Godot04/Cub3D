/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:28:46 by opopov            #+#    #+#             */
/*   Updated: 2025/07/14 16:16:09 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minilibx-linux/mlx.h"
#include "../inc/Libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#define GREY 0x808080
#define YELLOW 0xFFFF00
#define GREEN 0x00FF00

#define PLAYER_SIZE 20
#define PLAYER_COLISION_RADIUS 10
#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define MS 1.0
#define RS 0.2

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int		p_height;
	int		p_width;
	int		p_color;
	float	p_speed;
	float	p_angle;
	float	p_angle_speed;
	int		is_key_w;
	int		is_key_a;
	int		is_key_s;
	int		is_key_d;
	int		is_left_rotate;
	int		is_right_rotate;

} t_player;

#define PI 3.14159265359
#define ESC 65307
#define WALL_SIZE 60
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

typedef struct s_data
{
	void		*mlx;
	void		*window;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	// background
	void		*background;
	char		*background_addr;

	// map
	int			map[MAP_HEIGHT][MAP_WIDTH];

	// player
	t_player	*player;

	// wall
	void		*wall;
	int			w_height;
	int			w_width;
}	t_data;


int		key_pressed(int key, t_data *data);
int		key_released(int key, t_data *data);
int		p_movement(t_data *data);
void	player_draw(t_data *data);
void	wall_draw(t_data *data);
void	background_draw(t_data *data);
int		close_window(t_data *data);
int		is_wall(t_data *data, float x, float y);
