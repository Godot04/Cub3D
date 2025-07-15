/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:03:37 by opopov            #+#    #+#             */
/*   Updated: 2025/07/14 13:10:28 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_wall(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	pos;
	int	*img_data;

	i = -1;
	img_data = (int *)data->background_addr;
	while (++i < WALL_SIZE)
	{
		j = -1;
		while (++j < WALL_SIZE)
		{
			pos = ((y + j) * data->line_length / 4) + (x + i);
			if (pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				img_data[pos] = GREEN;
		}
	}
}

void	wall_draw(t_data *data)
{
	int	y;
	int	x;
	int	center_x;
	int	center_y;

	center_x = (WINDOW_WIDTH - (MAP_WIDTH * WALL_SIZE)) / 2;
	center_y = (WINDOW_HEIGHT - (MAP_HEIGHT * WALL_SIZE)) / 2;
	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			if (data->map[y][x] == 1)
				put_wall(data, center_x + x * WALL_SIZE, center_y + y * WALL_SIZE);
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->background, 0, 0);
}

void	player_draw(t_data *data)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	pixel_pos;
	int	*img_data;

	start_x = data->player->pos_x;
	start_y = data->player->pos_y;
	img_data = (int *)data->background_addr;
	y = -1;
	while (++y < data->player->p_height)
	{
		x = -1;
		while (++x < data->player->p_width)
		{
			pixel_pos = (start_y + y) * (data->line_length / 4) + (start_x + x);
			if (pixel_pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				img_data[pixel_pos] = data->player->p_color;
		}
	}
}

void	background_draw(t_data *data)
{
	int	i;
	int	*img_data;

	img_data = (int *)data->background_addr;
	i = -1;
	while (++i < WINDOW_HEIGHT * WINDOW_WIDTH)
		img_data[i] = GREY;
	player_draw(data);
	wall_draw(data);
	mlx_put_image_to_window(data->mlx, data->window, data->background, 0, 0);
}
