#include "point_arr.hpp"

static void clear_points_from_arr(point_t *&data, size_t len) {
  for (size_t i = 0; i < len; ++i)
    destroy_point(data[i]);
}

void destroy_pt_arr(pt_arr_t arr) {
  if (arr.data != nullptr)
    clear_points_from_arr(arr.data, arr.len);

  free(arr.data);
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

int pt_arr_apply_shift(pt_arr_t &pt_arr, const point_t shifts) {
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;
  int rc = ALL_OK;
  rc = wrap_apply_shift(pt_arr.data, pt_arr.len, shifts);
  return rc;
}

static int wrap_apply_scale(point_t *&data, size_t len,
                            const tr_scale_data_t &s_data) {
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

int pt_arr_apply_scale(pt_arr_t &pt_arr, const point_t origin,
                       const point_t coeffs) {
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  tr_scale_data_t data = form_tr_scale_data(origin, coeffs);
  int rc = wrap_apply_scale(pt_arr.data, pt_arr.len, data);
  return rc;
}

static int wrap_apply_rotate(point_t *&data, size_t len,
                             const tr_rot_data_t &r_data) {
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

int pt_arr_apply_rotate(pt_arr_t &pt_arr, const point_t origin,
                        const point_t angles) {
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  tr_rot_data_t data = form_rot_data(origin, angles);
  int rc = wrap_apply_rotate(pt_arr.data, pt_arr.len, data);
  return rc;
}
