/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:01:54 by opopov            #+#    #+#             */
/*   Updated: 2025/07/14 17:05:29 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int key, t_data *data)
{
	if (key == W)
		data->player->is_key_w = 1;
	else if (key == A)
		data->player->is_key_a = 1;
	else if (key == S)
		data->player->is_key_s = 1;
	else if (key == D)
		data->player->is_key_d = 1;
	else if (key == LEFT)
		data->player->is_left_rotate = 1;
	else if (key == RIGHT)
		data->player->is_right_rotate = 1;
	else if (key == ESC)
		close_window(data);
	return (0);
}
int	key_released(int key, t_data *data)
{
	if (key == W)
		data->player->is_key_w = 0;
	else if (key == A)
		data->player->is_key_a = 0;
	else if (key == S)
		data->player->is_key_s = 0;
	else if (key == D)
		data->player->is_key_d = 0;
	else if (key == LEFT)
		data->player->is_left_rotate = 0;
	else if (key == RIGHT)
		data->player->is_right_rotate = 0;
	return (0);
}

int	p_movement(t_data *data)
{
	float	new_x;
	float	new_y;
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	// rotation
	if (data->player->is_left_rotate)
		data->player->p_angle -= data->player->p_angle_speed;
	if (data->player->is_right_rotate)
		data->player->p_angle += data->player->p_angle_speed;
	// check boundries
	data->player->p_angle = fmod(data->player->p_angle, 2 * PI);
	if (data->player->p_angle < 0)
		data->player->p_angle += 2 * PI;
	// movement
	if (data->player->is_key_w)
		move_x += data->player->p_speed;
	if (data->player->is_key_s)
		move_x -= data->player->p_speed;
	if (data->player->is_key_d)
		move_y += data->player->p_speed;
	if (data->player->is_key_a)
		move_y -= data->player->p_speed;
	new_x = data->player->pos_x + cos(data->player->p_angle) * move_x
			+ cos(data->player->p_angle + PI/2) * move_y;
	new_y = data->player->pos_y + sin(data->player->p_angle) * move_x
			+ sin(data->player->p_angle + PI/2) * move_y;
	if (!is_wall(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	else
	{
		if (!is_wall(data, new_x, data->player->pos_y))
			data->player->pos_x = new_x;
		else if (!is_wall(data, data->player->pos_x, new_y))
			data->player->pos_y = new_y;
	}
	background_draw(data);
	return (0);
}
