#include "edge_arr.hpp"

static void clear_cons_from_arr(connection_t *&data, size_t len) {
  for (size_t i = 0; i < len; ++i)
    destroy_connection(data[i]);
}

void destroy_con_arr(con_arr_t arr) {
  if (arr.data != nullptr)
    clear_cons_from_arr(arr.data, arr.len);

  free(arr.data);
}
