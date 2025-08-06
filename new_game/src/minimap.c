/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:35:08 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/05 16:50:07 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

// void	draw_minimap(t_game *game, t_player *player)
// {
// 	int		map_width;
// 	int		map_height;
// 	double	start_x = 0;
// 	double	start_y = 0;
// 	double	world_x;
// 	double	world_y;
// 	int		x = 0;
// 	int		y = 0;
// 	map_xy_count(game->map, &map_width, &map_height);
// 	if (map_width > MAX_MAP_WIDTH)
// 		start_x = player->pos_x - (MAX_MAP_WIDTH / 2);
// 	if (map_height > MAX_MAP_HEIGHT)
// 		start_y = player->pos_y - (MAX_MAP_HEIGHT / 2);
// 	if (start_x < 0)
// 		start_x = 0;
// 	if (start_y < 0)
// 		start_y = 0;
// 	if (start_x > map_width - MAX_MAP_WIDTH)
// 		start_x = map_width - MAX_MAP_WIDTH;
// 	if (start_y > map_height - MAX_MAP_HEIGHT)
// 		start_y = map_height - MAX_MAP_HEIGHT;
// 	while (y < MAX_MAP_HEIGHT * MAP_SIZE && y < map_height * MAP_SIZE)
// 	{
// 		x = 0;
// 		while (x < MAX_MAP_WIDTH * MAP_SIZE && x < map_width * MAP_SIZE)
// 		{
// 			world_x = start_x + (double)x / MAP_SIZE;
// 			world_y = start_y + (double)y / MAP_SIZE;
// 			int map_y = (int)world_y;
// 			int map_x = (int)world_x;
// 			if (map_y >= 0 && map_y < map_height &&
// 				map_x >= 0 && map_x < (int)ft_strlen(game->map[map_y]))
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 					put_pixel(&game->img, x, y, 0x333333);
// 				else if (game->map[map_y][map_x] != ' ')
// 					put_pixel(&game->img, x, y, 0xCCCCCC);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_square((game->player.pos_x - start_x) * MAP_SIZE - PLAYER_SIZE / 4,
// 		(game->player.pos_y - start_y) * MAP_SIZE - PLAYER_SIZE / 4,
// 		PLAYER_SIZE / 2, trgb_to_int(0, 128, 255, 128), game);
// }

void	draw_mini(t_game *game, int xy[2], double start[2], int map[2])
{
	double	world[2];
	int		map_int[2];

	while (xy[Y] < MAX_MAP_HEIGHT * MAP_SIZE && xy[Y] < map[Y] * MAP_SIZE)
	{
		xy[X] = 0;
		while (xy[X] < MAX_MAP_WIDTH * MAP_SIZE && xy[X] < map[X] * MAP_SIZE)
		{
			world[X] = start[X] + (double)xy[X] / MAP_SIZE;
			world[Y] = start[Y] + (double)xy[Y] / MAP_SIZE;
			map_int[X] = (int)world[0];
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
			xy[X]++;
		}
		xy[Y]++;
	}
}

void	draw_minimap(t_game *game, t_player *player)
{
	int		map[2];
	double	start[2];
	int		xy[2];

	map_xy_count(game->map, &map[X], &map[Y]);
	xy[Y] = 0;
	if (map[X] > MAX_MAP_WIDTH)
		start[X] = player->pos_x - (MAX_MAP_WIDTH / 2);
	if (map[Y] > MAX_MAP_HEIGHT)
		start[Y] = player->pos_y - (MAX_MAP_HEIGHT / 2);
	if (start[X] < 0)
		start[X] = 0;
	if (start[Y] < 0)
		start[Y] = 0;
	if (start[X] > map[X] - MAX_MAP_WIDTH)
		start[X] = map[X] - MAX_MAP_WIDTH;
	if (start[Y] > map[Y] - MAX_MAP_HEIGHT)
		start[Y] = map[Y] - MAX_MAP_HEIGHT;
	draw_mini(game, xy, start, map);
	xy[X] = (game->player.pos_x - start[X]) * MAP_SIZE - PLAYER_SIZE / 4;
	xy[Y] = (game->player.pos_y - start[Y]) * MAP_SIZE - PLAYER_SIZE / 4;
	draw_square(xy, PLAYER_SIZE / 2, trgb_to_int(0, 128, 255, 128), game);
}
