/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:53 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/06 11:55:04 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
}

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	close_game(t_game *game)
{
	clean_ptrs(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	clean_path(game);
	if (game->map)
		map_free(game->map);
	exit(0);
	return (0);
}

int	is_wall(t_game *data, float x, float y)
{
	float	check_x;
	float	check_y;
	int		i;
	float	angles[8];

	angles_declaration(angles);
	if (!data || !data->map || !data->map[0])
		return (1);
	i = -1;
	while (++i < 8)
	{
		check_x = x + COLLISION_RADIUS * cos(angles[i]);
		check_y = y + COLLISION_RADIUS * sin(angles[i]);
		if ((int)check_x < 0 || (int)check_y < 0)
			return (1);
		if (data->map[(int)check_y][(int)check_x] == '1')
			return (1);
	}
	return (0);
}
