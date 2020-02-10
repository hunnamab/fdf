#include "fdf.h"

int main(int argc, char **argv)
{
	int	fd;
	c_cntrl *cntrl;

	cntrl = (c_cntrl *)ft_memalloc(sizeof(c_cntrl));
	if (argc != 2)
	{
		ft_putstr("Usage: ./fdf [file_name.fdf]\n");
		exit(EXIT_SUCCESS);
	}
	fd = open(argv[1], O_RDONLY);
	cntrl->points = point_arr(fd, cntrl);
	close(fd);

	// !! map_settings.c contains functions default_settings, make_3d and find_center

	default_settings(cntrl); //default map parameters
	make_3d(cntrl); //create a 3d map from a flat one
	find_center(cntrl); //get central points of a map to rotate it
	points_output(cntrl->points, cntrl); //connect points to get a map
	mlx_put_image_to_window(cntrl->mlx_ptr, cntrl->win_ptr, cntrl->img_ptr, 0, 0);
	key_mouse_control(cntrl);
	mlx_loop(cntrl->mlx_ptr);
	return (0);
}
