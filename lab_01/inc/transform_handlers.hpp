#ifndef TRANSFORM_HANDLERS_H
#define TRANSFORM_HANDLERS_H

#include "model.hpp"
#include "model_error.hpp"

typedef struct {
  point_t origin;
  point_t values;
} transform_data_t;

int handle_scale(model_t model, transform_data_t &data);
int handle_rotate(model_t model, transform_data_t &data);
int handle_shift(model_t model, transform_data_t &data);

#endif
