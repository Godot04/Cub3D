/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:35:08 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/15 17:25:54 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

size_t	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	return (a);
}

int	get_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

void	draw_rectangle(int start_x, int start_y, int end_x, int end_y, int color, t_game *game)
{
	int		x;

	while (start_y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			put_pixel(&game->img, x, start_y, color);
			x++;
		}
		start_y++;
	}
}

void	draw_minimap(t_game *game, t_player *player)
{
	int map_width = ft_strlen(game->map[0]);
	int	map_height = get_height(game->map);
	double	start_x = 0;
	double	start_y = 0;
	double	world_x;
	double	world_y;
	int	x = 0;
	int	y = 0;
	if (map_width > MAX_MAP_WIDTH)
		start_x = player->pos_x - (MAX_MAP_WIDTH / 2);
	if (map_height > MAX_MAP_HEIGHT)
		start_y = player->pos_y - (MAX_MAP_HEIGHT / 2);
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (start_x > map_width - MAX_MAP_WIDTH)
		start_x = map_width - MAX_MAP_WIDTH;
	if (start_y > map_height - MAX_MAP_HEIGHT)
		start_y = map_height - MAX_MAP_HEIGHT;
	while (y < MAX_MAP_HEIGHT * MAP_SIZE && y < map_height * MAP_SIZE)
	{
		x = 0;
		while (x < MAX_MAP_WIDTH * MAP_SIZE && x < map_width * MAP_SIZE)
		{
			world_x = start_x + (double)x / MAP_SIZE;
			world_y = start_y + (double)y / MAP_SIZE;
			if (game->map[(int)world_y][(int)world_x] == '1')
				put_pixel(&game->img, x, y, 0x333333);
			else
				put_pixel(&game->img, x, y, 0xCCCCCC);
			x++;
		}
		y++;
	}
	draw_square((game->player.pos_x - start_x) * MAP_SIZE - PLAYER_SIZE / 4, (game->player.pos_y - start_y) * MAP_SIZE - PLAYER_SIZE / 4, PLAYER_SIZE / 2, trgb_to_int(0, 128, 255, 128), game);
}
