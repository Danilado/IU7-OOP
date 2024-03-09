#include "model.hpp"
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

static int point_origin_shift(point_t pt, const point_t origin, bool backwards = false)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (origin == nullptr)
        return TRANSFORM_NO_DATA;

    pt->x += origin->x * (-1 * backwards);
    pt->y += origin->y * (-1 * backwards);
    pt->z += origin->z * (-1 * backwards);

    return 0;
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

static int transform_point_rotate_x(point_t pt, double angle)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;

    double newy, newz;
    double angle_sin = sin(angle);
    double angle_cos = cos(angle);

    newy = pt->y * angle_cos - pt->z * angle_sin;
    newz = pt->y * angle_sin + pt->z * angle_cos;

    pt->y = newy;
    pt->z = newz;

    return 0;
}

static int transform_point_rotate_y(point_t pt, double angle)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;

    double newx, newz;
    double angle_sin = sin(angle);
    double angle_cos = cos(angle);

    newx = pt->x * angle_cos + pt->z * angle_sin;
    newz = -pt->x * angle_sin + pt->z * angle_cos;

    pt->x = newx;
    pt->z = newz;

    return 0;
}

static int transform_point_rotate_z(point_t pt, double angle)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;

    double newx, newy;
    double angle_sin = sin(angle);
    double angle_cos = cos(angle);

    newx = pt->x * angle_cos - pt->y * angle_sin;
    newy = pt->x * angle_sin + pt->y * angle_cos;

    pt->x = newx;
    pt->y = newy;

    return 0;
}

static int point_rotate_all(point_t pt, const point_t angles)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (angles == nullptr)
        return TRANSFORM_NO_DATA;

    // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
    int rc = transform_point_rotate_x(pt, angles->x);
    if (!rc)
    {
        rc = transform_point_rotate_y(pt, angles->y);
        if (!rc)
            rc = transform_point_rotate_z(pt, angles->z);
    }

    return rc;
}

int transform_point_rotate(point_t pt, const point_t origin, const point_t angles)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (origin == nullptr)
        return TRANSFORM_NO_ORIGIN;
    if (angles == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = point_origin_shift(pt, origin, true);
    if (!rc)
    {
        rc = point_rotate_all(pt, angles);
        if (!rc)
            rc = point_origin_shift(pt, origin, false);
    }

    return rc;
}

int transform_point_shift(point_t pt, const point_t shifts)
{
    if (pt == nullptr)
        return TRANSFORM_NO_POINT;
    if (shifts == nullptr)
        return TRANSFORM_NO_DATA;

    point_origin_shift(pt, shifts);

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
