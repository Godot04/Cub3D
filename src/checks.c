/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:18:42 by opopov            #+#    #+#             */
/*   Updated: 2025/07/14 17:05:08 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_data *data, float x, float y)
{
	float	player_center_x;
	float	player_center_y;
	float	check_x;
	float	check_y;
	int		map_x;
	int		map_y;
	int		map_check_x;
	int		map_check_y;
	int		i;
	float angles[8] = {0, PI/4, PI/2, 3*PI/4, PI, 5*PI/4, 3*PI/2, 7*PI/4};

	map_check_x = (WINDOW_WIDTH - (MAP_WIDTH * WALL_SIZE)) / 2;
	map_check_y = (WINDOW_HEIGHT - (MAP_HEIGHT * WALL_SIZE)) / 2;
	player_center_x = x + (PLAYER_SIZE / 2);
	player_center_y = y + (PLAYER_SIZE / 2);
	i = -1;
	while (++i < 8)
	{
		check_x = player_center_x + PLAYER_COLISION_RADIUS * cos(angles[i]);
		check_y = player_center_y + PLAYER_COLISION_RADIUS * sin(angles[i]);
		map_x = (int)((check_x - map_check_x) / WALL_SIZE);
		map_y = (int)((check_y - map_check_y) / WALL_SIZE);
		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			return (1);
		else if (data->map[map_y][map_x] == 1)
			return (1);
	}
	return (0);
}
