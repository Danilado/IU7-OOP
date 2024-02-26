#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <QColor>
#include <QLineF>
#include <QPainter>
#include <QPointF>
#include <QString>
#include <cmath>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point *point_t;
point_t create_point(double x, double y, double z);
void destroy_point(point_t *pt);

void transform_point_scale(point_t pt, const point_t origin, double kx, double ky, double kz);
void transform_point_rotate(point_t pt, const point_t origin, double ax, double ay, double az);
void transform_point_shift(point_t pt, double dx, double dy, double dz);

QPointF *point_to_QPointF(point_t pt, double offset_x, double offset_y);

// В соединениях лежит point_t, то есть указатель =>
// когда меняем точки, соединение будет меняться само
typedef struct connection *connection_t;
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t *con);

QLineF *connection_to_QLineF(connection_t con, double offset_x, double offset_y);

typedef struct graph *graph_t;
graph_t create_graph(size_t points_len,
                     point_t *points,
                     size_t connections_len,
                     connection_t *connections);
void destroy_graph(graph_t *gr);

graph_t create_graph_from_file(QString filename);
void write_graph_to_file(graph_t gr, QString filename);

void draw_graph(graph_t gr,
                QPainter *ctx,
                QColor linecolor,
                QColor pointcolor,
                double offset_x,
                double offset_y);

void draw_connections(graph_t gr, QPainter *ctx, QColor color, double offset_x, double offset_y);
void draw_points(graph_t gr, QPainter *ctx, QColor color, double offset_x, double offset_y);

void graph_apply_scale(graph_t gr, const point_t origin, double kx, double ky, double kz);
void graph_apply_rotate(graph_t gr, const point_t origin, double ax, double ay, double az);
void graph_apply_shift(graph_t gr, double dx, double dy, double dz);

#endif // MY_GRAPH_H
