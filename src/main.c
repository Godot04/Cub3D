/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:55 by silpaukn          #+#    #+#             */
/*   Updated: 2025/08/12 13:44:16 by silpaukn         ###   ########.fr       */
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
	game->ea_path = NULL;
	game->we_path = NULL;
	game->no_path = NULL;
	game->so_path = NULL;
	game->c_r = -1;
	game->c_g = -1;
	game->c_b = -1;
	game->f_r = -1;
	game->f_g = -1;
	game->f_b = -1;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	init_game_ptrs(game);
	if (!game->north.ptr || !game->east.ptr
		|| !game->south.ptr || !game->west.ptr)
	{
		printf("Error: Invalid texture path\n");
		close_game(game);
	}
	init_player(&game->player, game->map);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr
		(game->img.ptr, &game->img.bitsinpixel,
			&game->img.line_bytes, &game->img.endian);
	gettimeofday(&game->last_frame, NULL);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

int	game_loop(t_game *game)
{
	int	xy[2];

	ft_bzero(game->img.addr, WIDTH * HEIGHT * sizeof(int));
	move_player(game);
	if (DEBUG)
		draw_map(game);
	ray_caster(game);
	if (DEBUG)
	{
		xy[X] = game->player.pos_x * BLOCK_SIZE - PLAYER_SIZE / 2;
		xy[Y] = game->player.pos_y * BLOCK_SIZE - PLAYER_SIZE / 2;
		draw_square(xy, PLAYER_SIZE, trgb_to_int(0, 128, 255, 128), game);
	}
	else if (MINIMAP)
		draw_minimap(game, &game->player, xy);
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
