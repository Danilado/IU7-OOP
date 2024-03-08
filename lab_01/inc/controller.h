#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model_error.h"
#include "model.h"

#include "draw_handlers.h"
#include "io_handlers.h"
#include "transform_handlers.h"

typedef enum
{
  EXIT,
  LOAD,
  SAVE,
  SCALE,
  ROTATE,
  SHIFT,
  DRAW,
} option_t;

typedef struct
{
  option_t option;
  union
  {
    io_data_t io_data;
    transform_data_t t_data;
    draw_data_t d_data;
    int *empty_data;
  };
} request_t;

int handle(request_t req);

#endif // CONTROLLER_H
