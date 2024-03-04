#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H

#include "my_graph.h"

#include <QPainter>
#include <QColor>

typedef struct
{
    QColor linecolor;
    QColor pointcolor;
} colors_t;

typedef struct
{
    double offset_x;
    double offset_y;
} offset_t;

typedef struct
{
    colors_t colors;
    offset_t offset;
} draw_params_t;

int draw_graph(graph_t gr, QPainter *ctx, draw_params_t params);

int draw_connections(graph_t gr, QPainter *ctx, draw_params_t params);

int draw_points(graph_t gr, QPainter *ctx, draw_params_t params);

#endif
