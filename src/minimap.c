/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:35:08 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/12 13:46:26 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_mini(t_game *game, int xy[2], double start[2], int map[2])
{
	double	world[2];
	int		map_int[2];

	while (++xy[Y] < MAX_MAP_HEIGHT * MAP_SIZE && xy[Y] < map[Y] * MAP_SIZE)
	{
		xy[X] = -1;
		while (++xy[X] < MAX_MAP_WIDTH * MAP_SIZE && xy[X] < map[X] * MAP_SIZE)
		{
			world[X] = start[X] + (double)xy[X] / MAP_SIZE;
			world[Y] = start[Y] + (double)xy[Y] / MAP_SIZE;
			map_int[X] = (int)world[X];
			map_int[Y] = (int)world[Y];
			if (map_int[X] >= 0 && map_int[X]
				< (int)ft_strlen(game->map[map_int[Y]])
				&& map_int[Y] >= 0 && map_int[Y] < map[Y])
			{
				if (game->map[map_int[Y]][map_int[X]] == '1')
					put_pixel(&game->img, xy[X], xy[Y], 0x333333);
				else if (game->map[map_int[Y]][map_int[X]] != ' ')
					put_pixel(&game->img, xy[X], xy[Y], 0xCCCCCC);
			}
			else
				put_pixel(&game->img, xy[X], xy[Y], 0xCCCCCC);
		}
	}
}

void	draw_minimap(t_game *game, t_player *player, int xy[2])
{
	int		map[2];
	double	start[2];

	map_xy_count(game->map, &map[X], &map[Y]);
	xy[Y] = -1;
	if (map[X] > MAX_MAP_WIDTH)
		start[X] = player->pos_x - (MAX_MAP_WIDTH / 2);
	else
		start[X] = 0;
	if (map[Y] > MAX_MAP_HEIGHT)
		start[Y] = player->pos_y - (MAX_MAP_HEIGHT / 2);
	else
		start[Y] = 0;
	if (start[X] < 0)
		start[X] = 0;
	if (start[Y] < 0)
		start[Y] = 0;
	if (map[X] > MAX_MAP_WIDTH && start[X] > map[X] - MAX_MAP_WIDTH)
		start[X] = map[X] - MAX_MAP_WIDTH;
	if (map[Y] > MAX_MAP_HEIGHT && start[Y] > map[Y] - MAX_MAP_HEIGHT)
		start[Y] = map[Y] - MAX_MAP_HEIGHT;
	draw_mini(game, xy, start, map);
	xy[X] = (game->player.pos_x - start[X]) * MAP_SIZE - PLAYER_SIZE / 4;
	xy[Y] = (game->player.pos_y - start[Y]) * MAP_SIZE - PLAYER_SIZE / 4;
	draw_square(xy, PLAYER_SIZE / 2, trgb_to_int(0, 128, 255, 128), game);
}
