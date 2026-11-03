/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:35:33 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/17 15:42:38 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	sign_atoi(const char *nptr)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (nptr[i] == '-')
		sign *= -1;
	return (sign);
}

double	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	double	res;
	double	factor;

	i = 0;
	res = 0;
	sign = sign_atoi(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		i++;
	factor = 0.1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res + factor * (nptr[i] - '0');
		i++;
		factor /= 10;
	}
	return (res * sign);
}

int	parser(char *s)
{
	int	index;
	int	digit;

	index = 0;
	digit = 0;
	if (!s || s[0] == '\0')
		return (0);
	if (s[index] == '+' || s[index] == '-')
		index++;
	while (s[index] >= '0' && s[index] <= '9')
	{
		index++;
		digit = 1;
	}
	if (s[index] == '.')
		index++;
	while (s[index] >= '0' && s[index] <= '9')
		index++;
	if (s[index] == '\0' && digit == 1)
		return (0);
	else
		return (1);
}

t_complex	divergence_param(char *r, char *i)
{
	t_complex	z;
	int			index;

	z.r = -0.4;
	z.i = 0.6;
	index = 0;
	if (!r || !i)
		return (z);
	z.r = ft_atoi(r);
	z.i = ft_atoi(i);
	return (z);
}
