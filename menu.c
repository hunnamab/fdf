/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:22 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:17:19 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_menu(t_cntrl *cntrl)
{
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 250, IVORY, \
		"Change color:");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 270, IVORY, \
		"[1] - mint");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 290, IVORY, \
		"[2] - mars");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 310, IVORY, \
		"[3] - indigo");
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 340, IVORY, \
		"Exit [esc]");
}

void	show_menu(t_cntrl *cntrl)
{
	mlx_string_put(cntrl->mlx, cntrl->win, 80, 30, IVORY, \
		"Control keys");
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 60, IVORY, \
		"Rotate:");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 80, IVORY, \
		"X- and Y-axis rotation - arrows");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 100, IVORY, \
		"Z-axis rotation [a] / [d]");
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 130, IVORY, \
		"Change projection [z] / [x]");
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 150, IVORY, \
		"Scale [+] / [-]");
	mlx_string_put(cntrl->mlx, cntrl->win, 20, 180, IVORY, \
		"Move:");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 200, IVORY, \
		"up / down - [i] / [k]");
	mlx_string_put(cntrl->mlx, cntrl->win, 30, 220, IVORY, \
		"left / right - [j] / [l]");
	color_menu(cntrl);
}
