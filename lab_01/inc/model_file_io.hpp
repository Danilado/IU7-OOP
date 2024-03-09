#ifndef MODEL_IO_H
#define MODEL_IO_H

#include "model_error.hpp"
#include "model.hpp"

int create_model_from_file(model_t &gr, const char *filename);
int write_model_to_file(const model_t gr, const char *filename);

#endif
