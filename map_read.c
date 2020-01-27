#include "fdf.h"

p_point iso_coor(p_point point, double angle)
{
    //double buf = point.x;
    point.x = (point.x - point.y) * cos(angle);
    point.y = (point.y + point.x) * sin(angle) - point.z;
    return (point);
}

p_point change_alt(p_point point, char sign)
{
    if (sign == '+')
        point.y = point.y + point.z * sin(-0.15);
    if (sign == '-')
        point.y = point.y + point.z * sin(0.15);
    return(point);
}

p_point rotate_z(p_point point, char sign)
{
    double buf = point.x;
    if (sign == '+')
    {
        point.x = point.x * cos(0.05) - point.y * sin(0.05);
        point.y = buf * sin(0.05) + point.y * cos(0.05);
    }
    else
    {
        point.x = point.x * cos(-0.05) - point.y * sin(-0.05);
        point.y = buf * sin(-0.05) + point.y * cos(-0.05);
    }
    return(point); 
}

p_point rotate_y(p_point point, char sign)
{
    double buf = point.x;
    if (sign == '+')
    {
        point.x = point.x * cos(0.05) + point.z * sin(0.05);
        point.z = -buf * sin(0.05) + point.z * cos(0.05);
    }
    else
    {
        point.x = point.x * cos(-0.05) + point.z * sin(-0.05);
        point.z = -buf * sin(-0.05) + point.z * cos(-0.05);
    }
    return(point);
}

p_point rotate_x(p_point point, char sign)
{
    double buf = point.y;
    if (sign == '+')
    {
        point.y = point.y * cos(0.05) + point.z * sin(0.05);
        point.z = -buf * sin(0.05) + point.z * cos(0.05);
    }
    else
    {
        point.y = point.y * cos(-0.05) + point.z * sin(-0.05);
        point.z = -buf * sin(-0.05) + point.z * cos(-0.05);
    }
    return(point);
}

p_point *get_point_arr(char **arr, int points, int rows)
{
    int i = 0;
    int j = 0;
    int a = 0;
    int q = points / rows;
    int d = 0;
    p_point *point_arr;

    point_arr = (p_point *)malloc(sizeof(p_point) * points);
    while (j < rows)
    {
        while(i < q)
        {
            point_arr[i].z = ft_atoi(arr[a]);
            point_arr[i].x = (d * 30);
            point_arr[i].y = (j * 30);
            //point_arr[i] = iso_coor(point_arr[i]);
            point_arr[i].x += 400;
            //point_arr[i].y += 500;
            a++;
            d++;
            i++;
        }
        d = 0;
        q = q + (points / rows);
        j++;
    }
    return(point_arr);
}

p_point *get_double_arr(int points, int rows, char *buf)
{
    char **arr;
    char *buf2;
    int i = 0;
    int x = 0;

    arr = (char **)malloc(sizeof(char *) * rows + 1);
    while(buf[i])
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
    while(buf2[i])
    {
        buf2[i] == '\n' ? buf2[i] = ' ' : 0;
        i++;
    }
    arr = ft_strsplit(buf2, ' ');
    return (get_point_arr(arr, points, rows));
}

p_point *point_arr(int fd)
{
    char buf[2048];
    int x = 0;
    int j = 0;
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
        if (buf[i] == '\n')
            j++;
        i++;
    }
    return ((get_double_arr(x, j, buf)));
}
