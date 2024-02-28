#ifndef MY_GRAPH_FUNCS_H
#define MY_GRAPH_FUNCS_H

#include "my_graph.h"

#include <QColor>
#include <QLineF>
#include <QPainter>
#include <QPointF>
#include <QString>

QPointF *point_to_QPointF(point_t pt, double offset_x, double offset_y);
QLineF *connection_to_QLineF(connection_t con, double offset_x,
                             double offset_y);

void write_graph_to_file(graph_t gr, QString filename);

void draw_graph(graph_t gr, QPainter *ctx, QColor linecolor, QColor pointcolor,
                double offset_x, double offset_y);

void draw_connections(graph_t gr, QPainter *ctx, QColor color, double offset_x,
                      double offset_y);
void draw_points(graph_t gr, QPainter *ctx, QColor color, double offset_x,
                 double offset_y);

graph_t create_graph_from_file(QString filename);

#endif