/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_changes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:41:56 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:36:26 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(t_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 34)
			cntrl->points[i].y -= 10;
		if (key == 40)
			cntrl->points[i].y += 10;
		if (key == 38)
			cntrl->points[i].x -= 10;
		if (key == 37)
			cntrl->points[i].x += 10;
		i++;
	}
	find_center(cntrl);
}

void	scale(t_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 24)
			cntrl->points[i] = change_scale(cntrl->points[i], '+', \
				cntrl->dx, cntrl->dy);
		if (key == 27)
			cntrl->points[i] = change_scale(cntrl->points[i], '-', \
				cntrl->dx, cntrl->dy);
		i++;
	}
}

void	rotation(t_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 123)
			cntrl->points[i] = rotate_y(cntrl->points[i], -0.05, cntrl->dx);
		if (key == 126)
			cntrl->points[i] = rotate_x(cntrl->points[i], -0.05, cntrl->dy);
		if (key == 124)
			cntrl->points[i] = rotate_y(cntrl->points[i], 0.05, cntrl->dx);
		if (key == 125)
			cntrl->points[i] = rotate_x(cntrl->points[i], 0.05, cntrl->dy);
		if (key == 0)
			cntrl->points[i] = rotate_z(cntrl->points[i], -0.05, cntrl->dx, \
				cntrl->dy);
		if (key == 2)
			cntrl->points[i] = rotate_z(cntrl->points[i], 0.05, cntrl->dx, \
				cntrl->dy);
		i++;
	}
}
