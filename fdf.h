#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <stdint.h>
#include <mlx.h>

# define MAX(x,y) x > y ? x : y;

# define WID 1024
# define HEI 768

# define INDIGO 0x4B0082
# define IVORY 0xFFFFF0
# define MINT 0x30A497

typedef struct  point
{
    double      x;
    double      y;
    double      z;
}               p_point;

typedef struct  cntrl
{
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img_ptr; //pointer to an image
    int         *data_ptr; //pointer to data address (mlx_get_data_addr)
    int         bpp;
	int         size_line;
	int         endian;
    int         color;
    int         nmb_op;
	int         nmb_or;
    double      angle;
    p_point     *points;
}               c_cntrl;

int             ft_new_line(char **s, char **line, int fd, int ret);
int             get_next_line(const int fd, char **line);
int             decart_to_iso_x(int x, int y);
int             decart_to_iso_y(int x, int y);
p_point         *point_arr(int fd);
p_point         rotate_x(p_point point, char sign);
p_point         rotate_y(p_point point, char sign);
p_point         rotate_z(p_point point, char sign);
p_point         iso_coor(p_point point, double angle);
p_point         change_alt(p_point point, char sign);
int             key_mouse_control(c_cntrl *cntrl);
void            points_output(p_point *points, c_cntrl *cntrl);
void            make_3d(c_cntrl *cntrl);

#endif
