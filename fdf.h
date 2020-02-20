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
#include "error.h"
# define MAX(x,y) x > y ? x : y;

# define WID 3000
# define HEI 2000

# define INDIGO 0x4B0082
# define MARS 0xD54418
# define MINT 0x30A497
# define IVORY 0xE4E4E1
# define RED 0xa4303d
typedef struct      point
{
    double          x;
    double          y;
    double          z;
	double			z_cpy;
	uint32_t		color;
}                   p_point;

typedef struct  cntrl
{
	void        *mlx;
	void        *win;
	void        *img;
	int         *data;
	int         bpp;
	int         size_line;
	int         endian;
	int         color;
	int32_t     end_color;
	p_point     *points;
	int         nmb_op;
	int         nmb_or;
	int         iso;
	double      angle;
	double      dx;
	double      dy;
	double      x_pos;
	double      y_pos;
	int         scale;
	int			z_max;
	int			z_min;
}               c_cntrl;

int		get_next_line(const int fd, char **line);
p_point *point_arr(int fd, c_cntrl *cntrl, char *filename);
void    default_settings(c_cntrl *cntrl);
void    show_menu(c_cntrl *c_cntrl);
void    make_3d(c_cntrl *cntrl);
void	parallel_coor(c_cntrl *cntrl);
p_point iso_coor(p_point point, double angle, double x_pos, double y_pos);
void	find_center(c_cntrl *cntrl);
void	points_output(p_point *points, c_cntrl *cntrl, int i, int j);
int     key_mouse_control(c_cntrl *cntrl);
void    rotation(c_cntrl *cntrl, int key);
void    altitude(c_cntrl *cntrl, int key);
void    scale(c_cntrl *cntrl, int key);
void    move(c_cntrl *cntrl, int key);
p_point rotate_x(p_point point, double alpha, double dy);
p_point rotate_y(p_point point, double beta, double dx);
p_point rotate_z(p_point point, double gamma, double dx, double dy);
p_point change_alt(p_point point, int sign);
p_point change_scale(p_point point, char sign, double dx, double dy);
void	error_exit(char *mes);
int 	choose_color_x(c_cntrl *cntrl, p_point point_f, p_point point_s, int x);
int 	choose_color_y(c_cntrl *cntrl, p_point point_f, p_point point_s, int y);
int		get_color(int start, int curr_pos, int distance,\
int start_color, int end_color);
int		get_light(int start_color, int end_color, double percentage);
double	percent(int start, int curr_pos, int distance);
void	cleanup(c_cntrl *cntrl);
void	validation(char *filename);

#endif
