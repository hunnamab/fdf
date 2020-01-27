#include "fdf.h"

void	get_line(c_cntrl *cntrl, int x1, int y1, int x2, int y2)
{
	int dx = (x2 - x1) >= 0 ? 1 : -1;
	int dy = (y2 - y1) >= 0 ? 1 : -1;

	int lengthX = abs(x2 - x1);
	int lengthY = abs(y2 - y1);

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
			cntrl->data_ptr[y * WID + x] = cntrl->color;
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
			cntrl->data_ptr[y * WID + x] = cntrl->color;
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
				get_line(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
				i++;
				break ;
			}
			if (i != a - 1)
			{
				get_line(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
				get_line(cntrl, points[i].x, points[i].y, points[i + cntrl->nmb_op / cntrl->nmb_or].x, points[i + cntrl->nmb_op / cntrl->nmb_or].y);
			}
			i++;
		}
		a = a + cntrl->nmb_op / cntrl->nmb_or;
		j++;
	}
	while (i < a - 1)
	{
		get_line(cntrl, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		i++;
	}
}

int		number_of_rows(int fd)
{
	char buf[2048];
    int x = 0;
    int i = 0;

    if ((i = read(fd, buf, 2048)))
        buf[i] = '\0';
    else
        return 0;
    i = 0;
    while (buf[i])
    {
        if (buf[i] == '\n')
            x++;
        i++;
    }
    return (x);
}

int		number_of_points(int fd)
{
	char buf[2048];
    int x = 0;
    int i = 0;

    if ((i = read(fd, buf, 2048)))
        buf[i] = '\0';
    else
        return 0;
    i = 0;
    while (buf[i])
    {
        if (buf[i] != '\n' && buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n'))
            x++;
        i++;
    }
    return (x);
}

void make_3d(c_cntrl *cntrl)
{
	int i;
	int j;
	int q;

	i = 0;
	j = 0;
	q = cntrl->nmb_op / cntrl->nmb_or;
	while (j < cntrl->nmb_or)
	{
		while (i < q)
		{
			cntrl->points[i] = iso_coor(cntrl->points[i], cntrl->angle);
			i++;
		}
		q = q + (cntrl->nmb_op / cntrl->nmb_or);
		j++;
	}
}

int main(int argc, char **argv)
{
	int	fd;
	c_cntrl *cntrl;

	cntrl = (c_cntrl *)ft_memalloc(sizeof(c_cntrl));
	if (argc != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	cntrl->nmb_op = number_of_points(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	cntrl->nmb_or = number_of_rows(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	cntrl->points = point_arr(fd);
	cntrl->mlx_ptr = mlx_init();
	cntrl->win_ptr = mlx_new_window(cntrl->mlx_ptr, WID, HEI, "fdfffs");
	//create a pointer to a new image to manipulate on
	cntrl->img_ptr = mlx_new_image(cntrl->mlx_ptr, WID, HEI);
	//data_ptr contains info about the image created above, so points_output puts pixels in here first
	cntrl->data_ptr = (int *)mlx_get_data_addr(cntrl->img_ptr, &cntrl->bpp, &cntrl->size_line, &cntrl->endian);
	cntrl->angle = 0.523599;
	make_3d(cntrl);
	cntrl->color = MINT;
	points_output(cntrl->points, cntrl);
	//the next func displays the image
	mlx_put_image_to_window(cntrl->mlx_ptr, cntrl->win_ptr, cntrl->img_ptr, 0, 0);
	key_mouse_control(cntrl); //esc key only for now
	mlx_loop(cntrl->mlx_ptr);
	return (0);
}
