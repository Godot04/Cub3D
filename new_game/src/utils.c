/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:53 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/05 14:43:01 by opopov           ###   ########.fr       */
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

int	trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

int	close_game(t_game *game)
{
	int	i;

	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->north.ptr)
		mlx_destroy_image(game->mlx, game->north.ptr);
	if (game->east.ptr)
		mlx_destroy_image(game->mlx, game->east.ptr);
	if (game->south.ptr)
		mlx_destroy_image(game->mlx, game->south.ptr);
	if (game->west.ptr)
		mlx_destroy_image(game->mlx, game->west.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->map)
		map_free(game->map);
	exit(0);
	return (0);
}

int	is_wall(t_game *data, float x, float y)
{
	float	check_x;
	float	check_y;
	int		map_x;
	int		map_y;
	int		i;
	float	angles[8] = {0, PI/4, PI/2, 3*PI/4, PI, 5*PI/4, 3*PI/2, 7*PI/4};

	if (!data || !data->map || !data->map[0])
		return (1);
	i = -1;
	while (++i < 8)
	{
		check_x = x + COLLISION_RADIUS * cos(angles[i]);
		check_y = y + COLLISION_RADIUS * sin(angles[i]);
		map_x = (int)check_x;
		map_y = (int)check_y;
		if (map_x < 0 ||  map_y < 0)
			return (1);
		if (data->map[map_y][map_x] == '1')
			return (1);
	}
	return (0);
}
