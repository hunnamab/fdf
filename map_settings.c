/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:08 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:17:19 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_center(t_cntrl *cntrl)
{
	int		oneline_p;
	double	x;
	double	y;
	double	x2;
	double	y2;

	oneline_p = cntrl->nmb_op / cntrl->nmb_or;
	x = (cntrl->points[oneline_p - 1].x - cntrl->points[0].x) / 2;
	x = x + cntrl->points[0].x;
	x2 = (cntrl->points[cntrl->nmb_op - 1].x - cntrl->points[cntrl->nmb_op - \
		oneline_p].x) / 2;
	x2 = x2 + cntrl->points[cntrl->nmb_op - oneline_p].x;
	cntrl->dx = ((x - x2) / 2) + x2;
	y = (cntrl->points[cntrl->nmb_op - oneline_p].y - cntrl->points[0].y) / 2;
	y = y + cntrl->points[0].y;
	y2 = (cntrl->points[cntrl->nmb_op - 1].y - cntrl->points[oneline_p - 1].y) \
		/ 2;
	y2 = y2 + cntrl->points[oneline_p - 1].y;
	cntrl->dy = ((y2 - y) / 2) + y;
}

void	make_3d(t_cntrl *cntrl)
{
	int i;
	int j;
	int q;
	int d;

	i = 0;
	j = 0;
	q = cntrl->nmb_op / cntrl->nmb_or;
	while (j < cntrl->nmb_or)
	{
		d = 0;
		while (i < q)
		{
			cntrl->points[i].x = (d * cntrl->scale);
			cntrl->points[i].y = (j * cntrl->scale);
			cntrl->points[i] = iso_coor(cntrl->points[i], cntrl->angle, \
				cntrl->x_pos, cntrl->y_pos);
			i++;
			d++;
		}
		q = q + (cntrl->nmb_op / cntrl->nmb_or);
		j++;
	}
}

int		get_scale(t_cntrl *cntrl)
{
	int scale;

	scale = 20;
	while ((((cntrl->nmb_op / cntrl->nmb_or) * scale) > WID) \
	|| (cntrl->nmb_or * scale) > WID)
	{
		scale--;
	}
	return (scale);
}

void	get_z(t_cntrl *cntrl)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (cntrl->points[i].z_cpy > cntrl->z_max)
			cntrl->z_max = cntrl->points[i].z_cpy;
		if (cntrl->points[i].z_cpy < cntrl->z_min)
			cntrl->z_min = cntrl->points[i].z_cpy;
		i++;
	}
}

void	default_settings(t_cntrl *cntrl)
{
	cntrl->mlx = mlx_init();
	cntrl->win = mlx_new_window(cntrl->mlx, WID, HEI, "fdfffs");
	cntrl->img = mlx_new_image(cntrl->mlx, WID, HEI);
	cntrl->data = (int *)mlx_get_data_addr(cntrl->img, &cntrl->bpp, \
		&cntrl->size_line, &cntrl->endian);
	get_z(cntrl);
	cntrl->color = MINT;
	cntrl->end_color = RED;
	cntrl->angle = 0.523599;
	cntrl->scale = get_scale(cntrl);
	cntrl->iso = 1;
	cntrl->x_pos = WID / 3;
	cntrl->y_pos = HEI / 3;
}
