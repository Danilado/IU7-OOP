#include "transform_handlers.h"

int handle_scale(model_t gr, transform_data_t data)
{
  if (gr == nullptr)
    return NO_MODEL;

  if (data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_scale(gr, data.origin, data.values);

  return rc;
}

int handle_rotate(model_t gr, transform_data_t data)
{
  if (gr == nullptr)
    return NO_MODEL;

  if (data.origin == nullptr)
    return TRANSFORM_NO_ORIGIN;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_rotate(gr, data.origin, data.values);

  return rc;
}

int handle_shift(model_t gr, transform_data_t data)
{
  if (gr == nullptr)
    return NO_MODEL;

  if (data.values == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = model_apply_shift(gr, data.values);

  return rc;
}
