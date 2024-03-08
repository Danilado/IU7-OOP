#ifndef IO_HANDLERS_H
#define IO_HANDLERS_H

#include "model_error.h"
#include "model.h"

typedef struct
{
  const char *filename;
} io_data_t;

int handle_load(model_t &gr, io_data_t data);
int handle_save(const model_t gr, io_data_t data);

#endif
