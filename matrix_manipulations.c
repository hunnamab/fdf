#include "fdf.h"

p_point change_scale(p_point point, char sign, double dx, double dy)
{
    if (sign == '+')
    {
        point.x = ((point.x - dx) * 1.1) + dx;
        point.y = ((point.y - dy) * 1.1) + dy;
    }
    if (sign == '-')
    {
        point.x = ((point.x - dx) / 1.1) + dx;
        point.y = ((point.y - dy) / 1.1) + dy;
    }
    return (point);
}

p_point change_alt(p_point point, int sign)
{
    //if (point.flatness != 0)
        //point.y += sign;
    return (point);
}

p_point rotate_z(p_point point, double gamma, double dx, double dy)
{
    double buf = point.x;
    point.x = ((point.x - dx) * cos(gamma) - (point.y - dy) * sin(gamma)) + dx;
    point.y = ((buf - dx) * sin(gamma) + (point.y - dy) * cos(gamma)) + dy;
    return (point);
}

p_point rotate_y(p_point point, double beta, double dx)
{
    double buf = point.x;
    point.x = (point.x - dx) * cos(beta) + point.z * sin(beta) + dx;
    point.z = -(buf - dx) * sin(beta) + point.z * cos(beta);
    return (point);
}

p_point rotate_x(p_point point, double alpha, double dy)
{
    double buf = point.y;
    point.y = (point.y - dy) * cos(alpha) + point.z * sin(alpha) + dy;
    point.z = -(buf - dy) * sin(alpha) + point.z * cos(alpha);
    return (point);
}

//создание единичной матрицы

/*void    make_identity(matrix_ptr i)
{
    i->elem[0][0] = i->elem[1][1] = i->elem[2][2] = i-> elem[3][3] = 1;
    i->elem[0][1] = i->elem[0][2] = i->elem[0][3] = 0;
    i->elem[1][0] = i->elem[1][2] = i->elem[1][3] = 0;
    i->elem[2][0] = i->elem[2][1] = i->elem[2][3] = 0;
    i->elem[3][0] = i->elem[3][1] = i->elem[3][2] = 0;
}

void clear_matrix(matrix_ptr m)
{
    m->elem[0][0] = m->elem[0][1] = m->elem[0][2] = m->elem[0][3] = 0;
    m->elem[1][0] = m->elem[1][1] = m->elem[1][2] = m->elem[1][3] = 0;
    m->elem[2][0] = m->elem[2][1] = m->elem[2][2] = m->elem[2][3] = 0;
    m->elem[3][0] = m->elem[3][1] = m->elem[3][2] = m->elem[3][3] = 0;
}

void mat_mul(m_point_ptr p, matrix_ptr m)
{
    double x_new;
    double y_new;

    x_new = p->cor[0] * m->elem[0][0] + p->cor[1] * m->elem[1][0] + p->cor[2] * m->elem[2][0] + m->elem[3][0];
    y_new = p->cor[0] * m->elem[0][1] + p->cor[1] * m->elem[1][1] + p->cor[2] * m->elem[2][1] + m->elem[3][1];

    p->cor[X_COMP] = x_new;
    p->cor[Y_COMP] = y_new;
}

void    scale_obj(c_cntrl *cntrl)
{
    int i = 0;

    while (i < cntrl->nmb_op)
    {
        mat_mul((m_point_ptr)&cntrl->points[i], (matrix_ptr)&cntrl->m_point_ptr->scale);
        i++;
    }
}*/
