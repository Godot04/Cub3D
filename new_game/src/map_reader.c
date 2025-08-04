/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:24:20 by opopov            #+#    #+#             */
/*   Updated: 2025/08/04 14:31:29 by opopov           ###   ########.fr       */
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

	while ((input = read_line(fd)) != NULL)
	{
		tmp = ft_strtrim(input, " \t\n\r\f\v");
		if (!tmp)
		{
			printf("Error: Memory allocation failed\n");
			free(input);
			return (NULL);
		}
		if (!*tmp)
		{
			free(tmp);
			free(input);
			continue ;
		}
		if (*tmp == '1' || *tmp == '0')
		{
			free(tmp);
			return (input);
		}
		free(input);
		free(tmp);
	}
	return (NULL);
}

int	map_input_reader(t_game *game)
{
	char	**map;
	char	*input;
	char	*first_line;
	char	*tmp;
	int		fd;
	int		fd_count;
	int		fd_read;
	int		x;
	int		y;
	int		i;

	fd = open(game->file_path, O_RDONLY);
	first_line = skip_additional_lines(fd);
	if (!first_line)
	{
		printf("Error: File doesn't contain map\n");
		close(fd);
		return (0);
	}
	close(fd);
	fd_count = open(game->file_path, O_RDONLY);
	tmp = skip_additional_lines(fd_count);
	if (tmp)
		free(tmp);
	y = lines_counter(fd_count) + 1;
	close(fd_count);
	if (y == 0)
	{
		printf("Error: Map is empty\n");
		free(first_line);
		return (0);
	}
	map = malloc((sizeof(char *)) * (y + 1));
	if (!map)
	{
		printf("Error: Map allocation failed\n");
		free(first_line);
		return (0);
	}
	fd_read = open(game->file_path, O_RDONLY);
	tmp = skip_additional_lines(fd_read);
	if (tmp)
		free(tmp);
	x = 1;
	map[0] = first_line;
	while ((input = read_line(fd_read)) != NULL)
	{
		if (is_line_empty(input))
		{
			free(input);
			continue ;
		}
		map[x] = ft_strdup(input);
		if (!map[x])
		{
			printf("Error: Map allocation failed\n");
			while (--x >= 0)
				free(map[x]);
			free(map);
			free(input);
			close(fd_read);
			return (0);
		}
		x++;
		free(input);
	}
	map[x] = NULL;
	close(fd_read);
	if (!is_map_correct(map))
	{
		i = -1;
		while (map[++i])
			free(map[i]);
		free(map);
		return (0);
	}
	game->map = map;
	return (1);
}
