/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:28:46 by opopov            #+#    #+#             */
/*   Updated: 2025/07/07 17:27:08 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minilibx-linux/mlx.h"
#include "../inc/Libft/libft.h"
#include <stdlib.h>

#define GREY 0x808080
#define YELLOW 0xFFFF00
#define PLAYER_SIZE 20
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*window;
	// background
	void	*background;
	int		background_width;
	int		background_height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	// player
	int	px;
	int	py;
	int	p_height;
	int	p_width;
	int	p_color;
}	t_data;
