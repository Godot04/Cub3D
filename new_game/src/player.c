/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:50:45 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:30 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	get_x(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)x + 0.5);
			x++;
		}
		y++;
	}
	return (1.5);
}

float	get_y(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)y + 0.5);
			x++;
		}
		y++;
	}
	return (1.5);
}

void	init_player2(t_player *player, char facing)
{
	if (facing == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = FOV;
	}
	if (facing == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = FOV;
		player->plane_y = 0.0;
	}
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_player(t_player *player, char **map)
{
	char	facing;

	player->pos_x = get_x(map);
	player->pos_y = get_y(map);
	facing = map[(int)get_y(map)][(int)get_x(map)];
	if (facing == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -FOV;
	}
	if (facing == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -FOV;
		player->plane_y = 0.0;
	}
	init_player2(player, facing);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == ESC)
		close_game(game);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	return (0);
}

void	rotate(t_game *game, double r_s)
{
	double	dir;
	double	p;

	if (game->player.left_rotate)
	{
		dir = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-r_s)
			- game->player.dir_y * sin(-r_s);
		game->player.dir_y = dir * sin(-r_s) + game->player.dir_y * cos(-r_s);
		p = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-r_s)
			- game->player.plane_y * sin(-r_s);
		game->player.plane_y = p * sin(-r_s) + game->player.plane_y * cos(-r_s);
	}
	if (game->player.right_rotate)
	{
		dir = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(r_s)
			- game->player.dir_y * sin(r_s);
		game->player.dir_y = dir * sin(r_s) + game->player.dir_y * cos(r_s);
		p = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(r_s)
			- game->player.plane_y * sin(r_s);
		game->player.plane_y = p * sin(r_s) + game->player.plane_y * cos(r_s);
	}
}

void	collision(t_game *game, double dir_x, double dir_y, double speed)
{
	double	len;
	double	tmp_x;
	double	tmp_y;

	if ((dir_x != 0 || dir_y != 0))
	{
		len = sqrt(dir_x * dir_x + dir_y * dir_y);
		tmp_x = game->player.pos_x + (dir_x / len) * speed;
		tmp_y = game->player.pos_y + (dir_y / len) * speed;
	}
	else
		return ;
	if (!is_wall(game, tmp_x, tmp_y))
	{
		game->player.pos_x = tmp_x;
		game->player.pos_y = tmp_y;
	}
	else
	{
		if (!is_wall(game, tmp_x, game->player.pos_y))
			game->player.pos_x = tmp_x;
		else if (!is_wall(game, game->player.pos_x, tmp_y))
			game->player.pos_y = tmp_y;
	}
}

void	move(t_game *game, double dir_x, double dir_y, double speed)
{
	if (game->player.key_up)
	{
		dir_x += game->player.dir_x;
		dir_y += game->player.dir_y;
	}
	if (game->player.key_down)
	{
		dir_x -= game->player.dir_x;
		dir_y -= game->player.dir_y;
	}
	if (game->player.key_left)
	{
		dir_x -= game->player.plane_x;
		dir_y -= game->player.plane_y;
	}
	if (game->player.key_right)
	{
		dir_x += game->player.plane_x;
		dir_y += game->player.plane_y;
	}
	collision(game, dir_x, dir_y, speed);
}

void	move_player(t_game *game)
{
	double			delta_time;
	double			move_dir_x;
	double			move_dir_y;
	struct timeval	current_frame;

	gettimeofday(&current_frame, NULL);
	delta_time = (current_frame.tv_sec - game->last_frame.tv_sec)
		+ (current_frame.tv_usec - game->last_frame.tv_usec) / 1000000.0;
	game->last_frame = current_frame;
	rotate(game, delta_time * ROTATION_SPEED);
	move_dir_x = 0.0;
	move_dir_y = 0.0;
	move(game, move_dir_x, move_dir_y, delta_time * MOVE_SPEED);
}
