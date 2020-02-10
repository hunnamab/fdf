#include "fdf.h"

// !! matrix_manipulations.c contains functions change_alt, rotate_x, rotate_y and rotate_z

void move(c_cntrl *cntrl, int key)
{
    int i = 0;

    while (i < cntrl->nmb_op)
    {
        if (key == 34) // i - up
            cntrl->points[i].y -= 10;
        if (key == 40) // k - down
            cntrl->points[i].y += 10;
        if (key == 38) // j - left
            cntrl->points[i].x -= 10;
        if (key == 37) // l - right
            cntrl->points[i].x += 10;
        i++;
    }
    find_center(cntrl);
}

void scale(c_cntrl *cntrl, int key)
{
    int i = 0;
    while (i < cntrl->nmb_op)
    {
        if (key == 24) // 0x0039 9
        {
            cntrl->points[i] = change_scale(cntrl->points[i], '+', cntrl->dx, cntrl->dy);
        }
        if (key == 27) // 0x0038 8
        {
            cntrl->points[i] = change_scale(cntrl->points[i], '-', cntrl->dx, cntrl->dy);
        }
        i++;
    }
}

void altitude(c_cntrl *cntrl, int key)
{
    int i = 0;

    while (i < cntrl->nmb_op)
    {
        if (key == 13) // 0x0077 w
            cntrl->points[i] = change_alt(cntrl->points[i], -1);
        if (key == 1) // 0x0073 s
            cntrl->points[i] = change_alt(cntrl->points[i], 1);
        i++;
    }
}

void rotation(c_cntrl *cntrl, int key)
{
    int i = 0;

    while (i < cntrl->nmb_op)
    {
        if (key == 123) // 0xff51 left
        {
            cntrl->beta = -0.05;
            cntrl->points[i] = rotate_y(cntrl->points[i], cntrl->beta, cntrl->dx);
        }
        if (key == 126) // up 0xff52
        {
            cntrl->alpha = 0.05;
            cntrl->points[i] = rotate_x(cntrl->points[i], cntrl->alpha, cntrl->dy);
        }
        if (key == 124) // right 0xff53
        {
            cntrl->beta = 0.05;
            cntrl->points[i] = rotate_y(cntrl->points[i], cntrl->beta, cntrl->dx); 
        }
        if (key == 125) // down 0xff54
        {
            cntrl->alpha = -0.05;
            cntrl->points[i] = rotate_x(cntrl->points[i], cntrl->alpha, cntrl->dy);
        }
        if (key == 0) // 0x0061 a 
        {
            cntrl->gamma = -0.05;
            cntrl->points[i] = rotate_z(cntrl->points[i], cntrl->gamma, cntrl->dx, cntrl->dy);
        }
        if (key == 2) // 0x0064 d
        {
            cntrl->gamma = 0.05;
            cntrl->points[i] = rotate_z(cntrl->points[i], cntrl->gamma, cntrl->dx, cntrl->dy);
        }
        i++;
    }
}
