/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manipulations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:14 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:17:19 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	change_scale(t_point point, char sign, double dx, double dy)
{
	if (sign == '+')
	{
		point.x = ((point.x - dx) * 1.1) + dx;
		point.y = ((point.y - dy) * 1.1) + dy;
		point.z = (point.z * 1.1);
	}
	if (sign == '-')
	{
		point.x = ((point.x - dx) / 1.1) + dx;
		point.y = ((point.y - dy) / 1.1) + dy;
		point.z = point.z / 1.1;
	}
	return (point);
}

t_point	rotate_z(t_point point, double gamma, double dx, double dy)
{
	double buf;

	buf = point.x;
	point.x = ((point.x - dx) * cos(gamma) - (point.y - dy) * sin(gamma)) + dx;
	point.y = ((buf - dx) * sin(gamma) + (point.y - dy) * cos(gamma)) + dy;
	return (point);
}

t_point	rotate_y(t_point point, double beta, double dx)
{
	double buf;

	buf = point.x;
	point.x = (point.x - dx) * cos(beta) + point.z * sin(beta) + dx;
	point.z = -(buf - dx) * sin(beta) + point.z * cos(beta);
	return (point);
}

t_point	rotate_x(t_point point, double alpha, double dy)
{
	double buf;

	buf = point.y;
	point.y = (point.y - dy) * cos(alpha) + point.z * sin(alpha) + dy;
	point.z = -(buf - dy) * sin(alpha) + point.z * cos(alpha);
	return (point);
}
