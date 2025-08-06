/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:08:08 by opopov            #+#    #+#             */
/*   Updated: 2025/08/06 11:55:07 by opopov           ###   ########.fr       */
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

void	init_game_ptrs(t_game *game)
{
	game->north.ptr = mlx_xpm_file_to_image
		(game->mlx, game->no_path, &game->north.width, &game->north.height);
	if (game->north.ptr)
		game->north.addr = (int *)mlx_get_data_addr
			(game->north.ptr, &game->north.bitsinpixel,
				&game->north.line_bytes, &game->north.endian);
	game->east.ptr = mlx_xpm_file_to_image
		(game->mlx, game->ea_path,
			&game->east.width, &game->east.height);
	if (game->east.ptr)
		game->east.addr = (int *)mlx_get_data_addr
			(game->east.ptr, &game->east.bitsinpixel,
				&game->east.line_bytes, &game->east.endian);
	game->south.ptr = mlx_xpm_file_to_image(game->mlx, game->so_path,
			&game->south.width, &game->south.height);
	if (game->south.ptr)
		game->south.addr = (int *)mlx_get_data_addr
			(game->south.ptr, &game->south.bitsinpixel,
				&game->south.line_bytes, &game->south.endian);
	game->west.ptr = mlx_xpm_file_to_image
		(game->mlx, game->we_path, &game->west.width, &game->west.height);
	if (game->west.ptr)
		game->west.addr = (int *)mlx_get_data_addr
			(game->west.ptr, &game->west.bitsinpixel,
				&game->west.line_bytes, &game->west.endian);
}
