/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:24:04 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 14:55:27 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*read_line(int fd)
{
	char	*line;
	int		i;
	int		ch_read;

	line = malloc(MAX_LINE_LEN + 1);
	if (!line)
		return (printf("Error: Memory line allocation failed\n"), NULL);
	i = -1;
	while (++i < MAX_LINE_LEN)
	{
		ch_read = read(fd, &line[i], 1);
		if (ch_read <= 0)
			break ;
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
	}
	if (!i && ch_read <= 0)
		return (free(line), NULL);
	line[i] = '\0';
	return (line);
}

int	cmp_string(t_game *game, char *tmp)
{
	if (!ft_strncmp(tmp, "NO ", 3))
		if (!path_extracter(&game->no_path, tmp))
			return (0);
	if (!ft_strncmp(tmp, "SO ", 3))
		if (!path_extracter(&game->so_path, tmp))
			return (0);
	if (!ft_strncmp(tmp, "WE ", 3))
		if (!path_extracter(&game->we_path, tmp))
			return (0);
	if (!ft_strncmp(tmp, "EA ", 3))
		if (!path_extracter(&game->ea_path, tmp))
			return (0);
	if (!ft_strncmp(tmp, "F ", 2))
		if (!rgb_extracter(game, tmp, 'F'))
			return (0);
	if (!ft_strncmp(tmp, "C ", 2))
		if (!rgb_extracter(game, tmp, 'C'))
			return (0);
	return (1);
}

int	res_check(t_game *game)
{
	if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path
		|| (game->c_r == -1 && game->c_g == -1 && game->c_b == -1)
		|| (game->f_r == -1 && game->f_g == -1 && game->f_b == -1))
	{
		printf("Error: Missing configuration elements\n");
		return (0);
	}
	return (1);
}

int	rgb_res_check(t_game *game, int *colors, int i, char t)
{
	if (i != 2)
	{
		printf("Error: Need %d more color values\n", 3 - (i + 1));
		return (0);
	}
	if (t == 'C')
	{
		game->c_r = colors[0];
		game->c_g = colors[1];
		game->c_b = colors[2];
	}
	else if (t == 'F')
	{
		game->f_r = colors[0];
		game->f_g = colors[1];
		game->f_b = colors[2];
	}
	game->crgb = trgb_to_int(0, game->c_r, game->c_g, game->c_b);
	game->frgb = trgb_to_int(0, game->f_r, game->f_g, game->f_b);
	return (1);
}

int	rgb_number_extract(char **tmp, int *colors, int i)
{
	int		j;
	char	atoi_tmp[3];

	j = 0;
	while ((*tmp)[j] && !ft_isspace((*tmp)[j]) && (*tmp)[j] != ',' && j < 3)
	{
		if (!ft_isdigit((*tmp)[j]))
			return (printf("Error: Non-digital value for rgb format\n"), 0);
		atoi_tmp[j] = (*tmp)[j];
		j++;
	}
	atoi_tmp[j] = '\0';
	if (j == 0)
	{
		printf("Error: Empty input for color format\n");
		return (0);
	}
	colors[i] = ft_atoi(atoi_tmp);
	if (colors[i] > 255 || colors[i] < 0)
	{
		printf("Error: Incorrect int value for rgb (0-255)\n");
		return (0);
	}
	(*tmp) += j;
	return (1);
}
