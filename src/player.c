/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:50:45 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/12 13:41:57 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	no_collision(t_game *game, double dir_x, double dir_y, double speed)
{
	double	len;
	double	tmp_x;
	double	tmp_y;
	int		xy[2];

	if ((dir_x != 0 || dir_y != 0))
	{
		len = sqrt(dir_x * dir_x + dir_y * dir_y);
		tmp_x = game->player.pos_x + (dir_x / len) * speed;
		tmp_y = game->player.pos_y + (dir_y / len) * speed;
		map_xy_count(game->map, &xy[X], &xy[Y]);
	}
	else
		return ;
	if (tmp_x >= 0 && (int)tmp_x
		< (int)ft_strlen(game->map[(int)game->player.pos_y]))
		game->player.pos_x = tmp_x;
	if (tmp_y >= 0 && (int)tmp_y < xy[Y] - 1
		&& (int)game->player.pos_x < (int)ft_strlen(game->map[(int)tmp_y]))
		game->player.pos_y = tmp_y;
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
	if (COLLISION)
		collision(game, dir_x, dir_y, speed);
	else
		no_collision(game, dir_x, dir_y, speed);
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
	if (VALGRIND)
		delta_time = 0.1;
	rotate(game, delta_time * ROTATION_SPEED);
	move_dir_x = 0.0;
	move_dir_y = 0.0;
	move(game, move_dir_x, move_dir_y, delta_time * MOVE_SPEED);
}
