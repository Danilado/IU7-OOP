#include "my_graph_funcs.h"

graph_t create_graph_from_file(FILE *f)
{
    if (f == nullptr)
        return nullptr;

    size_t pt_len, con_len;

    if (fscanf(f, "%zu", &pt_len) != 1) {
        return nullptr;
    }

    point_t *pt_arr = (point_t *) calloc(pt_len, sizeof(point_t));

    for (size_t i = 0; i < pt_len; ++i) {
        double tmp1, tmp2, tmp3;

        if (fscanf(f, "%lf%lf%lf", &tmp1, &tmp2, &tmp3) != 3) {
            for (size_t j = 0; j < i; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);
            return nullptr;
        }
        pt_arr[i] = create_point(tmp1, tmp2, tmp3);

        if (pt_arr[i] == nullptr) {
            for (size_t j = 0; j < i; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);
            return nullptr;
        }
    }

    if (fscanf(f, "%zu", &con_len) != 1) {
        for (size_t j = 0; j < pt_len; ++j)
            destroy_point(&pt_arr[j]);
        free(pt_arr);
        return nullptr;
    }

    connection_t *con_arr = (connection_t *) calloc(con_len, sizeof(connection_t));

    for (size_t i = 0; i < con_len; ++i) {
        size_t tmp1, tmp2;

        if (fscanf(f, "%zu%zu", &tmp1, &tmp2) != 2) {
            for (size_t j = 0; j < pt_len; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);

            for (size_t j = 0; j < i; ++j)
                destroy_connection(&con_arr[j]);
            free(con_arr);
            return nullptr;
        }
        con_arr[i] = create_connection(pt_arr[tmp1], pt_arr[tmp2]);

        if (con_arr[i] == nullptr) {
            for (size_t j = 0; j < pt_len; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);

            for (size_t j = 0; j < i; ++j)
                destroy_connection(&con_arr[j]);
            free(con_arr);
            return nullptr;
        }
    }

    graph_t res = create_graph(pt_len, pt_arr, con_len, con_arr);
    if (res == nullptr) {
        for (size_t j = 0; j < pt_len; ++j)
            destroy_point(&pt_arr[j]);
        free(pt_arr);

        for (size_t j = 0; j < con_len; ++j)
            destroy_connection(&con_arr[j]);
        free(con_arr);
        return nullptr;
    }
    return res;
}

void write_graph_to_file(graph_t gr, FILE *f)
{
    if (gr == nullptr)
        return;

    if (f == nullptr)
        return;

    size_t pt_len = graph_get_pt_len(gr);
    fprintf(f, "%zu\n", pt_len);

    for (size_t i = 0; i < pt_len; ++i) {
        point_t pt = graph_get_point(gr, i);

        fprintf(f, "%.6lf %.6lf %.6lf\n", point_get_x(pt), point_get_y(pt), point_get_z(pt));
    }

    size_t con_len = graph_get_con_len(gr);

    fprintf(f, "%zu\n", con_len);

    for (size_t i = 0; i < con_len; ++i) {
        connection_t con = graph_get_connection(gr, i);
        fprintf(f,
                "%zu %zu\n",
                graph_get_point_index(gr, connection_get_p1(con)),
                graph_get_point_index(gr, connection_get_p2(con)));
    }
}

void draw_graph(graph_t gr, QPainter *ctx, QColor linecolor, QColor pointcolor,
                double offset_x, double offset_y) {
  if (gr == nullptr)
    return;

  draw_connections(gr, ctx, linecolor, offset_x, offset_y);

  draw_points(gr, ctx, pointcolor, offset_x, offset_y);
}

void draw_connections(graph_t gr, QPainter *ctx, QColor color, double offset_x,
                      double offset_y) {
  if (gr == nullptr)
    return;

  ctx->setPen(color);

  size_t len = graph_get_con_len(gr);

  for (size_t i = 0; i < len; ++i) {
    connection_t tmp = graph_get_connection(gr, i);
    if (tmp == nullptr)
      continue;

    QLineF *tmpline = connection_to_QLineF(tmp, offset_x, offset_y);
    if (tmpline == nullptr)
      continue;

    ctx->drawLine(*tmpline);
    delete tmpline;
  }
}

void draw_points(graph_t gr, QPainter *ctx, QColor color, double offset_x,
                 double offset_y) {
  if (gr == nullptr)
    return;

  ctx->setBrush(color);

  size_t len = graph_get_pt_len(gr);

  for (size_t i = 0; i < len; ++i) {
    point_t tmp = graph_get_point(gr, i);
    if (tmp == nullptr)
      continue;

    QPointF *tmppoint = point_to_QPointF(tmp, offset_x, offset_y);
    if (tmppoint == nullptr)
      continue;

    ctx->drawPoint(*tmppoint);
    delete tmppoint;
  }
}

QPointF *point_to_QPointF(point_t pt, double offset_x, double offset_y) {
  if (pt == nullptr)
    return nullptr;

  return new QPointF(point_get_x(pt) + offset_x, point_get_y(pt) + offset_y);
}

QLineF *connection_to_QLineF(connection_t con, double offset_x,
                             double offset_y) {
  if (con == nullptr)
    return nullptr;

  point_t p1 = connection_get_p1(con);
  point_t p2 = connection_get_p2(con);

  return new QLineF(point_get_x(p1) + offset_x, point_get_y(p1) + offset_y,
                    point_get_x(p2) + offset_x, point_get_y(p2) + offset_y);
}
