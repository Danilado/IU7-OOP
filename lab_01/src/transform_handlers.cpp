#include "transform_handlers.hpp"

int handle_scale(model_t model, transform_data_t &data) {
  if (model == nullptr)
    return NO_MODEL;

  if (data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_scale(model, data.origin, data.values);

  return rc;
}

int handle_rotate(model_t model, transform_data_t &data) {
  if (model == nullptr)
    return NO_MODEL;

  if (data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_rotate(model, data.origin, data.values);

  return rc;
}

int handle_shift(model_t model, transform_data_t &data) {
  if (model == nullptr)
    return NO_MODEL;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_shift(model, data.values);

  return rc;
}
