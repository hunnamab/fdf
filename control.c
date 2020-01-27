#include "fdf.h"

void altitude(c_cntrl *cntrl, int key)
{
    int i = 0;
    int j = 0;
    int q = cntrl->nmb_op / cntrl->nmb_or;
    while (j < cntrl->nmb_or)
    {
        while (i < q)
        {
            if (key == 13) // w 0x0077
                cntrl->points[i] = change_alt(cntrl->points[i], '+');
            if (key == 1) // s 0x0073
                cntrl->points[i] = change_alt(cntrl->points[i], '-');
            i++;
        }
        q = q + (cntrl->nmb_op / cntrl->nmb_or);
        j++;
    }
}

void rotation(c_cntrl *cntrl, int key)
{
            if (key == 123) // left 0xff51
            {
                cntrl->angle += 0.05;
                make_3d(cntrl);
            }
            /*if (key == 126) // up 0xff52
            {
                cntrl->points[i] = rotate_x(cntrl->points[i], '-');
            }
            if (key == 124) // right 0xff53
            {
                cntrl->points[i] = rotate_y(cntrl->points[i], '-'); 
            }
            if (key == 125) // down 0xff54
            {
                cntrl->points[i] = rotate_x(cntrl->points[i], '+');
            }*/
}

int key_control(int key, c_cntrl *cntrl)
{
    if (key == 53) //0xff1b or 53
    {
        mlx_destroy_window(cntrl->mlx_ptr, cntrl->win_ptr);
        exit(EXIT_SUCCESS);
    }
    if (key == 18 || key == 19 || key == 20 || \
        key == 123 || key == 126 || key == 124 || key == 125 || \
        key == 13 || key == 1)
    {
        if (cntrl->img_ptr)
            mlx_destroy_image(cntrl->mlx_ptr, cntrl->img_ptr);
        cntrl->img_ptr = mlx_new_image(cntrl->mlx_ptr, WID, HEI);
        cntrl->data_ptr = (int *)mlx_get_data_addr(cntrl->img_ptr, &cntrl->bpp, &cntrl->size_line, &cntrl->endian);
        if (key == 18) //0x0031 or 18
            cntrl->color = MINT;
        if (key == 19) //0x0032 or 19
            cntrl->color = IVORY;
        if (key == 20) //0x0033 or 20
            cntrl->color = INDIGO;
        if (key == 123 || key == 126 || key == 124 || key == 125) //0xff51 123 left 2 126 up 3 124 right 4 125 down
            rotation(cntrl, key);
        if (key == 13 || key == 1) // 0x0077 13 w - altitude up, 0x0073 1 s - altitude down
            altitude(cntrl, key);
        points_output(cntrl->points, cntrl);
        mlx_put_image_to_window(cntrl->mlx_ptr, cntrl->win_ptr, cntrl->img_ptr, 0, 0);
    }
    return (0);
}

int key_mouse_control(c_cntrl *cntrl)
{
    mlx_hook(cntrl->win_ptr, 2, (1L<<0), key_control, cntrl);
    return (0);
}
