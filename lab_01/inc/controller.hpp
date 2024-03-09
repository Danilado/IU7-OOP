#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model_error.hpp"
#include "model.hpp"

#include "draw_handlers.hpp"
#include "io_handlers.hpp"
#include "transform_handlers.hpp"

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
