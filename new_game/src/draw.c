/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:51:28 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/06 11:52:57 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(int xy[2], int size, int color, t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < size)
	{
		width = 0;
		while (width < size)
		{
			put_pixel(&game->img, xy[X] + width, xy[Y] + height, color);
			width++;
		}
		height++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	xy[2];

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
			{
				xy[X] = x * BLOCK_SIZE;
				xy[Y] = y * BLOCK_SIZE;
				draw_square(xy, BLOCK_SIZE, 0xFF0000, game);
			}
			x++;
		}
		y++;
	}
}

void	draw_line(t_game *game, t_rc *rc)
{
	double	dir[2];
	double	steps;
	double	inc[2];
	int		i;

	dir[0] = rc->end[X] - rc->start[X];
	dir[1] = rc->end[Y] - rc->start[Y];
	if (fabs(dir[X]) > fabs(dir[Y]))
		steps = fabs(dir[X]);
	else
		steps = fabs(dir[Y]);
	inc[X] = dir[X] / steps;
	inc[Y] = dir[Y] / steps;
	i = 0;
	while (i < steps)
	{
		put_pixel(&game->img, round(rc->start[X]),
			round(rc->start[Y]), rc->face);
		rc->start[X] += inc[X];
		rc->start[Y] += inc[Y];
		i++;
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (game->img.addr[y * WIDTH + x] == 0)
			{
				if (y > HEIGHT / 2)
					put_pixel(&game->img, x, y, game->frgb);
				else
					put_pixel(&game->img, x, y, game->crgb);
			}
			x++;
		}
		y++;
	}
}

void	draw_texture(t_game *game, t_rc *rc, int x)
{
	t_img	*texture;
	double	tex_pos;
	double	step;
	int		tex_y;
	int		color;

	if (rc->face == NORTH)
		texture = &game->north;
	else if (rc->face == EAST)
		texture = &game->east;
	else if (rc->face == SOUTH)
		texture = &game->south;
	else
		texture = &game->west;
	step = 1.0 * texture->height / rc->line_height;
	tex_pos = (rc->draw[0] - HEIGHT / 2 + rc->line_height / 2) * step;
	while (rc->draw[0] < rc->draw[1])
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = texture->addr[texture->height * tex_y + rc->tex_x];
		put_pixel(&game->img, x, rc->draw[0], color);
		rc->draw[0]++;
	}
}
