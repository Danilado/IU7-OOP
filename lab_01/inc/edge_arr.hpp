#ifndef EDGE_ARR_H
#define EDGE_ARR_H

#include "edge.hpp"
#include "model_error.hpp"

typedef struct {
  size_t len;
  connection_t *data;
} con_arr_t;
void destroy_con_arr(con_arr_t arr);

#endif