#include "io_handlers.h"

#include "my_model_file_io.h"

int handle_load(model_t &gr, io_data_t data) {
  model_t new_model = nullptr;
  int rc = create_model_from_file(new_model, data.filename);

  if (rc)
    return rc;

  if (gr != nullptr)
    destroy_model(gr);

  gr = new_model;

  return 0;
}

int handle_save(const model_t gr, io_data_t data) {
  return write_model_to_file(gr, data.filename);
}
