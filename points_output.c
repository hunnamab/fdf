/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:30 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:18:36 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_x_line(t_point point_f, t_point point_s, int length, t_cntrl *cntrl)
{
	int x;
	int y;
	int d;
	int length_x;
	int length_y;

	length_y = abs((int)point_s.y - (int)point_f.y);
	length_x = abs((int)point_s.x - (int)point_f.x);
	x = point_f.x;
	y = point_f.y;
	d = -length_x;
	while (length--)
	{
		if (y >= 0 && y < HEI && x >= 0 && x < WID)
			cntrl->data[y * WID + x] = \
				choose_color_x(cntrl, point_f, point_s, x);
		x += (point_s.x - point_f.x) >= 0 ? 1 : -1;
		d += 2 * length_y;
		if (d > 0)
		{
			d -= 2 * length_x;
			y += (point_s.y - point_f.y) >= 0 ? 1 : -1;
		}
	}
}

void	get_y_line(t_point point_f, t_point point_s, int length, t_cntrl *cntrl)
{
	int x;
	int y;
	int d;
	int length_x;
	int length_y;

	length_y = abs((int)point_s.y - (int)point_f.y);
	length_x = abs((int)point_s.x - (int)point_f.x);
	x = point_f.x;
	y = point_f.y;
	d = -length_y;
	while (length--)
	{
		if (y >= 0 && y < HEI && x >= 0 && x < WID)
			cntrl->data[y * WID + x] = \
				choose_color_y(cntrl, point_f, point_s, y);
		y += (point_s.y - point_f.y) >= 0 ? 1 : -1;
		d += 2 * length_x;
		if (d > 0)
		{
			d -= 2 * length_y;
			x += (point_s.x - point_f.x) >= 0 ? 1 : -1;
		}
	}
}

void	get_line_colored(t_cntrl *cntrl, t_point point_f, t_point point_s)
{
	int length;
	int length_x;
	int length_y;

	length_y = abs((int)point_s.y - (int)point_f.y);
	length_x = abs((int)point_s.x - (int)point_f.x);
	length = length_x > length_y ? length_x : length_y;
	if (length == 0 && (point_f.y >= 0 && point_f.y < HEI && point_f.x >= 0 \
			&& point_f.x < WID) && (point_s.y >= 0 && point_s.y < HEI \
			&& point_s.x >= 0 && point_s.x < WID))
		cntrl->data[(int)point_f.y * WID + (int)point_f.x] = cntrl->color;
	if (length_y <= length_x)
		get_x_line(point_f, point_s, length + 1, cntrl);
	else
		get_y_line(point_f, point_s, length + 1, cntrl);
}

void	norme(t_point *points, t_cntrl *cntrl, int i, int a)
{
	while (i < a - 1)
	{
		get_line_colored(cntrl, points[i], points[i + 1]);
		i++;
	}
}

void	points_output(t_point *points, t_cntrl *cntrl, int i, int j)
{
	int a;
	int b;

	b = cntrl->nmb_op / cntrl->nmb_or;
	a = cntrl->nmb_op / cntrl->nmb_or;
	while (++j < cntrl->nmb_or)
	{
		while (i < a)
		{
			if (i == a - 1)
			{
				get_line_colored(cntrl, points[i], points[i + b]);
				i++;
				break ;
			}
			if (i != a - 1)
			{
				get_line_colored(cntrl, points[i], points[i + 1]);
				get_line_colored(cntrl, points[i], points[i + b]);
			}
			i++;
		}
		a = a + b;
	}
	norme(cntrl->points, cntrl, i, a);
}
