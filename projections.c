/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:36 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:29:05 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int curr_pos, int distance)
{
	double placement;

	placement = curr_pos - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

t_point	iso_coor(t_point point, double angle, double x_pos, double y_pos)
{
	double buf;

	buf = point.x;
	point.z = point.z_cpy * 8;
	point.x = (point.x - point.y) * cos(angle) + x_pos;
	point.y = (point.y + buf) * sin(angle) - point.z + y_pos;
	return (point);
}

void	parallel_coor(t_cntrl *cntrl)
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
			cntrl->points[i].z = cntrl->points[i].z_cpy * 8;
			i++;
			d++;
		}
		d = 0;
		q = q + (cntrl->nmb_op / cntrl->nmb_or);
		j++;
	}
}
