/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:08:08 by opopov            #+#    #+#             */
/*   Updated: 2025/08/05 15:45:38 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	angles_declaration(float angles[8])
{
	angles[0] = 0;
	angles[1] = PI / 4;
	angles[2] = PI / 2;
	angles[3] = 3 * PI / 4;
	angles[4] = PI;
	angles[5] = 5 * PI / 4;
	angles[6] = 3 * PI / 2;
	angles[7] = 7 * PI / 4;
}

void	clean_path(t_game *game)
{
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
}

void	clean_ptrs(t_game *game)
{
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
}
