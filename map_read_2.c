/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:03:36 by pmetron           #+#    #+#             */
/*   Updated: 2020/02/21 00:39:23 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char		*ft_strsub_hex(char const *s, unsigned int start)
{
	char	*str;
	size_t	i;
	size_t	len;

	str = NULL;
	i = start;
	len = 0;
	while (s[i])
	{
		len++;
		i++;
	}
	i = 0;
	if (s)
	{
		if (!(str = ft_memalloc(len)))
			return (NULL);
		while (i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
	}
	return (str);
}

uint32_t	hex2int(char *hex)
{
	uint32_t	val;
	uint8_t		byte;

	val = 0;
	while (*hex)
	{
		byte = *hex++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
	}
	return (val);
}

char		**double_arr_free(char **double_arr, char *line)
{
	int i;

	i = 0;
	ft_strdel(&line);
	while (double_arr[i])
	{
		free(double_arr[i]);
		i++;
	}
	free(double_arr);
	double_arr = NULL;
	return(double_arr);
}

void		point_arr_part_two(int fd, c_cntrl *cntrl, int i, int x)
{
	char	*line;
	char	**double_arr;
	int		j;

	j = 0;
	while ((get_next_line(fd, &line)) && (double_arr = ft_strsplit(line, ' ')))
	{
		while (double_arr[i])
		{
			cntrl->points[j].z = ft_atoi(double_arr[i]) * 8;
			cntrl->points[j].z_cpy = cntrl->points[j].z / 8;
			while (double_arr[i][x] != ',' && double_arr[i][x] != '\0')
				x++;
			if (double_arr[i][x + 3] != '\0')
				cntrl->points[j].color = \
				hex2int(ft_strsub_hex(double_arr[i], x + 3));
			else
				cntrl->points[j].color = 0;
			j++;
			i++;
			x = 0;
		}
		i = 0;
		double_arr = double_arr_free(double_arr, line);
	}
}

p_point		*point_arr(int fd, c_cntrl *cntrl, char *filename)
{
	char	*line;
	int		i;
	char	**double_arr;

	i = 0;
	while ((get_next_line(fd, &line)) && (double_arr = ft_strsplit(line, ' ')))
	{
		while (double_arr[i])
		{
			i++;
			cntrl->nmb_op++;
		}
		cntrl->nmb_or++;
		i = 0;
		double_arr = double_arr_free(double_arr, line);
	}
	(cntrl->nmb_op % cntrl->nmb_or) != 0 ? error_exit(ERR_MAP_VALID) : 0;
	cntrl->points = (p_point *)malloc(sizeof(p_point) * cntrl->nmb_op);
	close(fd);
	fd = open(filename, O_RDONLY);
	point_arr_part_two(fd, cntrl, 0, 0);
}
