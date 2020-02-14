#include "fdf.h"

void	color_menu(c_cntrl *cntrl)
{
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 270, IVORY, \
		"Change color:");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 290, IVORY, \
		"[1] - mint");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 310, IVORY, \
		"[2] - brick");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 330, IVORY, \
		"[3] - indigo");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 360, IVORY, \
		"Exit [esc]");
}

void	show_menu(c_cntrl *cntrl)
{
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 80, 30, IVORY, \
		"Control keys");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 60, IVORY, \
		"Rotate:");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 80, IVORY, \
		"X- and Y-axis rotation - arrows");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 100, IVORY, \
		"Z-axis rotation [a] / [d]");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 130, IVORY, \
		"Change altitude [w] / [s]");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 150, IVORY, \
		"Change projection [z] / [x]");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 170, IVORY, \
		"Scale [+] / [-]");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 20, 200, IVORY, \
		"Move:");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 220, IVORY, \
		"up / down - [i] / [k]");
	mlx_string_put(cntrl->mlx_ptr, cntrl->win_ptr, 30, 240, IVORY, \
		"left / right - [j] / [l]");
	color_menu(cntrl);
}
