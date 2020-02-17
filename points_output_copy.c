#include "fdf.h"

double percent(int start, int curr_pos, int distance)
{
	double placement = curr_pos - start;
	return ((distance == 0) ? 1.0 : (placement/distance));
}
int get_light(int start_color, int end_color, double percentage)
{
	return ((int)((1 - percentage) * start_color + percentage * end_color));
}
int get_color(int start, int curr_pos, int distance, int start_color, int end_color)
{
	int red = 0;
	int green = 0;
	int blue = 0;
	double percentage;
	
	percentage = percent(start, curr_pos, distance);
	red = (get_light((start_color >> 16) & 255, (end_color >> 16) & 255, percentage));
	green = (get_light((start_color >> 8) & 255, (end_color >> 8) & 255, percentage));
	blue = get_light(start_color & 255, end_color & 255, percentage);
	return((red << 16) | (green << 8) | blue);
}

void	get_line_colored(c_cntrl *cntrl, p_point point_f, p_point point_s)
{
	int dx = (point_s.x - point_f.x) >= 0 ? 1 : -1;
	int dy = (point_s.y - point_f.y) >= 0 ? 1 : -1;

	int lengthX = abs((int)point_s.x - (int)point_f.x);
	int lengthY = abs((int)point_s.y - (int)point_f.y);
	int length;
	length = MAX(lengthX, lengthY);
	if (length == 0 && (point_f.y >= 0 && point_f.y < HEI && point_f.x >= 0 && point_f.x < WID) &&\
	 (point_s.y >= 0 && point_s.y < HEI && point_s.x >= 0 && point_s.x < WID))
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
				cntrl->data_ptr[y * WID + x] = point_s.z_cpy - point_f.z_cpy != 0 ? \
				get_color(point_f.x, x, ((int)point_s.x - (int)point_f.x), point_s.z_cpy > point_f.z_cpy ? \
				cntrl->color : 0xD54418, (point_s.z_cpy > point_f.z_cpy ? 0xD54418 : cntrl->color)) : point_s.z_cpy > 0 ? \
				0xD54418 : cntrl->color;
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
		int x = point_f.x;
		int y = point_f.y;
		int d = -lengthY;
		length++;
		while (length--)
		{
			if (y >= 0 && y < HEI && x >= 0 && x < WID)
				cntrl->data_ptr[y * WID + x] = point_s.z_cpy - point_f.z_cpy != 0 ? \
				get_color(point_f.y, y, \
				((int)point_s.y - (int)point_f.y), point_s.z_cpy > point_f.z_cpy ? \
				cntrl->color : 0xD54418, (point_s.z_cpy > point_f.z_cpy ? 0xD54418 : cntrl->color)) \
				: point_s.z_cpy > 0 ? 0xD54418 : cntrl->color;
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
			get_line_colored(cntrl, points[i], points[i + 1]);
			i++;
	}
}
