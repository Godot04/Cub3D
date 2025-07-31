/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:58:10 by opopov            #+#    #+#             */
/*   Updated: 2025/07/31 12:29:37 by opopov           ###   ########.fr       */
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

int	is_map_closed(char **map)
{
	int		max_x;
	int		max_y;
	char	**tmp;
	int		i;
	int		player_x;
	int		player_y;

	if (!map || !map[0])
		return (0);
	map_xy_count(map, &max_x, &max_y);
	tmp = malloc(sizeof(char *) * (max_y + 1));
	if (!tmp)
		return (0);
	i = -1;
	while (++i < max_y)
	{
		tmp[i] = malloc(max_x + 1);
		if (!tmp[i])
		{
			while (--i >= 0)
				free(tmp[i]);
			free(tmp);
			return (0);
		}
		ft_strlcpy(tmp[i], map[i], max_x + 1);
		tmp[i][max_x] = '\0';
	}
	tmp[max_y] = NULL;
	player_spawn_search(&player_y, &player_x, map);
	if (!fill_v(tmp, player_y, player_x, max_x, max_y))
	{
		i = -1;
		while (++i < max_y)
			free(tmp[i]);
		free(tmp);
		return (0);
	}
	i = -1;
	while (++i < max_y)
		free(tmp[i]);
	free(tmp);
	return (1);
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
	// for (int y = 0; map[y]; y++)
	// 		printf("%s\n", map[y]);
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
