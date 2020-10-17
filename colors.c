/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:11:57 by pmetron           #+#    #+#             */
/*   Updated: 2020/02/21 16:34:20 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_light(int start_color, int end_color, double percentage)
{
	return ((int)((1 - percentage) * start_color + percentage * end_color));
}

int		get_color(int start, int curr_pos, int distance,\
			t_cntrl *cntrl)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	red = 0;
	green = 0;
	blue = 0;
	percentage = percent(start, curr_pos, distance);
	red = (get_light((cntrl->color >> 16) & 255, \
		(cntrl->end_color >> 16) & 255, percentage));
	green = (get_light((cntrl->color >> 8) & 255, \
		(cntrl->end_color >> 8) & 255, percentage));
	blue = get_light(cntrl->color & 255, cntrl->end_color & 255, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int		get_color_reverse(int start, int curr_pos, int distance,\
			t_cntrl *cntrl)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	red = 0;
	green = 0;
	blue = 0;
	percentage = percent(start, curr_pos, distance);
	red = (get_light((cntrl->end_color >> 16) & 255, \
		(cntrl->color >> 16) & 255, percentage));
	green = (get_light((cntrl->end_color >> 8) & 255, \
		(cntrl->color >> 8) & 255, percentage));
	blue = get_light(cntrl->end_color & 255, cntrl->color & 255, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int		choose_color_y(t_cntrl *cntrl, t_point point_f, t_point point_s, int y)
{
	int distance;

	distance = (int)point_s.y - (int)point_f.y;
	if (point_s.z_cpy - point_f.z_cpy != 0)
	{
		if (point_s.z_cpy > point_f.z_cpy)
			return (get_color(point_f.y, y, distance, cntrl));
		if (point_s.z_cpy < point_f.z_cpy)
			return (get_color_reverse(point_f.y, y, distance, cntrl));
	}
	else
	{
		if (point_s.z_cpy > 0)
			return (cntrl->end_color);
		else
			return (cntrl->color);
	}
	return (0);
}

int		choose_color_x(t_cntrl *cntrl, t_point point_f, t_point point_s, int x)
{
	int distance;

	distance = (int)point_s.x - (int)point_f.x;
	if (point_s.z_cpy - point_f.z_cpy != 0)
	{
		if (point_s.z_cpy > point_f.z_cpy)
			return (get_color(point_f.x, x, distance, cntrl));
		if (point_s.z_cpy < point_f.z_cpy)
			return (get_color_reverse(point_f.x, x, distance, cntrl));
	}
	else
	{
		if (point_s.z_cpy > 0)
			return (cntrl->end_color);
		else
			return (cntrl->color);
	}
	return (0);
}
