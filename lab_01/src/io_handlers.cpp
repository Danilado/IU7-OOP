#include "io_handlers.hpp"

#include "model_file_io.hpp"

int handle_load(model_t &model, io_data_t &data) {
  int rc = ALL_OK;
  model_t new_model = nullptr;

  rc = create_model_from_file(new_model, data.filename);
  if (!rc) {
    if (model != nullptr)
      destroy_model(model);

    model = new_model;
  }

  return rc;
}

int handle_save(const model_t model, io_data_t &data) {
  return write_model_to_file(model, data.filename);
}
