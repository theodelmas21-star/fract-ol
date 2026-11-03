/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:58 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/18 13:59:41 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	colors_init(t_data window)
{
	window.colors[0] = 0x2E001E;
	window.colors[1] = 0xC61E5C;
	window.colors[2] = 0xEE9BAC;
	window.colors[3] = 0xFFF5DC;
	return (window);
}

t_data	first_image_initializer(t_data window)
{
	window.image.addr = NULL;
	window.image.bpp = 0;
	window.image.endian = 0;
	window.image.img = NULL;
	window.image.line_length = 0;
	return (window);
}

t_data	img_to_plan(t_data window)
{
	double	height;
	double	width;

	height = window.size_y;
	width = window.size_x;
	window.data_plan.x_min = -2;
	window.data_plan.x_max = 2;
	window.data_plan.x_range = window.data_plan.x_max - window.data_plan.x_min;
	window.data_plan.x_step = window.data_plan.x_range / window.size_x;
	window.data_plan.y_range = window.data_plan.x_range * (height / width);
	window.data_plan.y_min = -window.data_plan.y_range / 2;
	window.data_plan.y_max = window.data_plan.y_range / 2;
	window.data_plan.y_step = window.data_plan.y_range / window.size_y;
	window.max_iter = 300;
	window.data_plan.win_ratio = window.data_plan.x_range
		/ window.data_plan.y_range;
	return (window);
}

t_data	init_img(t_data window)
{
	window.mlx = mlx_init();
	if (!window.mlx)
		return (window);
	window.image.img = mlx_new_image(window.mlx, window.size_x, window.size_y);
	if (!window.image.img)
	{
		mlx_destroy_display(window.mlx);
		free(window.mlx);
		window.mlx = NULL;
		return (window);
	}
	window.image.addr = mlx_get_data_addr(window.image.img, &(window.image.bpp),
			&(window.image.line_length), &(window.image.endian));
	if (!window.image.addr)
	{
		mlx_destroy_image(window.mlx, window.image.img);
		mlx_destroy_display(window.mlx);
		free(window.mlx);
		window.mlx = NULL;
		return (window);
	}
	window = colors_init(window);
	window = img_to_plan(window);
	return (window);
}

void	put_pixel(t_data window, t_complex c, int color)
{
	char	*pixel;

	pixel = window.image.addr + (int)c.i * window.image.line_length + (int)c.r
		* (window.image.bpp / 8);
	*(int *)pixel = color;
}
