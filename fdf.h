/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:22:09 by hunnamab          #+#    #+#             */
/*   Updated: 2020/02/21 16:43:54 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include "mlx.h"
# include "error.h"
# include "libft.h"

# define WID	2000
# define HEI	1500

# define INDIGO	0x4B0082
# define MARS	0xD54418
# define MINT	0x30A497
# define IVORY	0xE4E4E1
# define RED	0xa4303d

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	double			z_cpy;
	uint32_t		color;
}					t_point;

typedef struct		s_cntrl
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				color;
	int32_t			end_color;
	t_point			*points;
	int				nmb_op;
	int				nmb_or;
	int				iso;
	double			angle;
	double			dx;
	double			dy;
	double			x_pos;
	double			y_pos;
	int				scale;
	int				z_max;
	int				z_min;
}					t_cntrl;

int					get_next_line(const int fd, char **line);
t_point				*point_arr(int fd, t_cntrl *cntrl, char *filename);
void				default_settings(t_cntrl *cntrl);
void				show_menu(t_cntrl *cntrl);
void				make_3d(t_cntrl *cntrl);
void				parallel_coor(t_cntrl *cntrl);
t_point				iso_coor(t_point point, double angle, double x_pos, \
						double y_pos);
void				find_center(t_cntrl *cntrl);
void				points_output(t_point *points, t_cntrl *cntrl, \
						int i, int j);
int					key_mouse_control(t_cntrl *cntrl);
void				rotation(t_cntrl *cntrl, int key);
void				altitude(t_cntrl *cntrl, int key);
void				scale(t_cntrl *cntrl, int key);
void				move(t_cntrl *cntrl, int key);
t_point				rotate_x(t_point point, double alpha, double dy);
t_point				rotate_y(t_point point, double beta, double dx);
t_point				rotate_z(t_point point, double gamma, double dx, double dy);
t_point				change_alt(t_point point, int sign);
t_point				change_scale(t_point point, char sign, double dx, \
						double dy);
void				error_exit(char *mes);
int					choose_color_x(t_cntrl *cntrl, t_point point_f, \
						t_point point_s, int x);
int					choose_color_y(t_cntrl *cntrl, t_point point_f, \
						t_point point_s, int y);
int					get_color(int start, int curr_pos, int distance, \
						t_cntrl *cntrl);
int					get_light(int start_color, int end_color, \
						double percentage);
double				percent(int start, int curr_pos, int distance);
void				cleanup(t_cntrl *cntrl);
void				validation(char *filename);

#endif
