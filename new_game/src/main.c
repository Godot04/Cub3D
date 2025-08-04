/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:55 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/04 14:31:39 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		img->addr[y * WIDTH + x] = color;
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->img.ptr = NULL;
	game->north.ptr = NULL;
	game->east.ptr = NULL;
	game->south.ptr = NULL;
	game->west.ptr = NULL;
}

void	init_game(t_game *game)
{
	int	tex_w;
	int	tex_h;
	game->crgb = trgb_to_int(0, game->c_r, game->c_g, game->c_b);
	game->frgb = trgb_to_int(0, game->f_r, game->f_g, game->f_b);
	game->mlx = mlx_init();
	game->north.ptr = mlx_xpm_file_to_image(game->mlx, game->no_path, &tex_w, &tex_h);
	if (game->north.ptr)
		game->north.addr = (int *)mlx_get_data_addr(game->north.ptr, &game->north.bitsinpixel, &game->north.line_bytes, &game->north.endian);
	game->east.ptr = mlx_xpm_file_to_image(game->mlx, game->ea_path, &tex_w, &tex_h);
	if (game->east.ptr)
		game->east.addr = (int *)mlx_get_data_addr(game->east.ptr, &game->east.bitsinpixel, &game->east.line_bytes, &game->east.endian);
	game->south.ptr = mlx_xpm_file_to_image(game->mlx, game->so_path, &tex_w, &tex_h);
	if (game->south.ptr)
		game->south.addr = (int *)mlx_get_data_addr(game->south.ptr, &game->south.bitsinpixel, &game->south.line_bytes, &game->south.endian);
	game->west.ptr = mlx_xpm_file_to_image(game->mlx, game->we_path, &tex_w, &tex_h);
	if (game->west.ptr)
		game->west.addr = (int *)mlx_get_data_addr(game->west.ptr, &game->west.bitsinpixel, &game->west.line_bytes, &game->west.endian);
	if (!game->north.ptr || !game->east.ptr || !game->south.ptr || !game->west.ptr)
	{
		printf("Error: Invalid texture path\n");
		close_game(game);
	}
	init_player(&game->player, game->map);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr(game->img.ptr, &game->img.bitsinpixel, &game->img.line_bytes, &game->img.endian);
	gettimeofday(&game->last_frame, NULL);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < size)
	{
		width = 0;
		while (width < size)
		{
			put_pixel(&game->img, x + width, y + height, color);
			width++;
		}
		height++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				if (DEBUG)
					draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

void	draw_line(t_game *game, double start_x, double start_y, double end_x, double end_y, int side)
{
	double	dir_x;
	double	dir_y;
	double	steps;
	double	inc_x;
	double	inc_y;
	int		i;

	dir_x = end_x - start_x;
	dir_y = end_y - start_y;
	if (fabs(dir_x) > fabs(dir_y))
		steps = fabs(dir_x);
	else
		steps = fabs(dir_y);
	inc_x = dir_x / steps;
	inc_y = dir_y / steps;
	i = 0;
	while (i < steps)
	{
		put_pixel(&game->img, round(start_x), round(start_y), side);
		start_x += inc_x;
		start_y += inc_y;
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

void	draw_texture(t_game *game, int side, int x, int tex_x, int start_y, int line_height)
{
	t_img	*texture;
	double	tex_pos;
	double	step;
	int		y;
	int		tex_y;
	int		color;

	if (side == NORTH)
		texture = &game->north;
	else if (side == EAST)
		texture = &game->east;
	else if (side == SOUTH)
		texture = &game->south;
	else
		texture = &game->west;
	step = 1.0 * TEXTURE_HEIGHT / line_height;
	tex_pos = (start_y - HEIGHT / 2 + line_height / 2) * step;
	y = start_y;
	int draw_end = start_y + line_height;
	if (draw_end > HEIGHT)
		draw_end = HEIGHT;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		color = texture->addr[TEXTURE_HEIGHT * tex_y + tex_x];
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

void	ray_caster(t_game *game)
{
	int	x = 0;

	while (x < WIDTH)
	{
		double	camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate of the camera plane corresponding the current x-coordinate of the screen
		double	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x; // direction vector of the current ray
		double	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		int	map_x = (int)game->player.pos_x;
		int	map_y = (int)game->player.pos_y;
		double	side_dist_x; // distance from player to first x/y-side
		double	side_dist_y;
		double	delta_dist_x = fabs(1 / ray_dir_x); // distance from one x/y-side to the next
		double	delta_dist_y = fabs(1 / ray_dir_y);
		int	step_x; // what direction to go in
		int	step_y;

		if (ray_dir_x < 0) // calculate side_dist and set step
		{
			step_x = -1;
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
		}
		int	side;
		while (1)
		{
			if (side_dist_x < side_dist_y) // jump to next square in x-direction
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				if (step_x > 0)
					side = WEST;
				else
					side = EAST;
			}
			else // jump to next square in y-direction
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				if (step_y > 0)
					side = NORTH;
				else
					side = SOUTH;
			}
			if (map_y < 0 || map_y >= get_height(game->map) || \
				map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
				break ;
			if (game->map[map_y][map_x] == '1')
				break ;
		}
		double	perp_wall_dist; // length of the ray from the camera plane to the wall (to avoid the fish eye effect)
		if (side == EAST || side == WEST)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);
		if (DEBUG)
		{
			if (x % 32 == 0) // how far the lines are spread apart
			{
				double hit_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
				double hit_y = game->player.pos_y + perp_wall_dist * ray_dir_y;
				draw_line(game, game->player.pos_x * BLOCK_SIZE, game->player.pos_y * BLOCK_SIZE,
				hit_x * BLOCK_SIZE, hit_y * BLOCK_SIZE, side);
			}
		}
		else
		{
			int	line_height = (int)(HEIGHT / perp_wall_dist); // height of the whole wall
			int	draw_start = -line_height / 2 + HEIGHT / 2; // lowest pixel of wall
			if (draw_start < 0)
				draw_start = 0;
			int	draw_end = line_height / 2 + HEIGHT / 2; // highest pixel of wall
			if (draw_end >= HEIGHT)
				draw_end = HEIGHT - 1;

			double	wall_x;
			if (side == EAST || side == WEST)
				wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
			else
				wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
			wall_x -= floor(wall_x); // Get the fractional part

			// Calculate the x-coordinate on the texture
			int tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
			if (side == EAST || side == NORTH)
				tex_x = TEXTURE_WIDTH - tex_x - 1;
			if (TEXTURE)
				draw_texture(game, side, x, tex_x, draw_start, line_height);
			else
				draw_line(game, x, draw_start, x, draw_end, side);
		}
		x++;
	}
	if (!DEBUG)
		draw_ceiling_and_floor(game);
}

int	game_loop(t_game *game)
{
	ft_bzero(game->img.addr, WIDTH * HEIGHT * sizeof(int));
	move_player(game);
	if (DEBUG)
		draw_map(game);
	ray_caster(game);
	if (DEBUG)
		draw_square(game->player.pos_x * BLOCK_SIZE - PLAYER_SIZE / 2, game->player.pos_y * BLOCK_SIZE - PLAYER_SIZE / 2, PLAYER_SIZE, trgb_to_int(0, 128, 255, 128), game);
	else if (MINIMAP)
		draw_minimap(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error: Invalid .cub path\n"));
	game.file_path = argv[1];
	init_struct(&game);
	if (!ft_cub(game.file_path))
		return (printf("Error: Map file must have a .cub extension\n"));
	if (!open_file_check(game.file_path))
		return (printf("Error: File doesn't exist\n"));
	if (!cub_input_reader(&game))
		return (close_game(&game));
	if (!map_input_reader(&game))
		return (close_game(&game));
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
