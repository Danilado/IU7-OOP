#ifndef EDGE_H
#define EDGE_H

#include "model_error.hpp"
#include "point.hpp"
#include <cstdlib>

struct connection {
  point_t p1;
  point_t p2;
};
typedef struct connection *connection_t;

connection_t alloc_connection();
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t &con);

#endif