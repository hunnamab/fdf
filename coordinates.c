#include "fdf.h"

int     decart_to_iso_x(int x, int y)
{
    return(x - y);
}

int     decart_to_iso_y(int x, int y)
{
    return (((x + y) / 2));
}