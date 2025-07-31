/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:05:19 by opopov            #+#    #+#             */
/*   Updated: 2025/07/31 13:21:26 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	lines_counter(int fd)
{
	int		y;
	char	*input;

	y = 0;
	while ((input = read_line(fd)) != NULL)
	{
		if (is_line_empty(input))
		{
			free(input);
			continue ;
		}
		y++;
		free(input);
	}
	return (y);
}

int	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
			return (0);
	}
	return (1);
}

int	space_skip(char *str)
{
	while (str && ft_isspace(*str))
		str++;
	if (!str)
		return (0);
	return (1);
}

int	fill_v(char **map_copy, int y, int x, int width, int height)
{
	if (y < 0 || x < 0 || y >= height || x >= width || map_copy[y] == NULL )
		return (0);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return (1);
	map_copy[y][x] = 'V';
	if (!fill_v(map_copy, y + 1, x, width, height))
		return (0);
	if (!fill_v(map_copy, y - 1, x, width, height))
		return (0);
	if (!fill_v(map_copy, y, x + 1, width, height))
		return (0);
	if (!fill_v(map_copy, y, x - 1, width, height))
		return (0);
	return (1);
}

int	player_spawn_search(int *y, int *x, char **map)
{
	int	i;
	int	j;
	int	max_x;
	int	max_y;
	int	spawn_counter;

	i = -1;
	spawn_counter = 0;
	map_xy_count(map, &max_x, &max_y);
	while (++i < max_y)
	{
		j = -1;
		while (++j < max_x && map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				*x = j;
				*y = i;
				spawn_counter++;
			}
		}
	}
	return (spawn_counter == 1);
}
