/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:05:05 by opopov            #+#    #+#             */
/*   Updated: 2025/07/29 10:16:53 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_extracter(t_game *game, char *term_input, char t)
{
	int		j;
	int		i;
	int		colors[3];
	char	*tmp;
	char	atoi_tmp[4];

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
		{
			printf("Error: Missing values for the color\n");
			return (0);
		}
		j = 0;
		while (tmp[j] && !ft_isspace(tmp[j]) && tmp[j] != ',' && j < 3)
		{
			if (!ft_isdigit(tmp[j]))
			{
				printf("Error: Non-digital value for rgb format\n");
				return (0);
			}
			atoi_tmp[j] = tmp[j];
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
		tmp += j;
	}
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
	return (1);
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

	game->ea_path = NULL;
	game->we_path = NULL;
	game->no_path = NULL;
	game->so_path = NULL;
	game->c_r = -1;
	game->c_g = -1;
	game->c_b = -1;
	game->f_r = -1;
	game->f_g = -1;
	game->f_b = -1;
	fd = open(game->file_path, O_RDONLY);
	while ((input = read_line(fd)) != NULL)
	{
		tmp = ft_strtrim(input, " \t\n\r\f\v");
		free(input);
		if (!tmp)
		{
			printf("Error: Memory allocation failed\n");
			close(fd);
			free(tmp);
			return (0);
		}
		if (!*tmp)
		{
			free(tmp);
			continue ;
		}
		if(!ft_strncmp(tmp, "NO ", 3))
		{
			if (!path_extracter(&game->no_path, tmp))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		else if(!ft_strncmp(tmp, "SO ", 3))
		{
			if (!path_extracter(&game->so_path, tmp))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		else if(!ft_strncmp(tmp, "WE ", 3))
		{
			if (!path_extracter(&game->we_path, tmp))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		else if(!ft_strncmp(tmp, "EA ", 3))
		{
			if (!path_extracter(&game->ea_path, tmp))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		else if (!ft_strncmp(tmp, "F ", 2))
		{
			if (!rgb_extracter(game, tmp, 'F'))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		else if (!ft_strncmp(tmp, "C ", 2))
		{
			if (!rgb_extracter(game, tmp, 'C'))
			{
				free(tmp);
				close(fd);
				return (0);
			}
		}
		free(tmp);
	}
	close(fd);
	if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path
		|| (game->c_r == -1 && game->c_g == -1 && game->c_b == -1)
		|| (game->f_r == -1 && game->f_g == -1 && game->f_b == -1))
	{
		// printf("Error: Missing configuration elements\n");
		// printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\nF_r: %d\nF_g: %d\nF_b: %d\nC_r: %d\nC_g: %d\nC_b: %d\n",
        //        game->no_path, game->so_path, game->we_path, game->ea_path,
		// 	   game->f_r, game->f_g, game->f_b, game->c_r, game->c_g, game->c_b);
		return (0);
	}
	// printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\nF_r: %d\nF_g: %d\nF_b: %d\nC_r: %d\nC_g: %d\nC_b: %d\n",
    //            game->no_path, game->so_path, game->we_path, game->ea_path,
	// 		   game->f_r, game->f_g, game->f_b, game->c_r, game->c_g, game->c_b);
	return (1);
}
