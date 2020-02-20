/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:40:58 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 00:46:39 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	cleanup(c_cntrl *cntrl)
{
	ft_memdel((void **)&cntrl->points);
	ft_memdel((void **)&cntrl);
}
int	main(int argc, char **argv)
{
	int		fd;
	c_cntrl	*cntrl;

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
	point_arr(fd, cntrl, argv[1]);
	close(fd);
	cleanup(cntrl);
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
