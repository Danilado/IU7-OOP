#include "my_graph.h"

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

    res->x = x;
    res->y = y;
    res->z = z;

    return res;
}

void destroy_point(point_t *pt)
{
    free(*pt);
    *pt = nullptr;
}

void transform_point_scale(point_t pt, const point_t origin, double kx, double ky, double kz)
{
    pt->x = (pt->x - origin->x) * kx + origin->x * (1 - kx);
    pt->y = (pt->y - origin->y) * ky + origin->y * (1 - ky);
    pt->z = (pt->z - origin->z) * kz + origin->z * (1 - kz);
}

void transform_point_rotate(point_t pt, const point_t origin, double ax, double ay, double az)
{
    if (pt == nullptr || origin == nullptr)
        return;

    // https://ru.wikipedia.org/wiki/Матрица_поворота#Матрица_поворота_в_трёхмерном_пространстве
    double newx = (pt->x - origin->x) * cos(ay) * cos(az)      // x
                  - (pt->y - origin->y) * sin(az) * cos(ay)    // y
                  + (pt->z - origin->z) * sin(ay) + origin->x; // z

    double newy = (pt->x - origin->x) * sin(ax) * sin(ay) * cos(az) + (pt->x - origin->x) * sin(az) * cos(ax)   // x
                  - (pt->y - origin->y) * sin(ax) * sin(ay) * sin(az) + (pt->y - origin->y) * cos(ax) * cos(az) // y
                  - (pt->z - origin->z) * sin(ax) * cos(ay) + origin->y;                                        // z

    double newz = (pt->x - origin->x) * sin(ax) * sin(az) - (pt->x - origin->x) * sin(ay) * cos(ax) * cos(az)   // x
                  + (pt->y - origin->y) * sin(ax) * cos(az) + (pt->y - origin->y) * sin(ay) * sin(az) * cos(ax) // y
                  + (pt->z - origin->z) * cos(ax) * cos(ay) + origin->z;                                        // z

    pt->x = newx;
    pt->y = newy;
    pt->z = newz;
}

void transform_point_shift(point_t pt, double dx, double dy, double dz)
{
    pt->x += dx;
    pt->y += dy;
    pt->z += dz;
}

connection_t create_connection(point_t p1, point_t p2)
{
    connection_t res = (connection_t)calloc(1, sizeof(struct connection));

    res->p1 = p1;
    res->p2 = p2;

    return res;
}

void destroy_connection(connection_t *con)
{
    free(*con);
    *con = nullptr;
}

struct graph
{
    size_t conns_len;
    size_t points_len;
    connection_t *conns;
    point_t *points;
};

graph_t create_graph(size_t points_len, point_t *points, size_t connections_len, connection_t *connections)
{
    graph_t gr = (graph_t)calloc(1, sizeof(struct graph));
    if (!gr)
        return gr;

    gr->points_len = points_len;
    gr->conns_len = connections_len;

    gr->points = points;
    gr->conns = connections;

    return gr;
}

void destroy_graph(graph_t *gr)
{
    if (!gr || !*gr)
        return;

    for (size_t i = 0; i < (*gr)->points_len; ++i)
        destroy_point(&((*gr)->points[i]));

    for (size_t i = 0; i < (*gr)->conns_len; ++i)
        destroy_connection(&((*gr)->conns[i]));

    free(*gr);
    *gr = nullptr;
}

graph_t create_graph_from_file(QString filename)
{
    FILE *f = fopen(filename.toLocal8Bit().data(), "r");
    if (f == nullptr)
        return nullptr;

    size_t pt_len, con_len;

    if (fscanf(f, "%zu", &pt_len) != 1) {
        fclose(f);
        return nullptr;
    }

    point_t *pt_arr = (point_t *) calloc(pt_len, sizeof(point_t));

    for (size_t i = 0; i < pt_len; ++i) {
        double tmp1, tmp2, tmp3;

        if (fscanf(f, "%lf%lf%lf", &tmp1, &tmp2, &tmp3) != 3) {
            for (size_t j = 0; j < i; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);

            fclose(f);
            return nullptr;
        }
        pt_arr[i] = create_point(tmp1, tmp2, tmp3);

        if (pt_arr[i] == nullptr) {
            for (size_t j = 0; j < i; ++j)
                destroy_point(&pt_arr[j]);
            free(pt_arr);

            fclose(f);
            return nullptr;
        }
    }

    if (fscanf(f, "%zu", &con_len) != 1) {
        for (size_t j = 0; j < pt_len; ++j)
            destroy_point(&pt_arr[j]);
        free(pt_arr);
        fclose(f);

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

            fclose(f);

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

            fclose(f);

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

        fclose(f);

        return nullptr;
    }

    fclose(f);
    return res;
}

size_t _get_point_index(point_t pt, point_t *pts)
{
    size_t i = 0;
    for (i = 0; pt != pts[i]; ++i)
        ;
    return i;
}

void write_graph_to_file(graph_t gr, QString filename)
{
    if (gr == nullptr)
        return;

    FILE *f = fopen(filename.toLocal8Bit().data(), "w");
    if (f == nullptr)
        return;

    fprintf(f, "%zu\n", gr->points_len);

    for (size_t i = 0; i < gr->points_len; ++i)
        fprintf(f, "%.6lf %.6lf %.6lf\n", gr->points[i]->x, gr->points[i]->y, gr->points[i]->z);

    fprintf(f, "%zu\n", gr->conns_len);

    for (size_t i = 0; i < gr->conns_len; ++i)
        fprintf(f,
                "%zu %zu\n",
                _get_point_index(gr->conns[i]->p1, gr->points),
                _get_point_index(gr->conns[i]->p2, gr->points));

    fclose(f);
}
