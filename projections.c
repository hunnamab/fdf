/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:36 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/17 16:31:05 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

p_point	iso_coor(p_point point, double angle, double x_pos, double y_pos)
{
	double buf;

	buf = point.x;
	point.x = (point.x - point.y) * cos(angle) + x_pos;
	point.y = (point.y + buf) * sin(angle) - point.z + y_pos;
	return (point);
}

void	parallel_coor(c_cntrl *cntrl)
{
	int i;
	int j;
	int q;
	int d;

	i = 0;
	j = 0;
	d = 0;
	q = cntrl->nmb_op / cntrl->nmb_or;
	while (j < cntrl->nmb_or)
	{
		while (i < q)
		{
			cntrl->points[i].x = (d * cntrl->scale) + (WID / 3);
			cntrl->points[i].y = (j * cntrl->scale) + (HEI / 3);
			cntrl->points[i].z = cntrl->points[i].z_cpy;
			i++;
			d++;
		}
		d = 0;
		q = q + (cntrl->nmb_op / cntrl->nmb_or);
		j++;
	}
}
