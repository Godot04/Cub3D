/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:28:25 by opopov            #+#    #+#             */
/*   Updated: 2025/07/14 16:21:12 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	window_create(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
}

int	close_window(t_data *data)
{
	if (data->background)
		mlx_destroy_image(data->mlx, data->background);
	if (data->player)
		free(data->player);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	initialize_properties(t_data *data)
{
	int	map_check_x;
	int	map_check_y;

	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		perror("Error: failed to allocate player memory");
		close_window(data);
	}
	int	initial_map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};
	ft_memcpy(data->map, initial_map, sizeof(initial_map));
	map_check_x = (WINDOW_WIDTH - (MAP_WIDTH * WALL_SIZE)) / 2;
	map_check_y = (WINDOW_HEIGHT - (MAP_HEIGHT * WALL_SIZE)) / 2;
	data->player->pos_x = map_check_x + (MAP_WIDTH * WALL_SIZE / 2);
	data->player->pos_y = map_check_y + (MAP_HEIGHT * WALL_SIZE / 2);
	data->player->dir_x = -1;
	data->player->dir_y = 0;
	data->player->plane_x = 0;
	data->player->plane_y = 0.66;
	data->player->p_width = PLAYER_SIZE;
	data->player->p_height = PLAYER_SIZE;
	data->player->p_color = YELLOW;
	data->player->p_speed = MS;
	data->player->p_angle = PI / 2;
	data->player->p_angle_speed = RS;
	data->background = NULL;
	data->w_width = WALL_SIZE;
	data->w_height = WALL_SIZE;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->player->is_key_a = 0;
	data->player->is_key_d = 0;
	data->player->is_key_s = 0;
	data->player->is_key_w = 0;
	data->player->is_left_rotate = 0;
	data->player->is_right_rotate = 0;
	data->endian = 0;
	data->background = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->background_addr = mlx_get_data_addr(data->background, &data->bits_per_pixel,
											&data->line_length, &data->endian);
}

int	main()
{
	t_data	data;

	window_create(&data);
	initialize_properties(&data);
	background_draw(&data);
	mlx_hook(data.window, 17, 0, close_window, &data);
	mlx_hook(data.window, 2, 1L<<0, key_pressed, &data);
	mlx_hook(data.window, 3, 1L<<1, key_released, &data);
	mlx_loop_hook(data.mlx, p_movement, &data);
	mlx_loop(data.mlx);
	return (0);
}
