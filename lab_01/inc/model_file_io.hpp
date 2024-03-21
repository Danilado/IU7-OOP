#ifndef MODEL_IO_H
#define MODEL_IO_H

#include "model.hpp"
#include "model_error.hpp"

int create_model_from_file(model_t &model, const char *filename);
int write_model_to_file(const model_t model, const char *filename);

#endif
