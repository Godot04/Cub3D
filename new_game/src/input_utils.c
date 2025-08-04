/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:24:04 by opopov            #+#    #+#             */
/*   Updated: 2025/08/04 13:21:13 by opopov           ###   ########.fr       */
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
	{
		printf("Error: Memory line allocation failed\n");
		return (NULL);
	}
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
	if(!i && ch_read <= 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
