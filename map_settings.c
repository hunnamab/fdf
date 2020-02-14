#include "fdf.h"

void	find_center(c_cntrl *cntrl)
{
	double x;
	double y;
	double x2;
	double y2;

	x = (cntrl->points[(cntrl->nmb_op / cntrl->nmb_or) - 1].x - cntrl->points[0].x) / 2;
	x = x + cntrl->points[0].x;
	x2 = (cntrl->points[cntrl->nmb_op - 1].x - cntrl->points[cntrl->nmb_op - (cntrl->nmb_op / cntrl->nmb_or)].x) / 2;
	x2 = x2 + cntrl->points[cntrl->nmb_op - (cntrl->nmb_op / cntrl->nmb_or)].x;
	cntrl->dx = ((x - x2) / 2) + x2;
	y = (cntrl->points[cntrl->nmb_op - (cntrl->nmb_op / cntrl->nmb_or)].y - cntrl->points[0].y) / 2;
	y = y + cntrl->points[0].y;
	y2 = (cntrl->points[cntrl->nmb_op - 1].y - cntrl->points[(cntrl->nmb_op / cntrl->nmb_or) - 1].y) / 2;
	y2 = y2 + cntrl->points[(cntrl->nmb_op / cntrl->nmb_or) - 1].y;
	cntrl->dy = ((y2 - y) / 2) + y;
	//printf("z = %f\nz2 = %f\n", z, z2);
	//printf("dx = %f\ndy = %f\n", cntrl->dx, cntrl->dy);
}

void make_3d(c_cntrl *cntrl)
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
			cntrl->points[i].x = (d * cntrl->scale);
            cntrl->points[i].y = (j * cntrl->scale);
			cntrl->points[i].z = ft_atoi(cntrl->arr[i]);
            // !! projections.c contains iso_coor function
			cntrl->points[i] = iso_coor(cntrl->points[i], cntrl->angle, cntrl->x_pos, cntrl->y_pos);
			i++;
			d++;
		}
		d = 0;
		q = q + (cntrl->nmb_op / cntrl->nmb_or);
		j++;
	}
}

void default_settings(c_cntrl *cntrl)
{
	cntrl->mlx_ptr = mlx_init();
	cntrl->win_ptr = mlx_new_window(cntrl->mlx_ptr, WID, HEI, "fdfffs");
	//create a pointer to a new image to manipulate on
	cntrl->img_ptr = mlx_new_image(cntrl->mlx_ptr, WID, HEI);
	//data_ptr contains info about the image created above, so points_output puts pixels in here first
	cntrl->data_ptr = (int *)mlx_get_data_addr(cntrl->img_ptr, &cntrl->bpp, &cntrl->size_line, &cntrl->endian);
	cntrl->color = MINT;
	cntrl->angle = 0.523599;
	cntrl->scale = 20;
	cntrl->iso = 1;
	cntrl->alpha = 0;
	cntrl->beta = 0;
	cntrl->gamma = 0;
	cntrl->x_pos = WID / 3;
	cntrl->y_pos = HEI / 3;
}
