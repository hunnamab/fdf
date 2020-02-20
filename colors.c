/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:11:57 by pmetron           #+#    #+#             */
/*   Updated: 2020/02/20 22:07:45 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int curr_pos, int distance)
{
	double placement;

	placement = curr_pos - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start_color, int end_color, double percentage)
{
	return ((int)((1 - percentage) * start_color + percentage * end_color));
}

int		get_color(int start, int curr_pos, int distance,\
int start_color, int end_color)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	red = 0;
	green = 0;
	blue = 0;
	percentage = percent(start, curr_pos, distance);
	red = (get_light((start_color >> 16) & 255, (end_color >> 16) & 255, \
		percentage));
	green = (get_light((start_color >> 8) & 255, (end_color >> 8) & 255, \
		percentage));
	blue = get_light(start_color & 255, end_color & 255, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int		choose_color_y(c_cntrl *cntrl, p_point point_f, p_point point_s, int y)
{
	int distance;

	distance = (int)point_s.y - (int)point_f.y;
	if (point_s.z_cpy - point_f.z_cpy != 0)
	{
		if (point_s.z_cpy > point_f.z_cpy)
			return (get_color(point_f.y, y,\
				distance, cntrl->color, cntrl->end_color));
		if (point_s.z_cpy < point_f.z_cpy)
			return (get_color(point_f.y, y,\
				distance, cntrl->end_color, cntrl->color));
	}
	else
	{
		if (point_s.z_cpy > 0)
			return (cntrl->end_color);
		else
			return (cntrl->color);
	}
}

int		choose_color_x(c_cntrl *cntrl, p_point point_f, p_point point_s, int x)
{
	int distance;

	distance = (int)point_s.x - (int)point_f.x;
	if (point_s.z_cpy - point_f.z_cpy != 0)
	{
		if (point_s.z_cpy > point_f.z_cpy)
			return (get_color(point_f.x, x, \
			distance, cntrl->color, cntrl->end_color));
		if (point_s.z_cpy < point_f.z_cpy)
			return (get_color(point_f.x, x, \
			distance, cntrl->end_color, cntrl->color));
	}
	else
	{
		if (point_s.z_cpy > 0)
			return (cntrl->end_color);
		else
			return (cntrl->color);
	}
}
