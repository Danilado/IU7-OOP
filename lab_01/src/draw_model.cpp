#include "draw_model.hpp"
#include "model_converters.hpp"

typedef struct {
  offset_t offset;
  canvas_data_t canv_data;
} draw_loop_data_t;

draw_loop_data_t get_loop_data(offset_t &offset, canvas_data_t &canv_data) {
  return draw_loop_data_t{offset, canv_data};
}

int draw_model(model_t model, canvas_data_t &canv_data, draw_params_t &params) {
  if (model == nullptr)
    return DRAW_NO_MODEL;

  int rc = draw_connections(model->con_arr, canv_data, params);
  if (!rc)
    rc = draw_points(model->pt_arr, canv_data, params);

  return rc;
}

static int setQTPenColor(QPainter *p, QColor color) {
  if (p == nullptr)
    return DRAW_NO_SCENE;
  p->setPen(color);
  return ALL_OK;
}

static int apply_linecolor(canvas_data_t &canv_data, colors_t &color_params) {
  return setQTPenColor(canv_data.p, color_params.linecolor);
}

static int drawQTLine(connection_t con, offset_t &offset, QPainter *p) {
  if (p == nullptr)
    return DRAW_NO_CONTEXT;
  int rc = ALL_OK;

  QLineF *tmpline = connection_to_QLineF(con, offset);
  if (tmpline == nullptr)
    rc = MODEL_BAD_CONNECTION;

  if (!rc) {
    p->drawLine(*tmpline);
    delete tmpline;
  }

  return rc;
}

static int draw_line(connection_t con, offset_t &offset,
                     canvas_data_t &canv_data) {
  if (con == nullptr)
    return MODEL_BAD_CONNECTION;

  return drawQTLine(con, offset, canv_data.p);
}

static int draw_con_arr(connection_t *data, size_t len,
                        draw_loop_data_t &dl_data) {
  if (data == nullptr)
    return MODEL_BAD_CONNECTION;

  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = draw_line(data[i], dl_data.offset, dl_data.canv_data);

  return rc;
}

int draw_connections(con_arr_t con_arr, canvas_data_t &canv_data,
                     draw_params_t &params) {
  if (con_arr.data == nullptr)
    return NO_CON_ARR;

  int rc = apply_linecolor(canv_data, params.colors);
  if (!rc) {
    draw_loop_data_t dl_data = get_loop_data(params.offset, canv_data);
    rc = draw_con_arr(con_arr.data, con_arr.len, dl_data);
  }

  return rc;
}

static int setQTBrushColor(QPainter *p, QColor color) {
  if (p == nullptr)
    return DRAW_NO_SCENE;
  p->setBrush(color);
  return ALL_OK;
}

static int apply_pointcolor(canvas_data_t &canv_data, colors_t &color_params) {
  return setQTBrushColor(canv_data.p, color_params.linecolor);
}

static int drawQTPoint(point_t pt, offset_t &offset, QPainter *p) {
  if (p == nullptr)
    return DRAW_NO_CONTEXT;
  if (pt == nullptr)
    return MODEL_BAD_POINT;

  int rc = ALL_OK;
  QPointF *tmppoint = point_to_QPointF(pt, offset);
  if (tmppoint == nullptr)
    rc = MODEL_BAD_POINT;

  if (!rc) {
    p->drawPoint(*tmppoint);
    delete tmppoint;
  }

  return rc;
}

static int draw_point(point_t pt, offset_t &offset, canvas_data_t &canv_data) {
  if (pt == nullptr)
    return MODEL_BAD_POINT;

  return drawQTPoint(pt, offset, canv_data.p);
}

static int draw_pt_arr(point_t *data, size_t len, draw_loop_data_t &dl_data) {
  if (data == nullptr)
    return MODEL_BAD_POINT;

  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = draw_point(data[i], dl_data.offset, dl_data.canv_data);

  return rc;
}

int draw_points(pt_arr_t pt_arr, canvas_data_t &canv_data,
                draw_params_t &params) {
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;

  int rc = apply_pointcolor(canv_data, params.colors);
  if (!rc) {
    draw_loop_data_t dl_data = get_loop_data(params.offset, canv_data);
    rc = draw_pt_arr(pt_arr.data, pt_arr.len, dl_data);
  }

  return rc;
}
