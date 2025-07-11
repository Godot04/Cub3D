/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silpaukn <silpaukn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:50:55 by silpaukn          #+#    #+#             */
/*   Updated: 2025/07/11 16:56:52 by silpaukn         ###   ########.fr       */
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
	map[4] = "100001000010001";
	map[5] = "100000000000001";
	map[6] = "100000000100001";
	map[7] = "100010E00000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	game->map = get_map();
	init_player(&game->player, game->map);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr(game->img.ptr, &game->img.bitsinpixel, &game->img.line_bytes, &game->img.endian);
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
	while(game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	ft_bzero(game->img.addr, WIDTH * HEIGHT * sizeof(int));
	move_player(game);
	draw_map(game);
	draw_square(game->player.pos_x, game->player.pos_y, 16, trgb_to_int(0, 128, 255, 128), game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	draw_square(0, 0, BLOCK_SIZE, trgb_to_int(0, 222, 100, 0), &game);
	
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game.player);

	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}