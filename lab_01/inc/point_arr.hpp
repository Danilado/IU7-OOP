#ifndef POINT_ARR_H
#define POINT_ARR_H

#include "model_error.hpp"
#include "point.hpp"

typedef struct {
  size_t len;
  point_t *data;
} pt_arr_t;
void destroy_pt_arr(pt_arr_t arr);

int pt_arr_apply_shift(pt_arr_t &pt_arr, const point_t shifts);
int pt_arr_apply_scale(pt_arr_t &pt_arr, const point_t origin,
                       const point_t coeffs);
int pt_arr_apply_rotate(pt_arr_t &pt_arr, const point_t origin,
                        const point_t angles);

#endif