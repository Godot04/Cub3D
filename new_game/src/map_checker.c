/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:58:10 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 16:28:57 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_characters_check(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != '0'
				&& map[y][x] != 'N' && map[y][x] != 'S'
				&& map[y][x] != 'E' && map[y][x] != 'W')
				return (0);
		}
	}
	return (1);
}

int	map_free(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
	}
	return (0);
}

int	is_map_closed(char **map)
{
	int		max_x;
	int		max_y;
	char	**tmp;
	int		i;
	int		player_pos[2];

	map_xy_count(map, &max_x, &max_y);
	tmp = malloc(sizeof(char *) * (max_y + 1));
	if (!tmp)
		return (0);
	i = -1;
	while (++i < max_y)
	{
		tmp[i] = malloc(max_x + 1);
		if (!tmp[i])
			return (map_free(tmp));
		ft_strlcpy(tmp[i], map[i], max_x + 1);
		tmp[i][max_x] = '\0';
	}
	tmp[max_y] = NULL;
	player_spawn_search(&player_pos[0], &player_pos[1], map);
	if (!fill_v(tmp, player_pos[0], player_pos[1], map))
		return (map_free(tmp));
	return (map_free(tmp), 1);
}

int	is_map_correct(char **map)
{
	int	x;
	int	y;

	if (!map || !*map)
	{
		printf("Error: Map is NULL\n");
		return (0);
	}
	map_fill(map);
	if (!map_characters_check(map))
	{
		printf("Error: Invalid character input\n");
		return (0);
	}
	if (!player_spawn_search(&y, &x, map))
	{
		printf("Error: Invalid spawn counter\n");
		return (0);
	}
	if (!is_map_closed(map))
	{
		printf("Error: Invalid map input\n");
		return (0);
	}
	return (1);
}
