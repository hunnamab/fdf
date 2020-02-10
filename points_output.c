#include "fdf.h"

void	get_line(c_cntrl *cntrl, int x1, int y1, int x2, int y2)
{
	int dx = (x2 - x1) >= 0 ? 1 : -1;
	int dy = (y2 - y1) >= 0 ? 1 : -1;

	int lengthX = abs(x2 - x1);
	int lengthY = abs(y2 - y1);

	int length;
	int grad = 1;
	length = MAX(lengthX, lengthY);

	if (length == 0)
		cntrl->data_ptr[y1 * WID + x1] = cntrl->color;
	if (lengthY <= lengthX)
	{
		int x = x1;
		int y = y1;
		int d = -lengthX;

		length++;
		while (length--)
		{
			if (y2 - y1 == 0)
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			else if (y2 > y1)
			{
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			}
			else if (y2 < y1)
			{
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			}
			x += dx;
			d += 2 * lengthY;
			if (d > 0)
			{	
				d -= 2 * lengthX;
				y += dy;
			}
		}
	}
	else
	{
		int x = x1;
		int y = y1;
		int d = -lengthY;
		length++;
		while (length--)
		{
			if (y2 - y1 == 0)
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			else if (y2 > y1)
			{
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			}
			else if (y2 < y1)
			{
				cntrl->data_ptr[y * WID + x] = cntrl->color;
			}
			y += dy;
			d += 2 * lengthX;
			if (d > 0)
			{
				d -= 2 * lengthY;
				x += dx;
			}
		}
	}
}
int32_t get_color(int32_t start_color, int y)
{
	int32_t i = start_color;
	int32_t red = 0;
	int32_t green = 0;
	int32_t blue = 0;

	red = (i >> 16) & 255;
	green = (i >> 8) & 255;
	blue = i & 255;
	red += y;
	green += y;
	blue += y;
	red > 255 ? red = 255 : 0;
	green > 255 ? green = 255 : 0;
	blue > 255 ? blue = 255 : 0;
	red < 0 ? red = 0 : 0;
	green < 0 ? green = 0 : 0;
	blue < 0 ? blue = 0 : 0;
	red &= 255;
	green &= 255;
	blue &= 255;
	return(red << 16 | green << 8 | blue);
}

void	get_line_colored(c_cntrl *cntrl, int x1, int y1, int x2, int y2)
{
	int dx = (x2 - x1) >= 0 ? 1 : -1;
	int dy = (y2 - y1) >= 0 ? 1 : -1;

	int lengthX = abs(x2 - x1);
	int lengthY = abs(y2 - y1);
	int grad = 0;
	int length;
	length = MAX(lengthX, lengthY);

	if (length == 0)
		cntrl->data_ptr[y1 * WID + x1] = cntrl->color;
	if (lengthY <= lengthX)
	{
		int x = x1;
		int y = y1;
		int d = -lengthX;
	
		length++;
		while (length--)
		{
			cntrl->data_ptr[y * WID + x] = get_color(cntrl->color, length);
			x += dx;
			d += 2 * lengthY;
			if (d > 0)
			{	
				d -= 2 * lengthX;
				y += dy;
			}
			grad++;
		}
	}
	else
	{
		int x = x1;
		int y = y1;
		int d = -lengthY;
		length++;
		while (length--)
		{
			cntrl->data_ptr[y * WID + x] = get_color(cntrl->color, length);
			y += dy;
			d += 2 * lengthX;
			if (d > 0)
			{
				d -= 2 * lengthY;
				x += dx;
			}
			grad++;
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
					if (!points[i].flatness & !points[i + cntrl->nmb_op / cntrl->nmb_or].flatness)
					{
						get_line(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
						i++;
						break ;
					}
					else
					{
						get_line_colored(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
						i++;
						break ;
					}	
				}
				if (i != a - 1)
				{
					if (!points[i].flatness & !points[i + 1].flatness & !points[i + cntrl->nmb_op / cntrl->nmb_or].flatness)
					{
						get_line(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
						get_line(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
					}
					else
					{
						get_line_colored(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
						get_line_colored(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
					}
				}
				i++;
		}
		a = a + cntrl->nmb_op / cntrl->nmb_or;
		j++;
	}
	while (i < a - 1)
	{
		if (!points[i].flatness & !points[i].flatness)
		{
			get_line(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
			i++;
		}
		else
		{
			get_line_colored(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
			i++;
		}
	}
}
