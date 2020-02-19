/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:41:49 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/19 19:26:40 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_changes(int key, c_cntrl *cntrl)
{
	if ((key >= 123 && key <= 126) || (key == 0 || key == 2))
		rotation(cntrl, key);
	if (key == 24 || key == 27)
		scale(cntrl, key);
	if (key == 34 || key == 38 || key == 40 || key == 37)
		move(cntrl, key);
	if (key == 6)
	{
		parallel_coor(cntrl);
		find_center(cntrl);
	}
	if (key == 7)
	{
		make_3d(cntrl);
		find_center(cntrl);
	}
}
void color_changes(int key, c_cntrl *cntrl)
{
	if (key == 18)
	{
		cntrl->color = MINT;
		cntrl->end_color = RED;
	}
	if (key == 19)
	{
		cntrl->color = MARS;
		cntrl->end_color = IVORY;
	}
	if (key == 20)
	{
		cntrl->color = INDIGO;
		cntrl->end_color = MARS;
	}
}
int		key_control(int key, c_cntrl *cntrl)
{
	if (key == 53)
	{
		mlx_destroy_window(cntrl->mlx, cntrl->win);
		exit(EXIT_SUCCESS);
	}
	if (key == 18 || key == 19 || key == 20 || key == 123 || key == 126 || \
		key == 124 || key == 125 || key == 0 || key == 2 || key == 6 || \
		key == 7 || key == 24 || key == 27 || key == 34 || key == 38 || \
		key == 40 || key == 37)
	{
		if (cntrl->img)
			mlx_destroy_image(cntrl->mlx, cntrl->img);
		cntrl->img = mlx_new_image(cntrl->mlx, WID, HEI);
		cntrl->data = (int *)mlx_get_data_addr(cntrl->img, \
			&cntrl->bpp, &cntrl->size_line, &cntrl->endian);
		img_changes(key, cntrl);
		color_changes(key, cntrl);
		points_output(cntrl->points, cntrl, 0, 0);
		mlx_put_image_to_window(cntrl->mlx, cntrl->win, cntrl->img, 0, 0);
		show_menu(cntrl);
	}
	return (0);
}

int		key_mouse_control(c_cntrl *cntrl)
{
	mlx_hook(cntrl->win, 2, (1L << 0), key_control, cntrl);
	return (0);
}
