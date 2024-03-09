#include "draw_model.hpp"
#include "model_converters.hpp"

int draw_model(model_t gr, QPainter *ctx, draw_params_t params)
{
  if (gr == nullptr)
    return DRAW_NO_MODEL;

  if (ctx == nullptr)
    return DRAW_NO_CONTEXT;

  int rc = 0;

  rc = draw_connections(gr->con_arr, ctx, params);
  if (!rc)
    rc = draw_points(gr->pt_arr, ctx, params);

  return rc;
}

int draw_connections(con_arr_t con_arr, QPainter *ctx, draw_params_t params)
{
  if (con_arr.arr == nullptr)
    return NO_CON_ARR;
  if (ctx == nullptr)
    return DRAW_NO_CONTEXT;

  int rc = 0;

  ctx->setPen(params.colors.linecolor);

  for (size_t i = 0; !rc && i < con_arr.len; ++i)
  {
    connection_t tmp = con_arr.arr[i];
    if (tmp == nullptr)
      rc = MODEL_BAD_CONNECTION;

    if (!rc)
    {
      QLineF *tmpline = connection_to_QLineF(tmp, params.offset);
      if (tmpline == nullptr)
        rc = MODEL_BAD_CONNECTION;

      if (!rc)
      {
        ctx->drawLine(*tmpline);
        delete tmpline;
      }
    }
  }

  return rc;
}

int draw_points(pt_arr_t pt_arr, QPainter *ctx, draw_params_t params)
{
  if (pt_arr.arr == nullptr)
    return NO_PT_ARR;
  if (ctx == nullptr)
    return DRAW_NO_CONTEXT;

  int rc = 0;

  ctx->setBrush(params.colors.pointcolor);

  for (size_t i = 0; !rc && i < pt_arr.len; ++i)
  {
    point_t tmp = pt_arr.arr[i];
    if (tmp == nullptr)
      rc = MODEL_BAD_POINT;

    if (!rc)
    {
      QPointF *tmppoint = point_to_QPointF(tmp, params.offset);
      if (tmppoint == nullptr)
        rc = MODEL_BAD_POINT;

      if (!rc)
      {
        ctx->drawPoint(*tmppoint);
        delete tmppoint;
      }
    }
  }

  return rc;
}
