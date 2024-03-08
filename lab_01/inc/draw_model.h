#ifndef DRAW_MODEL_H
#define DRAW_MODEL_H

#include "my_model.h"

#include <QColor>
#include <QPainter>

typedef struct {
  QColor linecolor;
  QColor pointcolor;
} colors_t;

typedef struct {
  double offset_x;
  double offset_y;
} offset_t;

typedef struct {
  colors_t colors;
  offset_t offset;
} draw_params_t;

int draw_model(model_t gr, QPainter *ctx, draw_params_t params);

int draw_connections(model_t gr, QPainter *ctx, draw_params_t params);

int draw_points(model_t gr, QPainter *ctx, draw_params_t params);

#endif
