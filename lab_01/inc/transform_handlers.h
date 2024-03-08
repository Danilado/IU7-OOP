#ifndef TRANSFORM_HANDLERS_H
#define TRANSFORM_HANDLERS_H

#include "model_error.h"
#include "model.h"

typedef struct
{
  point_t origin;
  point_t values;
} transform_data_t;

int handle_scale(model_t gr, transform_data_t data);
int handle_rotate(model_t gr, transform_data_t data);
int handle_shift(model_t gr, transform_data_t data);

#endif
