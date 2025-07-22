/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:24:04 by opopov            #+#    #+#             */
/*   Updated: 2025/07/22 12:24:30 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	ch;

	line = malloc(MAX_LINE_LEN);
	if (!line)
	{
		printf("Error: Memory line allocation failed\n");
		return (NULL);
	}
	i = 0;
	while (read(fd, &ch, 1) > 0 && ch != '\n' && i < MAX_LINE_LEN - 1)
	{
		line[i++] = ch;
	}
	if(!i && ch != '\n')
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
