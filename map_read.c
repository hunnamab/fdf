/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:42:02 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/19 19:39:24 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

p_point	*get_point_arr(c_cntrl *cntrl)
{
	p_point *point_arr;

	point_arr = (p_point *)malloc(sizeof(p_point) * cntrl->nmb_op);
	return (point_arr);
}

p_point	*get_double_arr(c_cntrl *cntrl, char *buf)
{
	char	*buf2;
	int		i;
	int		x;

	i = 0;
	x = 0;
	cntrl->arr = (char **)malloc(sizeof(char *) * cntrl->nmb_or);
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
	cntrl->arr = ft_strsplit(buf2, ' ');
	ft_strdel(&buf2);
	return (get_point_arr(cntrl));
}

void	error_exit(char *mes)
{
		printf("%s\n", mes);
	exit(1);
}

int		get_points_in_row(char *buf, int i)
{
	int points_in_row;

	points_in_row = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			break;
		}
		if (buf[i] != '\n' && buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n') && buf[i]!= '-')
			points_in_row++;
		i++;
	}
	return(points_in_row);
}

p_point	*point_arr(int fd, c_cntrl *cntrl)
{
	char	buf[64000];
	int		i;
	int		points_in_row;

	points_in_row = 0;
	if ((i = read(fd, buf, 64000)))
		buf[i] = '\0';
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			break;
		}
		if (buf[i] != '\n' && buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n') && buf[i]!= '-')
			points_in_row++;
		i++;
	}
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n' && buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n') && buf[i] != '-')
			cntrl->nmb_op++;
		if (buf[i] == '\n' && buf[i + 1] != '\0')
		{
			cntrl->nmb_or++;
			cntrl->nmb_op / cntrl->nmb_or != points_in_row ? error_exit(ERR_MAP_VALID) : 0;
		}
		if (!(ft_isascii(buf[i])))
			error_exit(ERR_OPEN_FILE);
		i++;
	}
	cntrl->nmb_or += 1;
	if (cntrl->nmb_op % cntrl->nmb_or != 0 || cntrl->nmb_op == 0)
		error_exit(ERR_MAP_VALID);
	return ((get_double_arr(cntrl, buf)));
}
