/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 23:03:36 by pmetron           #+#    #+#             */
/*   Updated: 2020/02/20 01:36:07 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
void	error_exit(char *mes)
{
		printf("%s\n", mes);
	exit(1);
}
char	*ft_strsub_hex(char const *s, unsigned int start)
{
	char	*str;
	size_t	i;
    size_t len;

	str = NULL;
	i = start;
    len = 0;
    while(s[i])
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

uint32_t    hex2int(char *hex)
{
    uint32_t val = 0;
    while (*hex) {
        uint8_t byte = *hex++; 
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        val = (val << 4) | (byte & 0xF);
    }
    return (val);
}
p_point *point_arr_part_two(int fd, c_cntrl *cntrl, char *filename)
{
    int i;
    char *line;
    char **double_arr;
    int j;
    int x;

    x = 0;
    fd = open(filename, O_RDONLY);
    j = 0;
    i = 0;
    while((get_next_line(fd, &line)))
    {
        double_arr = ft_strsplit(line, ' ');
        while (double_arr[i])
        {
            cntrl->points[j].z = ft_atoi(double_arr[i]);
            cntrl->points[j].z_cpy =  cntrl->points[j].z;
            while(double_arr[i][x] != ',' && double_arr[i][x] != '\0')
                x++;
            x += 3;
            if (double_arr[i][x] != '\0')
                cntrl->points[j].color = hex2int(ft_strsub_hex(double_arr[i], x));
            else
                 cntrl->points[j].color = 0;
            i++;
            j++;
            x = 0;
        }
        i = 0;
    }
    return(0);
}
p_point	*point_arr(int fd, c_cntrl *cntrl, char *filename)
{
    char    *line;
    int     i;
    char **double_arr;
    int x;
    int j;

    x = 0;
    i = 0;
    j = 0;
    while((get_next_line(fd, &line)))
    {
        double_arr = ft_strsplit(line, ' ');
        while (double_arr[i])
        {
            i++;
            j++;
        }
        x++;
        i = 0;
    }
    cntrl->nmb_op = j;
    cntrl->nmb_or = x;
    (j % x) != 0 ? error_exit(ERR_MAP_VALID): 0;
    cntrl->points = (p_point *)malloc(sizeof(p_point) * j);
    close(fd);
    point_arr_part_two(fd, cntrl, filename);
    exit(1);
}