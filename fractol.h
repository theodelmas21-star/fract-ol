/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:30:20 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/17 15:42:33 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx/mlx.h"
# include "struct.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

t_complex	divergence_param(char *r, char *i);
void		put_pixel(t_data window, t_complex c, int color);
t_data		init_img(t_data window);
t_data		render_mandelbrot(t_data window);
t_data		colors_init(t_data window);
int			mouse_hook(int button, int x, int y, t_data *window);
int			key_event_handler(int button, t_data *window);
int			close_window(t_data *window);
int			parser(char *s);
int			ft_strcmp(const char *s1, const char *s2);

#endif