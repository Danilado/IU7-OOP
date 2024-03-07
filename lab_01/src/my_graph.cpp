#include "my_graph.h"
#include <cmath>
#include <cstdint>

struct point
{
  double x;
  double y;
  double z;
};

struct connection
{
  point_t p1;
  point_t p2;
};

point_t create_point(double x, double y, double z)
{
  point_t res = (point_t)calloc(1, sizeof(struct point));
  if (res == nullptr)
    return nullptr;

  res->x = x;
  res->y = y;
  res->z = z;

  return res;
}

void destroy_point(point_t &pt)
{
  free(pt);
  pt = nullptr;
}

double point_get_x(const point_t pt)
{
  if (pt == nullptr)
    return NAN;
  return pt->x;
}

double point_get_y(const point_t pt)
{
  if (pt == nullptr)
    return NAN;
  return pt->y;
}

double point_get_z(const point_t pt)
{
  if (pt == nullptr)
    return NAN;
  return pt->z;
}

int transform_point_scale(point_t pt, const point_t origin, const point_t coeffs)
{
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  pt->x = (pt->x - origin->x) * coeffs->x + origin->x;
  pt->y = (pt->y - origin->y) * coeffs->y + origin->y;
  pt->z = (pt->z - origin->z) * coeffs->z + origin->z;

  return 0;
}

int transform_point_rotate(point_t pt, const point_t origin, const point_t angles)
{
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
  double newx = (pt->x - origin->x) * cos(angles->y) * cos(angles->z)                      // x part
                - (pt->y - origin->y) * sin(angles->z) * cos(angles->y)                    // y part
                + (pt->z - origin->z) * sin(angles->y) + origin->x;                        // z part
  double newy = (pt->x - origin->x) * sin(angles->x) * sin(angles->y) * cos(angles->z) +   //
                (pt->x - origin->x) * sin(angles->z) * cos(angles->x)                      // x part
                - (pt->y - origin->y) * sin(angles->x) * sin(angles->y) * sin(angles->z) + //
                (pt->y - origin->y) * cos(angles->x) * cos(angles->z)                      // y part
                - (pt->z - origin->z) * sin(angles->x) * cos(angles->y) + origin->y;       // z part
  double newz = (pt->x - origin->x) * sin(angles->x) * sin(angles->z) -                    //
                (pt->x - origin->x) * sin(angles->y) * cos(angles->x) * cos(angles->z)     // x part
                + (pt->y - origin->y) * sin(angles->x) * cos(angles->z) +                  //
                (pt->y - origin->y) * sin(angles->y) * sin(angles->z) * cos(angles->x)     // y part
                + (pt->z - origin->z) * cos(angles->x) * cos(angles->y) + origin->z;       // z part

  pt->x = newx;
  pt->y = newy;
  pt->z = newz;

  return 0;
}

int transform_point_shift(point_t pt, const point_t shifts)
{
  if (pt == nullptr)
    return TRANSFORM_NO_POINT;
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;

  pt->x += shifts->x;
  pt->y += shifts->y;
  pt->z += shifts->z;

  return 0;
}

connection_t create_connection(point_t p1, point_t p2)
{
  connection_t res = (connection_t)calloc(1, sizeof(struct connection));
  if (res == nullptr)
    return nullptr;

  res->p1 = p1;
  res->p2 = p2;

  return res;
}

void destroy_connection(connection_t &con)
{
  free(con);
  con = nullptr;
}

struct graph
{
  size_t conns_len;
  size_t points_len;
  connection_t *conns;
  point_t *points;
};

graph_t create_graph(pt_arr_t pt_arr, con_arr_t con_arr)
{
  graph_t gr = (graph_t)calloc(1, sizeof(struct graph));
  if (gr == nullptr)
    return nullptr;

  gr->points_len = pt_arr.len;
  gr->conns_len = con_arr.len;

  gr->points = pt_arr.arr;
  gr->conns = con_arr.arr;

  return gr;
}

void destroy_graph(graph_t &gr)
{
  if (gr == nullptr)
    return;

  if (gr->points)
    for (size_t i = 0; i < gr->points_len; ++i)
      destroy_point(gr->points[i]);

  if (gr->conns)
    for (size_t i = 0; i < gr->conns_len; ++i)
      destroy_connection(gr->conns[i]);

  free(gr);
  gr = nullptr;
}

int graph_apply_scale(graph_t gr, const point_t origin, const point_t coeffs)
{
  if (gr == nullptr)
    return TRANSFORM_NO_GRAPH;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (coeffs == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = 0;

  for (size_t i = 0; !rc && i < gr->points_len; ++i)
    rc = transform_point_scale(gr->points[i], origin, coeffs);

  return rc;
}

int graph_apply_rotate(graph_t gr, const point_t origin, const point_t angles)
{
  if (gr == nullptr)
    return TRANSFORM_NO_GRAPH;
  if (origin == nullptr)
    return TRANSFORM_NO_ORIGIN;
  if (angles == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = 0;

  for (size_t i = 0; !rc && i < gr->points_len; ++i)
    rc = transform_point_rotate(gr->points[i], origin, angles);

  return rc;
}

int graph_apply_shift(graph_t gr, const point_t shifts)
{
  if (gr == nullptr)
    return TRANSFORM_NO_GRAPH;
  if (shifts == nullptr)
    return TRANSFORM_NO_DATA;

  int rc = 0;

  for (size_t i = 0; !rc && i < gr->points_len; ++i)
    rc = transform_point_shift(gr->points[i], shifts);

  return rc;
}

point_t connection_get_p1(const connection_t con)
{
  if (con == nullptr)
    return nullptr;

  return con->p1;
}

point_t connection_get_p2(const connection_t con)
{
  if (con == nullptr)
    return nullptr;

  return con->p2;
}

size_t graph_get_pt_len(const graph_t gr)
{
  if (gr == nullptr)
    return 0;

  return gr->points_len;
}

size_t graph_get_con_len(const graph_t gr)
{
  if (gr == nullptr)
    return 0;

  return gr->conns_len;
}

point_t graph_get_point(const graph_t gr, size_t index)
{
  if (gr == nullptr)
    return nullptr;
  if (index >= gr->points_len)
    return nullptr;

  return gr->points[index];
}

connection_t graph_get_connection(const graph_t gr, size_t index)
{
  if (gr == nullptr)
    return nullptr;
  if (index >= gr->conns_len)
    return nullptr;

  return gr->conns[index];
}

size_t graph_get_point_index(graph_t gr, point_t pt)
{
  if (gr == nullptr)
    return SIZE_MAX;
  if (pt == nullptr)
    return SIZE_MAX;

  size_t i = 0;
  for (i = 0; i < gr->points_len && pt != gr->points[i]; ++i)
    ;
  return i;
}
