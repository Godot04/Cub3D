/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:50:45 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/11 16:57:20 by silpaukn         ###   ########.fr       */
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
	player->pos_x = get_x(map) * BLOCK_SIZE;
	player->pos_y = get_y(map) * BLOCK_SIZE;
	player->pos_x = WIDTH / 2;
	player->pos_y = HEIGHT / 2;
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	player->plane_x = 0.66;
	player->plane_y = 0.;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	
}

int	key_pressed(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		exit(0);
	return (0);
}

int	key_released(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_player(t_game *game)
{
	double	move_speed;
	double	rotation_speed;
	double	old_dir_x;
	double	old_plane_x;

	move_speed = 3.0;
	rotation_speed = 0.05;
	if (game->player.key_up)
	{
		game->player.pos_x += (move_speed * game->player.dir_x);
		game->player.pos_y += (move_speed * game->player.dir_y);
	}
	if (game->player.key_down)
	{
		game->player.pos_x -= (move_speed * game->player.dir_x);
		game->player.pos_y -= (move_speed * game->player.dir_y);
	}
	if (game->player.key_left)
	{
		game->player.pos_x -= (move_speed * game->player.plane_x);
		game->player.pos_y -= (move_speed * game->player.plane_y);
	}
	if (game->player.key_right)
	{
		game->player.pos_x += (move_speed * game->player.plane_x);
		game->player.pos_y += (move_speed * game->player.plane_y);
	}
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
}