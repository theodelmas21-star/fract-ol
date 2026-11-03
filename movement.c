/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:30:06 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/17 15:55:46 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	*change_color(int keycode, t_data *window)
{
	if (keycode == 49)
	{
		window->colors[0] = 0x2E001E;
		window->colors[1] = 0xC61E5C;
		window->colors[2] = 0xEE9BAC;
		window->colors[3] = 0xFFF5DC;
	}
	if (keycode == 50)
	{
		window->colors[0] = 0x140B00;
		window->colors[1] = 0x7A1E00;
		window->colors[2] = 0xFF6F00;
		window->colors[3] = 0xFFD166;
	}
	if (keycode == 51)
	{
		window->colors[0] = 0x050014;
		window->colors[1] = 0x2E026D;
		window->colors[2] = 0x3A86FF;
		window->colors[3] = 0x8EECF5;
	}
	return (window);
}

t_data	*zoom(t_data *window, double x, double y, double factor)
{
	window->data_plan.x_range *= factor;
	window->data_plan.x_min = x - window->data_plan.x_range / 2;
	window->data_plan.x_max = x + window->data_plan.x_range / 2;
	window->data_plan.x_step = window->data_plan.x_range / window->size_x;
	window->data_plan.y_range = window->data_plan.y_range * factor;
	window->data_plan.y_min = y - window->data_plan.y_range / 2;
	window->data_plan.y_max = y + window->data_plan.y_range / 2;
	window->data_plan.y_step = window->data_plan.y_range / window->size_y;
	return (window);
}

int	mouse_hook(int button, int x, int y, t_data *window)
{
	t_complex	c;

	c.r = window->data_plan.x_min + x * window->data_plan.x_step;
	c.i = window->data_plan.y_max - y * window->data_plan.y_step;
	if (button == 4)
		window = zoom(window, c.r, c.i, 0.5);
	else if (button == 5)
		window = zoom(window, c.r, c.i, 2.0);
	render_mandelbrot(*window);
	mlx_put_image_to_window(window->mlx, window->win, window->image.img, 0, 0);
	return (0);
}

t_data	*arrows_hook(int keycode, t_data *window)
{
	if (keycode == 65361)
	{
		window->data_plan.x_min -= window->data_plan.x_range * 0.05;
		window->data_plan.x_max -= window->data_plan.x_range * 0.05;
	}
	else if (keycode == 65363)
	{
		window->data_plan.x_min += window->data_plan.x_range * 0.05;
		window->data_plan.x_max += window->data_plan.x_range * 0.05;
	}
	else if (keycode == 65362)
	{
		window->data_plan.y_min += window->data_plan.y_range * 0.05;
		window->data_plan.y_max += window->data_plan.y_range * 0.05;
	}
	else if (keycode == 65364)
	{
		window->data_plan.y_min -= window->data_plan.y_range * 0.05;
		window->data_plan.y_max -= window->data_plan.y_range * 0.05;
	}
	return (window);
}

int	key_event_handler(int keycode, t_data *window)
{
	if (keycode >= 65361 && keycode <= 65364)
		window = arrows_hook(keycode, window);
	else if (keycode == 65307)
	{
		close_window(window);
		return (0);
	}
	else if (keycode >= 49 && keycode <= 51)
		window = change_color(keycode, window);
	else if (keycode == 61)
		window->max_iter += 50;
	else if (keycode == 45)
		window->max_iter -= 50;
	render_mandelbrot(*window);
	mlx_put_image_to_window(window->mlx, window->win, window->image.img, 0, 0);
	return (0);
}
