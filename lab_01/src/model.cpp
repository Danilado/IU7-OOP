#include "model.hpp"
#include <cmath>
#include <stdint.h>

static void clear_points_from_arr(point_t *&data, size_t len) {
  for (size_t i = 0; i < len; ++i)
    destroy_point(data[i]);
}

void destroy_pt_arr(pt_arr_t arr) {
  if (arr.data != nullptr)
    clear_points_from_arr(arr.data, arr.len);

  free(arr.data);
}

static void clear_cons_from_arr(connection_t *&data, size_t len) {
  for (size_t i = 0; i < len; ++i)
    destroy_connection(data[i]);
}

void destroy_con_arr(con_arr_t arr) {
  if (arr.data != nullptr)
    clear_cons_from_arr(arr.data, arr.len);

  free(arr.data);
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

connection_t alloc_connection() {
  connection_t res = (connection_t)calloc(1, sizeof(struct connection));
  return res;
}

connection_t create_connection(point_t p1, point_t p2) {
  connection_t res = alloc_connection();
  if (res != nullptr) {
    res->p1 = p1;
    res->p2 = p2;
  }

  return res;
}

void destroy_connection(connection_t &con) {
  free(con);
  con = nullptr;
}

model_t alloc_model() {
  model_t res = (model_t)calloc(1, sizeof(struct model));
  return res;
}

model_t create_model(pt_arr_t pt_arr, con_arr_t con_arr) {
  model_t res = alloc_model();
  if (res != nullptr) {
    res->pt_arr = pt_arr;
    res->con_arr = con_arr;
  }

  return res;
}

void destroy_model(model_t &model) {
  if (model == nullptr)
    return;

  destroy_pt_arr(model->pt_arr);
  destroy_con_arr(model->con_arr);

  free(model);
  model = nullptr;
}

static int point_origin_shift(point_t pt, const point_t origin,
                              bool backwards = false) {
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_DATA;

  pt->x += origin->x * (-1 * backwards);
  pt->y += origin->y * (-1 * backwards);
  pt->z += origin->z * (-1 * backwards);

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

typedef struct {
  const point_t origin;
  const point_t coeffs;
} tr_scale_data_t;

static int wrap_apply_scale(point_t *&data, size_t len,
                            const tr_scale_data_t s_data) {
  if (data == nullptr)
    return TRANSFORM_NO_POINT;
  if (s_data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (s_data.coeffs == nullptr)
    return TRANSFORM_NO_DATA;
  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = transform_point_scale(data[i], s_data.origin, s_data.coeffs);
  return rc;
}

tr_scale_data_t form_tr_scale_data(const point_t origin, const point_t coeffs) {
  return tr_scale_data_t{origin, coeffs};
}

static int pt_arr_apply_scale(pt_arr_t pt_arr, const point_t origin,
                              const point_t coeffs) {
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  tr_scale_data_t data = form_tr_scale_data(origin, coeffs);
  int rc = wrap_apply_scale(pt_arr.data, pt_arr.len, data);
  return rc;
}

int model_apply_scale(model_t model, const point_t origin,
                      const point_t coeffs) {
  if (model == nullptr)
    return TRANSFORM_NO_MODEL;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  return pt_arr_apply_scale(model->pt_arr, origin, coeffs);
}

typedef struct {
  const point_t origin;
  const point_t angles;
} tr_rot_data_t;

static int wrap_apply_rotate(point_t *&data, size_t len,
                             const tr_rot_data_t r_data) {
  if (data == nullptr)
    return TRANSFORM_NO_POINT;
  if (r_data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (r_data.angles == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = transform_point_rotate(data[i], r_data.origin, r_data.angles);
  return rc;
}

tr_rot_data_t form_rot_data(const point_t origin, const point_t angles) {
  return tr_rot_data_t{origin, angles};
}

static int pt_arr_apply_rotate(pt_arr_t pt_arr, const point_t origin,
                               const point_t angles) {
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  tr_rot_data_t data = form_rot_data(origin, angles);
  int rc = wrap_apply_rotate(pt_arr.data, pt_arr.len, data);
  return rc;
}

int model_apply_rotate(model_t model, const point_t origin,
                       const point_t angles) {
  if (model == nullptr)
    return TRANSFORM_NO_MODEL;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  return pt_arr_apply_rotate(model->pt_arr, origin, angles);
}

static int wrap_apply_shift(point_t *&data, size_t len, const point_t shifts) {
  if (data == nullptr)
    return TRANSFORM_NO_POINT;
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;
  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = transform_point_shift(data[i], shifts);
  return rc;
}

static int pt_arr_apply_shift(pt_arr_t pt_arr, const point_t shifts) {
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;
  int rc = ALL_OK;
  rc = wrap_apply_shift(pt_arr.data, pt_arr.len, shifts);
  return rc;
}

int model_apply_shift(model_t model, const point_t shifts) {
  if (model == nullptr)
    return TRANSFORM_NO_MODEL;
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;

  return pt_arr_apply_shift(model->pt_arr, shifts);
}

static size_t wrap_find_index(point_t *data, size_t len, point_t pt) {
  if (data == nullptr)
    return len;
  if (pt == nullptr)
    return len;

  size_t i = 0;
  for (i = 0; i < len && pt != data[i]; ++i)
    ;

  return i;
}

int model_get_point_index(OUT size_t &dst, const pt_arr_t pt_arr, point_t pt) {
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;
  if (pt == nullptr)
    return MODEL_BAD_POINT;

  dst = wrap_find_index(pt_arr.data, pt_arr.len, pt);
  if (dst >= pt_arr.len)
    return PT_NOT_FOUND;
  return ALL_OK;
}
