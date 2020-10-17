/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:40:58 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:17:19 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup(t_cntrl *cntrl)
{
	ft_memdel((void **)&cntrl->points);
	ft_memdel((void **)&cntrl);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_cntrl	*cntrl;

	if (!(cntrl = (t_cntrl *)ft_memalloc(sizeof(t_cntrl))))
		return (0);
	if (argc != 2)
		error_exit(ERR_USAGE);
	validation(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(ERR_USAGE);
	point_arr(fd, cntrl, argv[1]);
	close(fd);
	default_settings(cntrl);
	make_3d(cntrl);
	find_center(cntrl);
	points_output(cntrl->points, cntrl, 0, 0);
	mlx_put_image_to_window(cntrl->mlx, cntrl->win, cntrl->img, 0, 0);
	show_menu(cntrl);
	key_mouse_control(cntrl);
	mlx_loop(cntrl->mlx);
	return (0);
}
