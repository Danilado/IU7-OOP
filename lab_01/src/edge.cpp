#include "edge.hpp"

connection_t alloc_connection() {
  connection_t res = (connection_t)calloc(1, sizeof(struct connection));
  return res;
}

connection_t create_connection(point_t p1, point_t p2) {
  connection_t res = alloc_connection();
  if (res != nullptr) {
    res->p1 = p1;
    res->p2 = p2;
  }

  return res;
}

void destroy_connection(connection_t &con) {
  free(con);
  con = nullptr;
}
