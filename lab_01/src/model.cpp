#include "model.h"
#include <cmath>
#include <stdint.h>

void destroy_pt_arr(pt_arr_t arr)
{
    if (arr.arr != nullptr)
        for (size_t i = 0; i < arr.len; ++i)
            destroy_point(arr.arr[i]);

    free(arr.arr);
}

void destroy_con_arr(con_arr_t arr)
{
    if (arr.arr != nullptr)
        for (size_t i = 0; i < arr.len; ++i)
            destroy_connection(arr.arr[i]);

    free(arr.arr);
}

point_t alloc_point()
{
    point_t res = (point_t)calloc(1, sizeof(struct point));
    return res;
}

point_t create_point(double x, double y, double z)
{
    point_t res = alloc_point();
    if (res != nullptr)
    {
        res->x = x;
        res->y = y;
        res->z = z;
    }

    return res;
}

void destroy_point(point_t &pt)
{
    free(pt);
    pt = nullptr;
}

connection_t alloc_connection()
{
    connection_t res = (connection_t)calloc(1, sizeof(struct connection));
    return res;
}

connection_t create_connection(point_t p1, point_t p2)
{
    connection_t res = alloc_connection();
    if (res != nullptr)
    {
        res->p1 = p1;
        res->p2 = p2;
    }

    return res;
}

void destroy_connection(connection_t &con)
{
    free(con);
    con = nullptr;
}

model_t alloc_model()
{
    model_t res = (model_t)calloc(1, sizeof(struct model));
    return res;
}

model_t create_model(pt_arr_t pt_arr, con_arr_t con_arr)
{
    model_t res = alloc_model();
    if (res != nullptr)
    {
        res->pt_arr = pt_arr;
        res->con_arr = con_arr;
    }

    return res;
}

void destroy_model(model_t &gr)
{
    if (gr == nullptr)
        return;

    destroy_pt_arr(gr->pt_arr);
    destroy_con_arr(gr->con_arr);

    free(gr);
    gr = nullptr;
}

int transform_point_scale(point_t pt, const point_t origin, const point_t coeffs)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (coeffs == nullptr)
        return TRANSFORM_NO_DATA;

    pt->x = (pt->x - origin->x) * coeffs->x + origin->x;
    pt->y = (pt->y - origin->y) * coeffs->y + origin->y;
    pt->z = (pt->z - origin->z) * coeffs->z + origin->z;

    return 0;
}

int transform_point_rotate(point_t pt, const point_t origin, const point_t angles)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (angles == nullptr)
        return TRANSFORM_NO_DATA;

    double cos_ax = cos(angles->x);
    double cos_ay = cos(angles->y);
    double cos_az = cos(angles->z);
    double sin_ax = sin(angles->x);
    double sin_ay = sin(angles->y);
    double sin_az = sin(angles->z);

    double dx = pt->x - origin->x;
    double dy = pt->y - origin->y;
    double dz = pt->z - origin->z;

    // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
    double newx = dx * cos_ay * cos_az -   //
                  dy * sin_az * cos_ay +   //
                  dz * sin_ay + origin->x; //

    double newy = dx * sin_ax * sin_ay * cos_az + //
                  dx * sin_az * cos_ax -          //
                  dy * sin_ax * sin_ay * sin_az + //
                  dy * cos_ax * cos_az -          //
                  dz * sin_ax * cos_ay +          //
                  origin->y;

    double newz = dx * sin_ax * sin_az -          //
                  dx * sin_ay * cos_ax * cos_az + //
                  dy * sin_ax * cos_az +          //
                  dy * sin_ay * sin_az * cos_ax + //
                  dz * cos_ax * cos_ay +          //
                  origin->z;

    pt->x = newx;
    pt->y = newy;
    pt->z = newz;

    return 0;
}

int transform_point_shift(point_t pt, const point_t shifts)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (shifts == nullptr)
        return TRANSFORM_NO_DATA;

    pt->x += shifts->x;
    pt->y += shifts->y;
    pt->z += shifts->z;

    return 0;
}

static int pt_arr_apply_scale(pt_arr_t pt_arr, const point_t origin, const point_t coeffs)
{
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (coeffs == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = 0;

    for (size_t i = 0; !rc && i < pt_arr.len; ++i)
        rc = transform_point_scale(pt_arr.arr[i], origin, coeffs);

    return rc;
}

int model_apply_scale(model_t gr, const point_t origin, const point_t coeffs)
{
    if (gr == nullptr)
        return TRANSFORM_NO_MODEL;
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (coeffs == nullptr)
        return TRANSFORM_NO_DATA;

    return pt_arr_apply_scale(gr->pt_arr, origin, coeffs);
}

static int pt_arr_apply_rotate(pt_arr_t pt_arr, const point_t origin, const point_t angles)
{
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (angles == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = 0;

    for (size_t i = 0; !rc && i < pt_arr.len; ++i)
        rc = transform_point_rotate(pt_arr.arr[i], origin, angles);

    return rc;
}

int model_apply_rotate(model_t gr, const point_t origin, const point_t angles)
{
    if (gr == nullptr)
        return TRANSFORM_NO_MODEL;
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (angles == nullptr)
        return TRANSFORM_NO_DATA;

    return pt_arr_apply_rotate(gr->pt_arr, origin, angles);
}

static int pt_arr_apply_shift(pt_arr_t pt_arr, const point_t shifts)
{
    if (shifts == nullptr)
        return TRANSFORM_NO_DATA;
    int rc = 0;

    for (size_t i = 0; !rc && i < pt_arr.len; ++i)
        rc = transform_point_shift(pt_arr.arr[i], shifts);

    return rc;
}

int model_apply_shift(model_t gr, const point_t shifts)
{
    if (gr == nullptr)
        return TRANSFORM_NO_MODEL;
    if (shifts == nullptr)
        return TRANSFORM_NO_DATA;

    return pt_arr_apply_shift(gr->pt_arr, shifts);
}

size_t model_get_point_index(pt_arr_t pt_arr, point_t pt)
{
    if (pt_arr.arr == nullptr)
        return SIZE_MAX;
    if (pt == nullptr)
        return SIZE_MAX;

    size_t i = 0;
    for (i = 0; i < pt_arr.len && pt != pt_arr.arr[i]; ++i)
        ;

    if (pt != pt_arr.arr[i])
        return SIZE_MAX;

    return i;
}
