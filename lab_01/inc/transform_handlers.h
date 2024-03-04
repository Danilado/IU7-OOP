#ifndef TRANSFORM_HANDLERS_H
#define TRANSFORM_HANDLERS_H

#include "my_graph.h"
#include "my_error.h"

typedef struct
{
    point_t origin;
    point_t values;
} transform_data_t;

int handle_scale(transform_data_t data, graph_t gr);
int handle_rotate(transform_data_t data, graph_t gr);
int handle_shift(transform_data_t data, graph_t gr);

#endif
