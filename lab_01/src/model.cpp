#include "model.hpp"
#include <cmath>
#include <stdint.h>

model_t alloc_model() {
  model_t res = (model_t)calloc(1, sizeof(struct model));
  return res;
}

static void destroy_model_fields(model_t &model) {
  if (model == nullptr)
    return;

  destroy_pt_arr(model->pt_arr);
  destroy_con_arr(model->con_arr);
}

void destroy_model(model_t &model) {
  if (model == nullptr)
    return;

  destroy_model_fields(model);

  free(model);
  model = nullptr;
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

int model_get_point_index(OUT size_t &dst, const pt_arr_t &pt_arr, point_t pt) {
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;
  if (pt == nullptr)
    return MODEL_BAD_POINT;

  dst = wrap_find_index(pt_arr.data, pt_arr.len, pt);
  if (dst >= pt_arr.len)
    return PT_NOT_FOUND;
  return ALL_OK;
}
