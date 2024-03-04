#ifndef MY_GRAPH_IO_H
#define MY_GRAPH_IO_H

#include "my_graph.h"
#include "my_error.h"

int create_graph_from_file(graph_t &gr, const char *filename);
int write_graph_to_file(const graph_t gr, const char *filename);

#endif
