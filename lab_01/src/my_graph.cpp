#include "my_graph.h"
#include <cmath>

struct point {
  double x;
  double y;
  double z;
};

struct connection {
  point_t p1;
  point_t p2;
};

point_t create_point(double x, double y, double z) {
  point_t res = (point_t)calloc(1, sizeof(struct point));

  res->x = x;
  res->y = y;
  res->z = z;

  return res;
}

void destroy_point(point_t *pt) {
  free(*pt);
  *pt = nullptr;
}

double point_get_x(const point_t pt) {
  if (pt == nullptr)
    return NAN;
  return pt->x;
}

double point_get_y(const point_t pt) {
  if (pt == nullptr)
    return NAN;
  return pt->y;
}

double point_get_z(const point_t pt) {
  if (pt == nullptr)
    return NAN;
  return pt->z;
}

void transform_point_scale(point_t pt, const point_t origin, double kx,
                           double ky, double kz) {
  pt->x = pt->x * kx + origin->x * (1 - kx);
  pt->y = pt->y * ky + origin->y * (1 - ky);
  pt->z = pt->z * kz + origin->z * (1 - kz);
}

void transform_point_rotate(point_t pt, const point_t origin, double ax,
                            double ay, double az) {
  if (pt == nullptr || origin == nullptr)
    return;

  // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
  double newx = (pt->x - origin->x) * cos(ay) * cos(az)      // x part
                - (pt->y - origin->y) * sin(az) * cos(ay)    // y part
                + (pt->z - origin->z) * sin(ay) + origin->x; // z part

  double newy = (pt->x - origin->x) * sin(ax) * sin(ay) * cos(az) +    //
                (pt->x - origin->x) * sin(az) * cos(ax)                // x part
                - (pt->y - origin->y) * sin(ax) * sin(ay) * sin(az) +  //
                (pt->y - origin->y) * cos(ax) * cos(az)                // y part
                - (pt->z - origin->z) * sin(ax) * cos(ay) + origin->y; // z part

  double newz = (pt->x - origin->x) * sin(ax) * sin(az) -              //
                (pt->x - origin->x) * sin(ay) * cos(ax) * cos(az)      // x part
                + (pt->y - origin->y) * sin(ax) * cos(az) +            //
                (pt->y - origin->y) * sin(ay) * sin(az) * cos(ax)      // y part
                + (pt->z - origin->z) * cos(ax) * cos(ay) + origin->z; // z part

  pt->x = newx;
  pt->y = newy;
  pt->z = newz;
}

void transform_point_shift(point_t pt, double dx, double dy, double dz) {
  pt->x += dx;
  pt->y += dy;
  pt->z += dz;
}

connection_t create_connection(point_t p1, point_t p2) {
  connection_t res = (connection_t)calloc(1, sizeof(struct connection));

  res->p1 = p1;
  res->p2 = p2;

  return res;
}

void destroy_connection(connection_t *con) {
  free(*con);
  *con = nullptr;
}

struct graph {
  size_t conns_len;
  size_t points_len;
  connection_t *conns;
  point_t *points;
};

graph_t create_graph(size_t points_len, point_t *points, size_t connections_len,
                     connection_t *connections) {
  graph_t gr = (graph_t)calloc(1, sizeof(struct graph));
  if (!gr)
    return gr;

  gr->points_len = points_len;
  gr->conns_len = connections_len;

  gr->points = points;
  gr->conns = connections;

  return gr;
}

void destroy_graph(graph_t *gr) {
  if (!gr || !*gr)
    return;

  for (size_t i = 0; i < (*gr)->points_len; ++i)
    destroy_point(&((*gr)->points[i]));

  for (size_t i = 0; i < (*gr)->conns_len; ++i)
    destroy_connection(&((*gr)->conns[i]));

  free(*gr);
  *gr = nullptr;
}

void graph_apply_scale(graph_t gr, const point_t origin, double kx, double ky,
                       double kz) {
  for (size_t i = 0; i < gr->points_len; ++i)
    transform_point_scale(gr->points[i], origin, kx, ky, kz);
}

void graph_apply_rotate(graph_t gr, const point_t origin, double ax, double ay,
                        double az) {
  for (size_t i = 0; i < gr->points_len; ++i)
    transform_point_rotate(gr->points[i], origin, ax, ay, az);
}

void graph_apply_shift(graph_t gr, double dx, double dy, double dz) {
  for (size_t i = 0; i < gr->points_len; ++i)
    transform_point_shift(gr->points[i], dx, dy, dz);
}

point_t connection_get_p1(const connection_t con) {
  if (con == nullptr)
    return nullptr;
  return con->p1;
}

point_t connection_get_p2(const connection_t con) {
  if (con == nullptr)
    return nullptr;
  return con->p2;
}

size_t graph_get_pt_len(const graph_t gr) {
  if (gr == nullptr)
    return 0;
  return gr->points_len;
}

size_t graph_get_con_len(const graph_t gr) {
  if (gr == nullptr)
    return 0;
  return gr->conns_len;
}

point_t graph_get_point(const graph_t gr, size_t index) {
  if (gr == nullptr)
    return nullptr;
  if (index >= gr->points_len)
    return nullptr;
  return gr->points[index];
}

connection_t graph_get_connection(const graph_t gr, size_t index) {
  if (gr == nullptr)
    return nullptr;
  if (index >= gr->conns_len)
    return nullptr;
  return gr->conns[index];
}

size_t graph_get_point_index(graph_t gr, point_t pt) {
  size_t i = 0;
  for (i = 0; i < gr->points_len && pt != gr->points[i]; ++i)
    ;
  return i;
}
