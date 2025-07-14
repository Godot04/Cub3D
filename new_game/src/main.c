/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:55 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/14 16:37:09 by silpaukn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		img->addr[y * WIDTH + x] = color;
}

char	**get_map(void)
{
	char	**map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000010001";
	map[2] = "100100000010001";
	map[3] = "100000000010001";
	map[4] = "1000010E0010001";
	map[5] = "100000000000001";
	map[6] = "100000000100001";
	map[7] = "100010000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	game->map = get_map();
	game->crgb = trgb_to_int(0, 0, 0, 64);
	game->frgb = trgb_to_int(0, 64, 0, 0);
	init_player(&game->player, game->map);
	game->mlx = mlx_init();
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
			{
				if (DEBUG)
					draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, 0xFF0000, game);
				else if (MINIMAP)
					draw_square(x * (BLOCK_SIZE / 4), y * (BLOCK_SIZE / 4), (BLOCK_SIZE / 4), 0xFF0000, game);
			}
			else if (MINIMAP)
				draw_square(x * (BLOCK_SIZE / 4), y * (BLOCK_SIZE / 4), (BLOCK_SIZE / 4), 0xFFFFFF, game);
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
					side = EAST;
				else
					side = WEST;
			}
			else // jump to next square in y-direction
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				if (step_y > 0)
					side = SOUTH;
				else
					side = NORTH;
			}
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
	{
		draw_map(game);
		draw_square(game->player.pos_x * (BLOCK_SIZE / 4) - 8, game->player.pos_y * (BLOCK_SIZE / 4) - 8, PLAYER_SIZE / 2, trgb_to_int(0, 128, 255, 128), game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);

	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}