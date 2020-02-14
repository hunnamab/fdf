#include "fdf.h"

void	move(c_cntrl *cntrl, int key)
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

void	scale(c_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 24)
			cntrl->points[i] = change_scale(cntrl->points[i], '+', cntrl->dx, cntrl->dy);
		if (key == 27)
			cntrl->points[i] = change_scale(cntrl->points[i], '-', cntrl->dx, cntrl->dy);
		i++;
	}
}

void	altitude(c_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 13)
			cntrl->points[i] = change_alt(cntrl->points[i], -1);
		if (key == 1)
			cntrl->points[i] = change_alt(cntrl->points[i], 1);
		i++;
	}
}

void	rotation(c_cntrl *cntrl, int key)
{
	int i;

	i = 0;
	while (i < cntrl->nmb_op)
	{
		if (key == 123)
		{
			cntrl->beta = -0.05;
			cntrl->points[i] = rotate_y(cntrl->points[i], cntrl->beta, cntrl->dx);
		}
		if (key == 126)
		{
			cntrl->alpha = 0.05;
			cntrl->points[i] = rotate_x(cntrl->points[i], cntrl->alpha, cntrl->dy);
		}
		if (key == 124)
		{
			cntrl->beta = 0.05;
			cntrl->points[i] = rotate_y(cntrl->points[i], cntrl->beta, cntrl->dx); 
		}
		if (key == 125)
		{
			cntrl->alpha = -0.05;
			cntrl->points[i] = rotate_x(cntrl->points[i], cntrl->alpha, cntrl->dy);
		}
		if (key == 0)
		{
			cntrl->gamma = -0.05;
			cntrl->points[i] = rotate_z(cntrl->points[i], cntrl->gamma, cntrl->dx, cntrl->dy);
		}
		if (key == 2)
		{
			cntrl->gamma = 0.05;
			cntrl->points[i] = rotate_z(cntrl->points[i], cntrl->gamma, cntrl->dx, cntrl->dy);
		}
		i++;
	}
}
