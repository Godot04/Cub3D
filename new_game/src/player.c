/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:50:45 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/31 12:44:10 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	get_x(char **map)
{
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)x + 0.5);
	return (1.5);
}

float	get_y(char **map)
{
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)y + 0.5);
	return (1.5);
}

void	init_player(t_player *player, char **map)
{
	player->pos_x = get_x(map);
	player->pos_y = get_y(map);
	char	facing = map[(int)get_y(map)][(int)get_x(map)];
	if (facing == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -FOV;
	}
	else if (facing == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -FOV;
		player->plane_y = 0.0;
	}
	else if (facing == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = FOV;
	}
	else
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

void	move_player(t_game *game)
{
	double	move_speed;
	double	rotation_speed;
	double	old_dir_x;
	double	old_plane_x;
	double	delta_time;
	double	move_dir_x = 0;
	double	move_dir_y = 0;
	double	tmp_x = 0;
	double	tmp_y = 0;
	struct timeval	current_frame;


	gettimeofday(&current_frame, NULL);
	delta_time = (current_frame.tv_sec - game->last_frame.tv_sec) + (current_frame.tv_usec - game->last_frame.tv_usec) / 1000000.0;
	game->last_frame = current_frame;

	move_speed = 3.0 * delta_time;
	rotation_speed = 2.0 * delta_time;

	if (game->player.left_rotate)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotation_speed) - game->player.dir_y * sin(-rotation_speed);
		game->player.dir_y = old_dir_x * sin(-rotation_speed) + game->player.dir_y * cos(-rotation_speed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rotation_speed) - game->player.plane_y * sin(-rotation_speed);
		game->player.plane_y = old_plane_x * sin(-rotation_speed) + game->player.plane_y * cos(-rotation_speed);
	}
	if (game->player.right_rotate)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotation_speed) - game->player.dir_y * sin(rotation_speed);
		game->player.dir_y = old_dir_x * sin(rotation_speed) + game->player.dir_y * cos(rotation_speed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotation_speed) - game->player.plane_y * sin(rotation_speed);
		game->player.plane_y = old_plane_x * sin(rotation_speed) + game->player.plane_y * cos(rotation_speed);
	}

	if (game->player.key_up)
	{
		move_dir_x += game->player.dir_x;
		move_dir_y += game->player.dir_y;
	}
	if (game->player.key_down)
	{
		move_dir_x -= game->player.dir_x;
		move_dir_y -= game->player.dir_y;
	}
	if (game->player.key_left)
	{
		move_dir_x -= game->player.plane_x;
		move_dir_y -= game->player.plane_y;
	}
	if (game->player.key_right)
	{
		move_dir_x += game->player.plane_x;
		move_dir_y += game->player.plane_y;
	}

	if ((move_dir_x != 0 || move_dir_y != 0))
	{
		double	len = sqrt(move_dir_x * move_dir_x + move_dir_y * move_dir_y);
		tmp_x = game->player.pos_x + (move_dir_x / len) * move_speed;
		tmp_y = game->player.pos_y + (move_dir_y / len) * move_speed;
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
