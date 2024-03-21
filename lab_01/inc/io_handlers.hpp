#ifndef IO_HANDLERS_H
#define IO_HANDLERS_H

#include "model.hpp"
#include "model_error.hpp"

typedef struct {
  const char *filename;
} io_data_t;

int handle_load(model_t &model, io_data_t data);
int handle_save(const model_t model, io_data_t data);

#endif
