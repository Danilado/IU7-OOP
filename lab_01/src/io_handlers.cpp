#include "io_handlers.h"

#include "model_file_io.h"

int handle_load(model_t &gr, io_data_t data)
{
  int rc = 0;
  model_t new_model = alloc_model();
  if (new_model == nullptr)
    return NO_MEMORY;

  if (!rc)
  {
    rc = create_model_from_file(new_model, data.filename);
    if (!rc)
    {
      if (gr != nullptr)
        destroy_model(gr);

      gr = new_model;
    }
  }

  if (rc)
    destroy_model(new_model);

  return rc;
}

int handle_save(const model_t gr, io_data_t data)
{
  return write_model_to_file(gr, data.filename);
}
