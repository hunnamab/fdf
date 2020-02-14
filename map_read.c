#include "fdf.h"

p_point	*get_point_arr(char **arr, c_cntrl *cntrl)
{
	p_point *point_arr;

	point_arr = (p_point *)malloc(sizeof(p_point) * cntrl->nmb_op);
	cntrl->arr = arr;
	return (point_arr);
}

p_point	*get_double_arr(c_cntrl *cntrl, char *buf)
{
	char	**arr;
	char	*buf2;
	int		i;
	int		x;

	i = 0;
	x = 0;
	arr = (char **)malloc(sizeof(char *) * cntrl->nmb_or + 1);
	while (buf[i])
	{
		if (buf[i] == ' ' && buf[i + 1] == ' ')
			x++;
		i++;
	}
	i = i - x;
	buf2 = ft_strnew(i);
	i = 0;
	x = 0;
	while (buf[i])
	{
		if (buf[i] == ' ' && buf[i + 1] == ' ')
			i++;
		buf2[x] = buf[i];
		x++;
		i++;
	}
	i = 0;
	while (buf2[i])
	{
		buf2[i] == '\n' ? buf2[i] = ' ' : 0;
		i++;
	}
	arr = ft_strsplit(buf2, ' ');
	return (get_point_arr(arr, cntrl));
}

p_point	*point_arr(int fd, c_cntrl *cntrl)
{
	char	buf[64000];
	int		i;

	i = 0;
	if ((i = read(fd, buf, 64000)))
		buf[i] = '\0';
	else
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n' && buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n'))
			cntrl->nmb_op++;
		if (buf[i] == '\n')
			cntrl->nmb_or++;
		i++;
	}
	return ((get_double_arr(cntrl, buf)));
}
