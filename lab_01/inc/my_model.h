#ifndef MY_MODEL_H
#define MY_MODEL_H

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

int transform_point_scale(point_t pt, const point_t origin,
                          const point_t coeffs);
int transform_point_rotate(point_t pt, const point_t origin,
                           const point_t angles);
int transform_point_shift(point_t pt, const point_t shifts);

// В соединениях лежит point_t, то есть указатель =>
// когда меняем точки, соединение будет меняться само
typedef struct connection *connection_t;
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t &con);

point_t connection_get_p1(const connection_t con);
point_t connection_get_p2(const connection_t con);

typedef struct {
  size_t len;
  point_t *arr;
} pt_arr_t;
typedef struct {
  size_t len;
  connection_t *arr;
} con_arr_t;

typedef struct model *model_t;
model_t create_model(pt_arr_t pt_arr, con_arr_t con_arr);
model_t create_empty_model();

size_t &model_get_pt_len(model_t model);
point_t *&model_get_pt_arr(model_t model);
size_t &model_get_con_len(model_t model);
connection_t *&model_get_con_arr(model_t model);

void destroy_model(model_t &gr);

size_t model_get_pt_len(const model_t gr);
size_t model_get_con_len(const model_t gr);

point_t model_get_point(const model_t gr, size_t index);
connection_t model_get_connection(const model_t gr, size_t index);

int model_apply_scale(model_t gr, const point_t origin, const point_t coeffs);
int model_apply_rotate(model_t gr, const point_t origin, const point_t angles);
int model_apply_shift(model_t gr, const point_t shifts);

size_t model_get_point_index(model_t gr, point_t pt);

#endif // MY_MODEL_H
