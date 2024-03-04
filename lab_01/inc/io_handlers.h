#ifndef IO_HANDLERS_H
#define IO_HANDLERS_H

#include "my_graph.h"
#include "my_error.h"

typedef struct
{
    const char *filename;
} io_data_t;

int handle_load(io_data_t data, graph_t &gr);
int handle_save(io_data_t data, const graph_t gr);

#endif
