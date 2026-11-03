/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:59:32 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/17 15:56:42 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	julia_divergence(t_data window, t_complex z, t_complex c)
{
	int			n;
	double		modulus;
	double		mu;
	t_complex	new;

	n = 0;
	while (n < window.max_iter)
	{
		new.r = z.r * z.r - z.i * z.i + c.r;
		new.i = 2 * z.i * z.r + c.i;
		if ((new.r * new.r + new.i * new.i) > 4)
		{
			modulus = sqrt(new.r * new.r + new.i * new.i);
			mu = n + 1 - log(log(modulus)) / log(2.0);
			return (mu);
		}
		n++;
		z = new;
	}
	return ((double)window.max_iter);
}

double	mandelbrot_divergence(t_data window, t_complex c)
{
	int			n;
	double		modulus;
	double		mu;
	t_complex	z;
	t_complex	new;

	n = 0;
	z.r = 0;
	z.i = 0;
	while (n < window.max_iter)
	{
		new.r = z.r * z.r - z.i * z.i + c.r;
		new.i = 2 * z.i * z.r + c.i;
		if ((new.r * new.r + new.i * new.i) > 4)
		{
			modulus = sqrt(new.r * new.r + new.i * new.i);
			mu = n + 1 - log(log(modulus)) / log(2.0);
			return (mu);
		}
		n++;
		z = new;
	}
	return ((double)window.max_iter);
}

int	linear_interpolation(int color1, int color2, double t)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = (int)(((color1 >> 16) & 0xFF) + t * (((color2 >> 16) & 0xFF)
				- ((color1 >> 16) & 0xFF)));
	green = (int)(((color1 >> 8) & 0xFF) + t * (((color2 >> 8) & 0xFF)
				- ((color1 >> 8) & 0xFF)));
	blue = (int)((color1 & 0xFF) + t * ((color2 & 0xFF) - (color1 & 0xFF)));
	color = ((red << 16) | (green << 8) | blue);
	return (color);
}

int	smooth_color(double iter, t_data window)
{
	double	t;
	double	pos;
	int		index;
	double	local_t;
	int		palette_size;

	palette_size = 3;
	if (iter >= window.max_iter)
		return (window.colors[0]);
	t = iter / window.max_iter;
	t = pow(t, 0.7);
	pos = t * palette_size;
	index = (int)pos;
	local_t = pos - index;
	if (index < 0)
		index = 0;
	if (index >= palette_size - 1)
		return (window.colors[palette_size - 1]);
	return (linear_interpolation(window.colors[index], window.colors[index + 1],
			local_t));
}

t_data	render_mandelbrot(t_data window)
{
	t_complex	pixel;
	t_complex	c;
	double		iter;
	int			color;

	pixel.i = 0;
	while (pixel.i < window.size_y)
	{
		pixel.r = 0;
		while (pixel.r < window.size_x)
		{
			c.r = window.data_plan.x_min + pixel.r * window.data_plan.x_step;
			c.i = window.data_plan.y_max - pixel.i * window.data_plan.y_step;
			if (window.checker == 0)
				iter = mandelbrot_divergence(window, c);
			else if (window.checker == 1)
				iter = julia_divergence(window, c, window.z);
			color = smooth_color(iter, window);
			put_pixel(window, pixel, color);
			pixel.r++;
		}
		pixel.i++;
	}
	return (window);
}
