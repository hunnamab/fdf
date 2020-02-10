#include "fdf.h"

p_point iso_coor(p_point point, double angle, double x_pos, double y_pos)
{
    double buf = point.x;
    point.x = (point.x - point.y) * cos(angle) + x_pos;
    point.y = (point.y + buf) * sin(angle) - point.z + y_pos;
    return (point);
}
