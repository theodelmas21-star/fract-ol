/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:30:20 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/17 15:49:50 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_complex
{
	double		r;
	double		i;
}				t_complex;

typedef struct s_plan
{
	double		x_min;
	double		x_max;
	double		x_range;
	double		x_step;
	double		win_ratio;
	double		y_min;
	double		y_max;
	double		y_range;
	double		y_step;
}				t_plan;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		image;
	int			colors[4];
	t_plan		data_plan;
	int			size_x;
	int			size_y;
	int			max_iter;
	t_complex	z;
	int			checker;
}				t_data;

#endif