#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include <memory.h>
#include <stdio.h>

#include "model_error.hpp"

#include "edge.hpp"
#include "edge_arr.hpp"
#include "point.hpp"
#include "point_arr.hpp"

#define OUT
#define VAR

struct model {
  pt_arr_t pt_arr;
  con_arr_t con_arr;
};
typedef struct model *model_t;

model_t alloc_model();

void destroy_model(model_t &model);

int model_apply_scale(model_t model, const point_t origin,
                      const point_t coeffs);
int model_apply_rotate(model_t model, const point_t origin,
                       const point_t angles);
int model_apply_shift(model_t model, const point_t shifts);

int model_get_point_index(OUT size_t &dst, const pt_arr_t &pt_arr, point_t pt);

#endif // MODEL_H
