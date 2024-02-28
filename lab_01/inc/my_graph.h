#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point *point_t;
point_t create_point(double x, double y, double z);
void destroy_point(point_t *pt);

double point_get_x(const point_t pt);
double point_get_y(const point_t pt);
double point_get_z(const point_t pt);

void transform_point_scale(point_t pt, const point_t origin, double kx,
                           double ky, double kz);
void transform_point_rotate(point_t pt, const point_t origin, double ax,
                            double ay, double az);
void transform_point_shift(point_t pt, double dx, double dy, double dz);

// В соединениях лежит point_t, то есть указатель =>
// когда меняем точки, соединение будет меняться само
typedef struct connection *connection_t;
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t *con);

point_t connection_get_p1(const connection_t con);
point_t connection_get_p2(const connection_t con);

typedef struct graph *graph_t;
graph_t create_graph(size_t points_len, point_t *points, size_t connections_len,
                     connection_t *connections);
void destroy_graph(graph_t *gr);

size_t graph_get_pt_len(const graph_t gr);
size_t graph_get_con_len(const graph_t gr);

point_t graph_get_point(const graph_t gr, size_t index);
connection_t graph_get_connection(const graph_t gr, size_t index);

void graph_apply_scale(graph_t gr, const point_t origin, double kx, double ky,
                       double kz);
void graph_apply_rotate(graph_t gr, const point_t origin, double ax, double ay,
                        double az);
void graph_apply_shift(graph_t gr, double dx, double dy, double dz);

size_t graph_get_point_index(graph_t gr, point_t pt);

#endif // MY_GRAPH_H
