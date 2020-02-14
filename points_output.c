#include "fdf.h"

int32_t get_color(int32_t start_color, int32_t y)
{
	int32_t i = start_color;
	int32_t red = 0;
	int32_t green = 0;
	int32_t blue = 0;
	
	red = i & 255;
	red += y;
	green = (i >> 8) & 255;
	green += y;
	blue = (i >> 16) & 255;
	blue += y;
	red > 255 ? red = 255 : 0;
	green > 255 ? green = 255 : 0;
	blue > 255 ? blue = 255 : 0;
	return(red | green << 8 | blue << 16);
}

void	get_line_colored(c_cntrl *cntrl, p_point point_f, p_point point_s)
{
	int dx = (point_s.x - point_f.x) >= 0 ? 1 : -1;
	int dy = (point_s.y - point_f.y) >= 0 ? 1 : -1;

	int lengthX = abs((int)point_s.x - (int)point_f.x);
	int lengthY = abs((int)point_s.y - (int)point_f.y);
	int length;
	length = MAX(lengthX, lengthY);
	int grad = point_s.z > point_f.z ? 0 : point_f.z + length;
	int grad_s = point_s.z > point_f.z ? point_s.z + length : 0;
	(point_s.z == point_f.z) > 0 ? grad = point_f.z + length : 0;
	if (length == 0)
		cntrl->data_ptr[(int)point_f.y * WID + (int)point_f.x] = cntrl->color;
	if (lengthY <= lengthX)
	{
		int x = point_f.x;
		int y = point_f.y;
		int d = -lengthX;
	
		length++;
		while (length--)
		{
			if (y >= 0 && y < HEI && x >= 0 && x < WID)
				cntrl->data_ptr[y * WID + x] = get_color(cntrl->color, grad);
			x += dx;
			d += 2 * lengthY;
			if (d > 0)
			{	
				d -= 2 * lengthX;
				y += dy;
			}
			grad_s > grad ? grad++ : grad--;
		}	
	}
	else
	{
		int x = point_f.x;
		int y = point_f.y;
		int d = -lengthY;
		length++;
		while (length--)
		{
			if (y >= 0 && y < HEI && x >= 0 && x < WID)
				cntrl->data_ptr[y * WID + x] = get_color(cntrl->color, grad);
			y += dy;
			d += 2 * lengthX;
			if (d > 0)
			{
				d -= 2 * lengthY;
				x += dx;
			}
			grad_s > grad ? grad++ : grad--;
		}
	}
}

void	points_output(p_point *points, c_cntrl *cntrl)
{
	int i = 0;
	int j = 1;
	int a = cntrl->nmb_op / cntrl->nmb_or;

	while (j < cntrl->nmb_or)
	{
		while(i < a)
		{
				if (i == a - 1)
				{
						get_line_colored(cntrl, points[i], points[i + cntrl->nmb_op / cntrl->nmb_or]);
						i++;
						break ;
				}
				if (i != a - 1)
				{
					get_line_colored(cntrl, points[i], points[i + 1]);
					get_line_colored(cntrl, points[i], points[i + cntrl->nmb_op / cntrl->nmb_or]);
				}
				i++;
		}
		a = a + cntrl->nmb_op / cntrl->nmb_or;
		j++;
	}
	while (i < a - 1)
	{
		if (!points[i].flatness && !points[i].flatness)
		{
			get_line_colored(cntrl, points[i], points[i + 1]);
			i++;
		}
	}
}
