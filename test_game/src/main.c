#include "../includes/game.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
	// for (int i = 0; i < size; i++)
	// 	for (int j = 0; j < size; j++)
	// 		put_pixel(i + x, j + y, color, game);
}

void	draw_map(t_game *game)
{
	char	**map = game->map;
	int		color = BLUE;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, game);
}

void	clear_image(t_game	*game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
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
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	gettimeofday(&game->last_frame, NULL);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x = px / BLOCK_SIZE;
	int	y = py / BLOCK_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - game->player.angle;
	float	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_block(t_game *game, int start_y, int end_x, int end_y, int color)
{
	for (int y = start_y; y < end_y; y++)
		for (int x = 0; x < end_x; x++)
			put_pixel(x, y, color, game);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		if (game->debug)
			put_pixel(ray_x, ray_y, RED, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!game->debug)
	{
		int		color;
		float	prev_x = ray_x - cos_angle;
		float	prev_y = ray_y - sin_angle;
		int		prev_map_x = (int)(prev_x / BLOCK_SIZE);
		int		prev_map_y = (int)(prev_y / BLOCK_SIZE);
		int		hit_map_x = (int)(ray_x / BLOCK_SIZE);
		int		hit_map_y = (int)(ray_y / BLOCK_SIZE);

		if (hit_map_x != prev_map_x)
		{
			if (cos_angle < 0)
				color = BLUE;
			else
				color = BLUE;
		}
		else
		{
			if (sin_angle > 0)
				color = DARK_BLUE;
			else
				color = DARK_BLUE; // change to wall image
		}
		float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
		int		start_y = (HEIGHT - height) / 2;
		int		end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, color, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player = &game->player;
	clear_image(game);
	move_player(player, game);

	if (!game->debug)
	{
		draw_block(game, 0, WIDTH, HEIGHT / 2, DARK_GREEN);
		draw_block(game, HEIGHT / 2, WIDTH, HEIGHT, DARK_RED);
	}
	if (game->debug)
	{
		draw_square(player->x, player->y, 10, GREEN, game);
		draw_map(game);
	}

	float	fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	mouse(int keycode, t_game *game)
{
	int	x = 0;
	int	y = 0;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	printf("%d at pos: x: %d y: %d\n", keycode, x, y);

	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	if (argc > 1)
		game.debug = 1;
	else
		game.debug = 0;

	init_game(&game);
	
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	// mlx_mouse_hook(game.win, mouse, &game);

	mlx_loop_hook(game.mlx, draw_loop, &game);

	mlx_loop(game.mlx);
	return (0);
}