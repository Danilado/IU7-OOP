#ifndef MY_MODEL_IO_H
#define MY_MODEL_IO_H

#include "my_error.h"
#include "my_model.h"

int create_model_from_file(model_t &gr, const char *filename);
int write_model_to_file(const model_t gr, const char *filename);

#endif
