/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:05:05 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 10:46:31 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_extracter(t_game *game, char *term_input, char t)
{
	int		i;
	int		colors[3];
	char	*tmp;

	colors[0] = -1;
	colors[1] = -1;
	colors[2] = -1;
	tmp = ft_strchr(term_input, ' ');
	if (!tmp)
	{
		printf("Error: Missing space and values for the color\n");
		return (0);
	}
	i = -1;
	while (*tmp && ++i < 3)
	{
		while (*tmp && (ft_isspace(*tmp) || *tmp == ','))
			tmp++;
		if (!*tmp)
			return (printf("Error: Missing values for the color\n"), 0);
		if (!rgb_number_extract(&tmp, colors, i))
			return (0);
	}
	return (rgb_res_check(game, colors, i, t));
}

int	path_extracter(char **dest, char *term_input)
{
	char	*tmp;
	char	*path;

	tmp = ft_strchr(term_input, ' ');
	if (!tmp)
	{
		printf("Error: Missing space and path of the texture\n");
		return (0);
	}
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (!tmp)
	{
		printf("Error: Missing path of the texture\n");
		return (0);
	}
	path = ft_strtrim(tmp, "\t\n\r\f\v");
	if (!path)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	*dest = path;
	return (1);
}

int	cub_input_reader(t_game *game)
{
	char	*input;
	char	*tmp;
	int		fd;

	fd = open(game->file_path, O_RDONLY);
	input = read_line(fd);
	while (input != NULL)
	{
		tmp = ft_strtrim(input, " \t\n\r\f\v");
		free(input);
		if (!tmp)
			return (close(fd), printf("Error: Memory allocation failed\n"), 0);
		if (!*tmp)
		{
			free(tmp);
			input = read_line(fd);
			continue ;
		}
		if (!cmp_string(game, tmp))
			return (free(tmp), close(fd), 0);
		free(tmp);
		input = read_line(fd);
	}
	close(fd);
	return (res_check(game));
}
