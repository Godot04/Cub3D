/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:21:06 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 14:21:58 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_skip_lines(int *fd, char **first_line, t_game *game)
{
	(*fd) = open(game->file_path, O_RDONLY);
	(*first_line) = skip_additional_lines((*fd));
	if (!(*first_line))
	{
		printf("Error: File doesn't contain map\n");
		close((*fd));
		return (0);
	}
	return (1);
}

char	**map_malloc(char *first_line, t_game *game)
{
	int		y;
	char	**map;
	int		fd_tmp;
	char	*tmp;

	fd_tmp = open(game->file_path, O_RDONLY);
	tmp = skip_additional_lines(fd_tmp);
	if (tmp)
		free(tmp);
	y = lines_counter(fd_tmp) + 1;
	close(fd_tmp);
	if (y == 0)
	{
		printf("Error: Map is empty\n");
		free(first_line);
		return (NULL);
	}
	map = malloc((sizeof(char *)) * (y + 1));
	if (!map)
	{
		printf("Error: Map allocation failed\n");
		return (free(first_line), NULL);
	}
	map[0] = first_line;
	return (map);
}

int	map_readline(int fd_read, char **map)
{
	char	*input;
	int		x;

	x = 1;
	input = read_line(fd_read);
	while (input != NULL)
	{
		if (is_line_empty(input))
		{
			free(input);
			input = read_line(fd_read);
			continue ;
		}
		map[x] = ft_strdup(input);
		if (!map[x])
		{
			printf("Error: Map allocation failed\n");
			return (free(input), close(fd_read), (map_free(map)));
		}
		x++;
		free(input);
		input = read_line(fd_read);
	}
	map[x] = NULL;
	return (1);
}
