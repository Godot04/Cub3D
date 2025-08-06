/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:49:03 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/06 11:50:35 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_xy(char **map, t_player *player)
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
			{
				player->pos_x = x + 0.5;
				player->pos_y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
	player->pos_x = 1.5;
	player->pos_y = 1.5;
	return ;
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

	get_xy(map, player);
	facing = map[(int)player->pos_y][(int)player->pos_x];
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
