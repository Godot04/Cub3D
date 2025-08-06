/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:14:08 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/05 17:21:24 by silpaukn         ###   ########.fr       */
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

void	set_rc(t_rc *rc, int x, t_game *game)
{
	rc->cam_x = 2 * x / (double)WIDTH - 1;
	rc->ray[X] = game->player.dir_x + game->player.plane_x * rc->cam_x;
	rc->ray[Y] = game->player.dir_y + game->player.plane_y * rc->cam_x;
	rc->map[X] = (int)game->player.pos_x;
	rc->map[Y] = (int)game->player.pos_y;
	rc->delta[X] = fabs(1 / rc->ray[0]);
	rc->delta[Y] = fabs(1 / rc->ray[1]);
	if (rc->ray[X] < 0)
		rc->step[X] = -1;
	else
		rc->step[X] = 1;
	if (rc->ray[Y] < 0)
		rc->step[Y] = -1;
	else
		rc->step[Y] = 1;
	if (rc->ray[X] < 0)
		rc->side[X] = (game->player.pos_x - rc->map[0]) * rc->delta[0];
	else
		rc->side[X] = (rc->map[0] + 1.0 - game->player.pos_x) * rc->delta[0];
	if (rc->ray[Y] < 0)
		rc->side[Y] = (game->player.pos_y - rc->map[1]) * rc->delta[1];
	else
		rc->side[Y] = (rc->map[1] + 1.0 - game->player.pos_y) * rc->delta[1];
}

void	cast_ray(t_game *game, t_rc *rc)
{
	while (1)
	{
		if (rc->side[X] < rc->side[Y])
		{
			rc->side[X] += rc->delta[X];
			rc->map[X] += rc->step[X];
			if (rc->step[X] > 0)
				rc->face = WEST;
			else
				rc->face = EAST;
		}
		else
		{
			rc->side[Y] += rc->delta[Y];
			rc->map[Y] += rc->step[Y];
			if (rc->step[Y] > 0)
				rc->face = NORTH;
			else
				rc->face = SOUTH;
		}
		if (game->map[rc->map[Y]][rc->map[X]] == '1')
			break ;
	}
}

void	line(t_game *game, t_rc *rc, int x)
{
	rc->line_height = (int)(HEIGHT / rc->perp_dist);
	rc->draw[X] = -rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw[X] < 0)
		rc->draw[X] = 0;
	rc->draw[1] = rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw[1] >= HEIGHT)
		rc->draw[1] = HEIGHT - 1;
	if (rc->face == EAST || rc->face == WEST)
		rc->wall_x = game->player.pos_y + rc->perp_dist * rc->ray[Y];
	else
		rc->wall_x = game->player.pos_x + rc->perp_dist * rc->ray[X];
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)game->north.width);
	if (rc->face == EAST || rc->face == NORTH)
		rc->tex_x = game->north.width - rc->tex_x - 1;
	if (TEXTURE)
		draw_texture(game, rc, x);
	else
	{
		rc->start[X] = x;
		rc->start[Y] = rc->draw[0];
		rc->end[X] = x;
		rc->end[Y] = rc->draw[1];
		draw_line(game, rc);
	}
}

void	print_line(t_game *game, t_rc *rc, int x)
{
	if (rc->face == EAST || rc->face == WEST)
		rc->perp_dist = (rc->side[0] - rc->delta[0]);
	else
		rc->perp_dist = (rc->side[Y] - rc->delta[Y]);
	if (DEBUG)
	{
		if (x % 32 == 0)
		{
			rc->hit[X] = game->player.pos_x + rc->perp_dist * rc->ray[X];
			rc->hit[Y] = game->player.pos_y + rc->perp_dist * rc->ray[Y];
			rc->start[X] = game->player.pos_x * BLOCK_SIZE;
			rc->start[Y] = game->player.pos_y * BLOCK_SIZE;
			rc->end[X] = rc->hit[X] * BLOCK_SIZE;
			rc->end[Y] = rc->hit[Y] * BLOCK_SIZE;
			draw_line(game, rc);
		}
	}
	else
		line(game, rc, x);
}

void	ray_caster(t_game *game)
{
	int		x;
	t_rc	rc;

	x = 0;
	while (x < WIDTH)
	{
		set_rc(&rc, x, game);
		cast_ray(game, &rc);
		print_line(game, &rc, x);
		x++;
	}
	if (!DEBUG)
		draw_ceiling_and_floor(game);
}
