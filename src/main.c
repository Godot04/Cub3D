/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:28:25 by opopov            #+#    #+#             */
/*   Updated: 2025/07/07 17:26:26 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	window_create(t_data *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 800, 800, "Cub3D");
}

int	close_window(t_data *data)
{
	if (data->background)
		mlx_destroy_image(data->mlx, data->background);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	background_draw(t_data *data)
{
	int	i;
	int	*img_data;

	if (!data->background)
	{
		data->background = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img_data = (int *)mlx_get_data_addr(data->background, &data->bits_per_pixel,
											&data->line_length, &data->endian);
		data->background_width = WINDOW_WIDTH;
		data->background_height = WINDOW_HEIGHT;
		i = 0;
		while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
		{
			img_data[i] = GREY;
			i++;
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->background, 0, 0);
}

void	player_draw(t_data *data)
{
	int	*img_data;
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	pixel_pos;

	img_data = (int *)mlx_get_data_addr(data->background, &data->bits_per_pixel,
										&data->line_length, &data->endian);
	start_x = data->px;
	start_y = data->py;
	y = 0;
	while (y < data->p_height)
	{
		x = 0;
		while (x < data->p_width)
		{
			pixel_pos = (start_y + y) * (data->line_length / 4) + (start_x + x);
			if (pixel_pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				img_data[pixel_pos] = data->p_color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->background, 0, 0);
}

void	initialize_properties(t_data *data)
{
	data->px = WINDOW_WIDTH / 2 - PLAYER_SIZE / 2;
	data->py = WINDOW_HEIGHT / 2 - PLAYER_SIZE / 2;
	data->p_width = PLAYER_SIZE;
	data->p_height = PLAYER_SIZE;
	data->p_color = YELLOW;
	data->background = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
}

int	main()
{
	t_data	data;

	window_create(&data);
	initialize_properties(&data);
	background_draw(&data);
	player_draw(&data);
	mlx_hook(data.window, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
