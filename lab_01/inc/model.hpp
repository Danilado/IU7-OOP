#ifndef MODEL_H
#define MODEL_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "model_error.hpp"

#define OUT
#define VAR

struct point
{
  double x;
  double y;
  double z;
};
typedef struct point *point_t;

struct connection
{
  point_t p1;
  point_t p2;
};
typedef struct connection *connection_t;

typedef struct
{
  size_t len;
  point_t *arr;
} pt_arr_t;
void destroy_pt_arr(pt_arr_t arr);
typedef struct
{
  size_t len;
  connection_t *arr;
} con_arr_t;
void destroy_con_arr(con_arr_t arr);

struct model
{
  pt_arr_t pt_arr;
  con_arr_t con_arr;
};
typedef struct model *model_t;

point_t alloc_point();
point_t create_point(double x, double y, double z);
void destroy_point(point_t &pt);

connection_t alloc_connection();
connection_t create_connection(point_t p1, point_t p2);
void destroy_connection(connection_t &con);

model_t alloc_model();
model_t create_model(pt_arr_t pt_arr, con_arr_t con_arr);

void destroy_model(model_t &gr);

int transform_point_scale(point_t pt, const point_t origin, const point_t coeffs);
int transform_point_rotate(point_t pt, const point_t origin, const point_t angles);
int transform_point_shift(point_t pt, const point_t shifts);

int model_apply_scale(model_t gr, const point_t origin, const point_t coeffs);
int model_apply_rotate(model_t gr, const point_t origin, const point_t angles);
int model_apply_shift(model_t gr, const point_t shifts);

size_t model_get_point_index(pt_arr_t pt_arr, point_t pt);

#endif // MODEL_H
