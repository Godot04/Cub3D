/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:41:55 by opopov            #+#    #+#             */
/*   Updated: 2025/07/22 12:24:47 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	open_file_check(char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	ft_cub(char *file_path)
{
	char	*tmp;

	tmp = ft_strrchr(file_path, '.');
	if (tmp && ft_strncmp(tmp, ".cub", ft_strlen(tmp)) != 0)
		return (0);
	return (1);
}
