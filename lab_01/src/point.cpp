#include <cmath>
#include <point.hpp>

tr_rot_data_t form_rot_data(const point_t origin, const point_t angles) {
  return tr_rot_data_t{origin, angles};
}

tr_scale_data_t form_tr_scale_data(const point_t origin, const point_t coeffs) {
  return tr_scale_data_t{origin, coeffs};
}

point_t alloc_point() {
  point_t res = (point_t)calloc(1, sizeof(struct point));
  return res;
}

point_t create_point(double x, double y, double z) {
  point_t res = alloc_point();
  if (res != nullptr) {
    res->x = x;
    res->y = y;
    res->z = z;
  }

  return res;
}

void destroy_point(point_t &pt) {
  free(pt);
  pt = nullptr;
}

static int point_origin_shift(point_t pt, const point_t origin,
                              bool backwards = false) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_DATA;

  int mul = 1;
  if (backwards)
    mul = -1;

  pt->x += origin->x * mul;
  pt->y += origin->y * mul;
  pt->z += origin->z * mul;

  return ALL_OK;
}

int transform_point_scale(point_t pt, const point_t origin,
                          const point_t coeffs) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  pt->x = (pt->x - origin->x) * coeffs->x + origin->x;
  pt->y = (pt->y - origin->y) * coeffs->y + origin->y;
  pt->z = (pt->z - origin->z) * coeffs->z + origin->z;

  return ALL_OK;
}

static int transform_point_rotate_x(point_t pt, double angle) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;

  double newy, newz;
  double angle_sin = sin(angle);
  double angle_cos = cos(angle);

  newy = pt->y * angle_cos - pt->z * angle_sin;
  newz = pt->y * angle_sin + pt->z * angle_cos;

  pt->y = newy;
  pt->z = newz;

  return ALL_OK;
}

static int transform_point_rotate_y(point_t pt, double angle) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;

  double newx, newz;
  double angle_sin = sin(angle);
  double angle_cos = cos(angle);

  newx = pt->x * angle_cos + pt->z * angle_sin;
  newz = -pt->x * angle_sin + pt->z * angle_cos;

  pt->x = newx;
  pt->z = newz;

  return ALL_OK;
}

static int transform_point_rotate_z(point_t pt, double angle) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;

  double newx, newy;
  double angle_sin = sin(angle);
  double angle_cos = cos(angle);

  newx = pt->x * angle_cos - pt->y * angle_sin;
  newy = pt->x * angle_sin + pt->y * angle_cos;

  pt->x = newx;
  pt->y = newy;

  return ALL_OK;
}

static int point_rotate_all(point_t pt, const point_t angles) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
  int rc = transform_point_rotate_x(pt, angles->x);
  if (!rc) {
    rc = transform_point_rotate_y(pt, angles->y);
    if (!rc)
      rc = transform_point_rotate_z(pt, angles->z);
  }

  return rc;
}

int transform_point_rotate(point_t pt, const point_t origin,
                           const point_t angles) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = point_origin_shift(pt, origin, true);
  if (!rc) {
    rc = point_rotate_all(pt, angles);
    if (!rc)
      rc = point_origin_shift(pt, origin, false);
  }

  return rc;
}

int transform_point_shift(point_t pt, const point_t shifts) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;

  point_origin_shift(pt, shifts);

  return ALL_OK;
}
