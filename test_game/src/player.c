#include "../includes/game.h"

float	get_x(char **map)
{
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)x + 0.5);
	return (1.5);
}

float	get_y(char **map)
{
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] != '0' && map[y][x] != '1')
				return ((float)y + 0.5);
	return (1.5);
}

void	init_player(t_player *player, char **map)
{

	player->x = get_x(map) * BLOCK_SIZE;
	player->y = get_y(map) * BLOCK_SIZE;
	int	x = player->x / 64;
	int	y = player->y / 64;
	char	facing = map[y][x];
	if (facing == 'W')
		player->angle = PI;
	else if (facing == 'S')
		player->angle = PI / 2;
	else if (facing == 'E')
		player->angle = 2 * PI;
	else
		player->angle = 3 * PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC_CODE)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
		if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_player(t_player *player, t_game *game)
{
	struct timeval	current_frame;
	int				move_speed;
	float			angle_speed;
	double			delta_time;

	gettimeofday(&current_frame, NULL);
	delta_time = (current_frame.tv_sec - game->last_frame.tv_sec) + (current_frame.tv_usec - game->last_frame.tv_usec) / 1000000.0;
	game->last_frame = current_frame;

	move_speed = 250.0 * delta_time;
	angle_speed = 2.5 * delta_time;
	float	cos_angle = cos(player->angle);
	float	sin_angle = sin(player->angle);
	float	x_next = 0;
	float	y_next = 0;

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		x_next = player->x + cos_angle * move_speed;
		y_next = player->y + sin_angle * move_speed;
		if (game->map[(int)y_next / BLOCK_SIZE][(int)x_next / BLOCK_SIZE] != '1')
		{
			player->x = x_next;
			player->y = y_next;
		}
	}
	if (player->key_down)
	{
		x_next = player->x - cos_angle * move_speed;
		y_next = player->y - sin_angle * move_speed;
		if (game->map[(int)(y_next / BLOCK_SIZE)][(int)(x_next / BLOCK_SIZE)] != '1')
		{
			player->x = x_next;
			player->y = y_next;
		}
	}
	if (player->key_left)
	{
		x_next = player->x + sin_angle * move_speed;
		y_next = player->y - cos_angle * move_speed;
		if (game->map[(int)(y_next / BLOCK_SIZE)][(int)(x_next / BLOCK_SIZE)] != '1')
		{
			player->x = x_next;
			player->y = y_next;
		}
	}
	if (player->key_right)
	{
		x_next = player->x - sin_angle * move_speed;
		y_next = player->y + cos_angle * move_speed;
		if (game->map[(int)(y_next / BLOCK_SIZE)][(int)(x_next / BLOCK_SIZE)] != '1')
		{
			player->x = x_next;
			player->y = y_next;
		}
	}
}
