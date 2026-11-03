/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 08:21:15 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/22 17:28:18 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_data *window)
{
	mlx_destroy_image(window->mlx, window->image.img);
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	exit(0);
	return (0);
}

int	different_hooks(t_data *window)
{
	window->win = mlx_new_window(window->mlx, window->size_x, window->size_y,
			"Mandelbrot");
	if (window->win == NULL)
	{
		mlx_destroy_image(window->mlx, window->image.img);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
		window->mlx = NULL;
		window->image.img = NULL;
		return (1);
	}
	mlx_put_image_to_window(window->mlx, window->win, window->image.img, 0, 0);
	mlx_mouse_hook(window->win, mouse_hook, window);
	mlx_hook(window->win, 2, 1L << 0, key_event_handler, window);
	mlx_hook(window->win, 17, 0L, close_window, window);
	return (0);
}

void	error_message(void)
{
	write(1, "Write 'Mandelbrot' or 'Julia' or 'Julia <real> <imag>' \n", 57);
	write(1, "Examples of valid instructions for Julia : \n", 45);
	write(1, "'Julia -0.2 0.4' 'Julia -0.4 0.6'", 34);
}

int	parsing_global(int argc, char **argv)
{
	if (ft_strcmp(argv[1], "Julia") == 0)
	{
		if (argc == 2)
			return (0);
		if (argc != 2 && argc != 4)
			return (1);
		if ((argv[2] != NULL && argv[3] == NULL) || (argv[2] == NULL
				&& argv[3] != NULL))
			return (1);
		else if (parser(argv[2]) == 1 || parser(argv[3]) == 1)
			return (1);
	}
	else if (ft_strcmp(argv[1], "Mandelbrot") == 0 && argc == 2)
		return (0);
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	window;

	if (argc < 2 || parsing_global(argc, argv) == 1)
	{
		error_message();
		return (0);
	}
	window.checker = 0;
	window.size_y = 800;
	window.size_x = 1000;
	window = init_img(window);
	if (!window.mlx || !window.image.img || !window.image.addr)
		return (0);
	if (ft_strcmp(argv[1], "Julia") == 0)
	{
		window.checker = 1;
		window.z = divergence_param(argv[2], argv[3]);
		window = render_mandelbrot(window);
	}
	else if (ft_strcmp(argv[1], "Mandelbrot") == 0)
		window = render_mandelbrot(window);
	if (different_hooks(&window) == 1)
		return (0);
	mlx_loop(window.mlx);
	return (0);
}
