/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:24:20 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 14:19:48 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	wall_counter(char **map)
{
	int	x;
	int	y;
	int	wall_counter;

	y = 0;
	wall_counter = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				wall_counter++;
			x++;
		}
		y++;
	}
	return (wall_counter);
}

void	map_xy_count(char **map, int *ox, int *oy)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	y = 0;
	x = 0;
	max_x = x;
	max_y = y;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > max_x)
			max_x = x;
		y++;
	}
	max_y = y;
	*ox = max_x;
	*oy = max_y;
}

void	map_fill(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_isspace(map[y][x]))
				map[y][x] = '0';
		}
	}
}

char	*skip_additional_lines(int fd)
{
	char	*input;
	char	*tmp;

	input = read_line(fd);
	while (input != NULL)
	{
		tmp = ft_strtrim(input, " \t\n\r\f\v");
		if (!tmp)
			return (printf("Error: Memory allocation failed\n"),
				free(input), NULL);
		if (!*tmp)
		{
			free(tmp);
			free(input);
			input = read_line(fd);
			continue ;
		}
		if (*tmp == '1' || *tmp == '0')
			return (free(tmp), input);
		free(input);
		free(tmp);
		input = read_line(fd);
	}
	return (NULL);
}

int	map_input_reader(t_game *game)
{
	char	**map;
	char	*first_line;
	int		fd_read;

	if (!map_skip_lines(&fd_read, &first_line, game))
		return (0);
	map = map_malloc(first_line, game);
	if (!map)
	{
		close(fd_read);
		return (0);
	}
	if (!map_readline(fd_read, map))
	{
		close(fd_read);
		return (0);
	}
	close(fd_read);
	if (!is_map_correct(map))
		return (map_free(map));
	game->map = map;
	return (1);
}
