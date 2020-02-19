/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:40:58 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/19 23:48:19 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		fd;
	c_cntrl	*cntrl;
	int i = 0;

	if (!(cntrl = (c_cntrl *)ft_memalloc(sizeof(c_cntrl))))
		return (0);
	if (argc != 2)
	{
		ft_putstr("Usage: ./fdf <file_name.fdf>\n");
		exit(EXIT_SUCCESS);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(ERR_OPEN_FILE);
	cntrl->points = point_arr(fd, cntrl, argv[1]);
	close(fd);
	default_settings(cntrl);
	make_3d(cntrl);
	find_center(cntrl);
	points_output(cntrl->points, cntrl, 0, 0);
	mlx_put_image_to_window(cntrl->mlx, cntrl->win, cntrl->img, 0, 0);
	show_menu(cntrl);
	key_mouse_control(cntrl);
	mlx_loop(cntrl->mlx);
	free(&cntrl->points);
	free(&cntrl);
	return (0);
}
