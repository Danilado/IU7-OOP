#ifndef POINT_H
#define POINT_H

#include "model_error.hpp"
#include <cstdlib>

struct point {
  double x;
  double y;
  double z;
};
typedef struct point *point_t;

typedef struct {
  const point_t origin;
  const point_t coeffs;
} tr_scale_data_t;

typedef struct {
  const point_t origin;
  const point_t angles;
} tr_rot_data_t;

tr_scale_data_t form_tr_scale_data(const point_t origin, const point_t coeffs);
tr_rot_data_t form_rot_data(const point_t origin, const point_t angles);

point_t alloc_point();
point_t create_point(double x, double y, double z);
void destroy_point(point_t &pt);

int transform_point_scale(point_t pt, const point_t origin,
                          const point_t coeffs);
int transform_point_rotate(point_t pt, const point_t origin,
                           const point_t angles);
int transform_point_shift(point_t pt, const point_t shifts);

#endif
