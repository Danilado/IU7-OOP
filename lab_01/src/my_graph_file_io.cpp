#include "my_graph_file_io.h"

static void destroy_point_arr(point_t *&arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        destroy_point(arr[i]);
    free(arr);
}

static void destroy_con_arr(connection_t *&arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        destroy_connection(arr[i]);
    free(arr);
}

static int graph_fread_pt_len(FILE *f, size_t &pt_len)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (fscanf(f, "%zu", &pt_len) != 1)
        return FILE_BAD_PT_LEN;

    return 0;
}

static int graph_fread_point(FILE *f, point_t &pt)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (pt != nullptr)
        return PT_NOT_NULL;

    double x, y, z;
    int rc = 0;

    if (fscanf(f, "%lf%lf%lf", &x, &y, &z) != 3)
        rc = FILE_BAD_PT;

    if (!rc)
    {

        pt = create_point(x, y, z);
        if (pt == nullptr)
            rc = NO_MEMORY;
    }

    return rc;
}

static int graph_fread_points(FILE *f, point_t *&pt_arr, size_t pt_len)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (pt_arr != nullptr)
        return PT_ARR_NOT_NULL;

    int rc = 0;

    pt_arr = (point_t *)calloc(pt_len, sizeof(point_t));
    if (pt_arr == nullptr)
        rc = NO_MEMORY;

    if (!rc)
        for (size_t i = 0; !rc && i < pt_len; ++i)
        {
            rc = graph_fread_point(f, pt_arr[i]);
            if (rc)
                destroy_point_arr(pt_arr, i);
        }

    return rc;
}

static int graph_fread_con_len(FILE *f, size_t &con_len)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (fscanf(f, "%zu", &con_len) != 1)
        return FILE_BAD_CON_LEN;

    return 0;
}

static int fread_con_index(FILE *f, size_t &i, size_t max)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    int rc = 0;

    if (fscanf(f, "%zu", &i) != 1)
        rc = FILE_BAD_CON;

    if (!rc)
        if (i >= max)
            rc = FILE_BAD_CON;

    return rc;
}

static int graph_fread_connection(FILE *f, connection_t &con, const pt_arr_t pt_arr)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (con != nullptr)
        return CON_NOT_NULL;

    if (pt_arr.arr == nullptr)
        return NO_PT_ARR;

    size_t i1, i2;
    int rc = fread_con_index(f, i1, pt_arr.len);
    if (!rc)
    {
        rc = fread_con_index(f, i2, pt_arr.len);
        if (!rc)
        {
            con = create_connection(pt_arr.arr[i1], pt_arr.arr[i2]);
            if (con == nullptr)
                rc = NO_MEMORY;
        }
    }

    return rc;
}

static int graph_fread_connections(FILE *f, con_arr_t &con_arr, const pt_arr_t pt_arr)
{
    if (f == nullptr)
        return IO_BAD_STREAM;

    if (con_arr.arr != nullptr)
        return CON_ARR_NOT_NULL;

    if (pt_arr.arr == nullptr)
        return NO_PT_ARR;

    int rc = 0;

    con_arr.arr = (connection_t *)calloc(con_arr.len, sizeof(connection_t));
    if (con_arr.arr == nullptr)
        rc = NO_MEMORY;

    if (!rc)
        for (size_t i = 0; !rc && i < con_arr.len; ++i)
        {
            rc = graph_fread_connection(f, con_arr.arr[i], pt_arr);
            if (rc)
                destroy_con_arr(con_arr.arr, i);
        }

    return rc;
}

static int read_points(pt_arr_t &dst, FILE *f)
{
    if (dst.arr != nullptr)
        return PT_ARR_NOT_NULL;

    if (f == nullptr)
        return IO_BAD_STREAM;

    int rc = 0;
    rc = graph_fread_pt_len(f, dst.len);
    if (!rc)
        rc = graph_fread_points(f, dst.arr, dst.len);

    return rc;
}

static int read_connections(con_arr_t &dst, const pt_arr_t pt_arr, FILE *f)
{
    if (dst.arr != nullptr)
        return CON_ARR_NOT_NULL;

    if (pt_arr.arr == nullptr)
        return NO_PT_ARR;

    if (f == nullptr)
        return IO_BAD_STREAM;

    int rc = 0;
    rc = graph_fread_con_len(f, dst.len);
    if (!rc)
        rc = graph_fread_connections(f, dst, pt_arr);

    return rc;
}

int create_graph_from_file(graph_t &dst, const char *filename)
{
    if (filename == nullptr)
        return IO_BAD_FILENAME;

    if (dst != nullptr)
        return IO_GRAPH_NOT_EMPTY;

    FILE *f = fopen(filename, "r");
    if (f == nullptr)
        return IO_BAD_FILENAME;

    int rc = 0;

    graph_t tmp = nullptr;
    pt_arr_t pt_arr = {0, nullptr};
    con_arr_t con_arr = {0, nullptr};

    rc = read_points(pt_arr, f);
    if (!rc)
    {
        rc = read_connections(con_arr, pt_arr, f);
        if (!rc)
        {
            tmp = create_graph(pt_arr, con_arr);
            if (tmp == nullptr)
                rc = NO_MEMORY;

            if (!rc)
                dst = tmp;
            else
                destroy_con_arr(con_arr.arr, con_arr.len);
        }

        if (rc)
            destroy_point_arr(pt_arr.arr, pt_arr.len);
    }

    fclose(f);
    return rc;
}

static int graph_fprint_points(const graph_t gr, FILE *f)
{
    if (gr == nullptr)
        return NO_GRAPH;
    if (f == nullptr)
        return IO_BAD_STREAM;

    int rc = 0;

    size_t pt_len = graph_get_pt_len(gr);
    if (fprintf(f, "%zu\n", pt_len) < 0)
        rc = PRINT_ERROR;

    if (!rc)
        for (size_t i = 0; !rc && i < pt_len; ++i)
        {
            point_t pt = graph_get_point(gr, i);
            if (fprintf(f, "%.6lf %.6lf %.6lf\n", point_get_x(pt), point_get_y(pt), point_get_z(pt)) < 0)
                rc = PRINT_ERROR;
        }

    return rc;
}

static int graph_fprint_connections(const graph_t gr, FILE *f)
{
    if (gr == nullptr)
        return NO_GRAPH;
    if (f == nullptr)
        return IO_BAD_STREAM;

    int rc = 0;

    size_t con_len = graph_get_con_len(gr);
    if (fprintf(f, "%zu\n", con_len) < 0)
        rc = PRINT_ERROR;

    if (!rc)
        for (size_t i = 0; !rc && i < con_len; ++i)
        {
            connection_t con = graph_get_connection(gr, i);
            if (fprintf(f,
                        "%zu %zu\n",
                        graph_get_point_index(gr, connection_get_p1(con)),
                        graph_get_point_index(gr, connection_get_p2(con))) < 0)
                rc = PRINT_ERROR;
        }

    return rc;
}

int write_graph_to_file(const graph_t gr, const char *filename)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (filename == nullptr)
        return IO_BAD_FILENAME;

    FILE *f = fopen(filename, "w");
    if (f == nullptr)
        return IO_BAD_FILENAME;

    int rc = 0;

    rc = graph_fprint_points(gr, f);
    if (!rc)
        rc = graph_fprint_connections(gr, f);

    return rc;
}
