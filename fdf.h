/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:16:21 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/17 16:19:13 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define INDIGO	0x4B0082
# define MARS	0xD54418
# define MINT	0x30A497
# define IVORY	0xE4E4E1

typedef struct	point
{
    double		x;
    double		y;
    double		z;
	double		z_cpy;
}				p_point;

typedef struct	cntrl
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			color;
	int32_t		end_color;
	p_point		*points;
	int			nmb_op;
	int			nmb_or;
	int			iso;
	double		angle;
	double		dx;
	double		dy;
	double		x_pos;
	double		y_pos;
	int			scale;
	char		**arr;
}				c_cntrl;

int		get_next_line(const int fd, char **line);
p_point	*point_arr(int fd, c_cntrl *cntrl);
void	default_settings(c_cntrl *cntrl);
void	show_menu(c_cntrl *c_cntrl);
void	make_3d(c_cntrl *cntrl);
void	parallel_coor(c_cntrl *cntrl);
p_point	iso_coor(p_point point, double angle, double x_pos, double y_pos);
void	find_center(c_cntrl *cntrl);
void	points_output(p_point *points, c_cntrl *cntrl);
int		key_mouse_control(c_cntrl *cntrl);
void	rotation(c_cntrl *cntrl, int key);
void	altitude(c_cntrl *cntrl, int key);
void	scale(c_cntrl *cntrl, int key);
void	move(c_cntrl *cntrl, int key);
p_point	rotate_x(p_point point, double alpha, double dy);
p_point	rotate_y(p_point point, double beta, double dx);
p_point	rotate_z(p_point point, double gamma, double dx, double dy);
p_point	change_alt(p_point point, int sign);
p_point	change_scale(p_point point, char sign, double dx, double dy);

#endif
