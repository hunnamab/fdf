#include "fdf.h"

int main(int argc, char **argv)
{
	int bpp;
	int size_line;
	int endian;
	c_cntrl *control;

	control = (c_cntrl *)ft_memalloc(sizeof(c_cntrl));
	control->mlx_ptr = mlx_init();
	control->win_ptr = mlx_new_window(control->mlx_ptr, 1024, 768, "fdfffs");
	control->img_ptr = mlx_new_image(control->mlx_ptr, 1024, 768); //create a new image to manipulate on
	control->data_ptr = (int *)mlx_get_data_addr(control->img_ptr, &bpp, &size_line, &endian);
	int count_h = 0;
	while (count_h < 768)
	{
		int count_w = 0;
		while (count_w < 1024)
		{
			if (!(count_w % 10))
				control->data_ptr[count_h * 1024 + count_w] = IVORY;
			else
				control->data_ptr[count_h * 1024 + count_w] = 0;
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(control->mlx_ptr, control->win_ptr, control->img_ptr, 0, 0);
	mlx_loop(control->mlx_ptr);
	return (0);
}