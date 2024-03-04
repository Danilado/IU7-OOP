#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_error.h"

typedef struct point *point_t;
point_t create_point(double x, double y, double z);
void destroy_point(point_t &pt);

double point_get_x(const point_t pt);
double point_get_y(const point_t pt);
double point_get_z(const point_t pt);

int transform_point_scale(point_t pt, const point_t origin, const point_t coeffs);
int transform_point_rotate(point_t pt, const point_t origin, const point_t angles);
int transform_point_shift(point_t pt, const point_t shifts);

// В соединениях лежит point_t, то есть указатель =>
// когда меняем точки, соединение будет меняться само
typedef struct connection *connection_t;
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t &con);

point_t connection_get_p1(const connection_t con);
point_t connection_get_p2(const connection_t con);

typedef struct
{
    size_t len;
    point_t *arr;
} pt_arr_t;
typedef struct
{
    size_t len;
    connection_t *arr;
} con_arr_t;

typedef struct graph *graph_t;
graph_t create_graph(pt_arr_t pt_arr, con_arr_t con_arr);
void destroy_graph(graph_t &gr);

size_t graph_get_pt_len(const graph_t gr);
size_t graph_get_con_len(const graph_t gr);

point_t graph_get_point(const graph_t gr, size_t index);
connection_t graph_get_connection(const graph_t gr, size_t index);

int graph_apply_scale(graph_t gr, const point_t origin, const point_t coeffs);
int graph_apply_rotate(graph_t gr, const point_t origin, const point_t angles);
int graph_apply_shift(graph_t gr, const point_t shifts);

size_t graph_get_point_index(graph_t gr, point_t pt);

#endif // MY_GRAPH_H
