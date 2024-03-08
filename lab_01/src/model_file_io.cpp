#include "model_file_io.h"

static int model_fread_pt_len(size_t &pt_len, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &pt_len) != 1)
    return FILE_BAD_PT_LEN;

  return 0;
}

static int model_fread_point(point_t &pt, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

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

static int pt_arr_alloc(point_t *&pt_arr, size_t pt_len)
{
  pt_arr = (point_t *)calloc(pt_len, sizeof(point_t));
  int rc = 0;
  if (pt_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int con_arr_alloc(connection_t *&con_arr, size_t con_len)
{
  con_arr = (connection_t *)calloc(con_len, sizeof(connection_t));
  int rc = 0;
  if (con_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int model_fread_points(point_t *&pt_arr, size_t pt_len, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;
  if (pt_arr == nullptr)
    return NO_MEMORY;

  int rc = 0;
  for (size_t i = 0; !rc && i < pt_len; ++i)
    rc = model_fread_point(pt_arr[i], f);

  return rc;
}

static int model_fread_con_len(size_t &con_len, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &con_len) != 1)
    return FILE_BAD_CON_LEN;

  return 0;
}

static int fread_con_index(size_t &i, size_t max, FILE *f)
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

static int model_fread_connection(connection_t &con, const pt_arr_t pt_arr, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  size_t i1, i2;
  int rc = fread_con_index(i1, pt_arr.len, f);
  if (!rc)
  {
    rc = fread_con_index(i2, pt_arr.len, f);
    if (!rc)
    {
      con = create_connection(pt_arr.arr[i1], pt_arr.arr[i2]);
      if (con == nullptr)
        rc = NO_MEMORY;
    }
  }

  return rc;
}

static int model_read_points(pt_arr_t &dst, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;
  rc = model_fread_pt_len(dst.len, f);
  if (!rc)
  {
    rc = pt_arr_alloc(dst.arr, dst.len);
    if (!rc)
      rc = model_fread_points(dst.arr, dst.len, f);
  }

  return rc;
}

static int read_points(model_t &dst, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  return model_read_points(dst->pt_arr, f);
}

static int model_fread_connections(con_arr_t &con_arr, const pt_arr_t pt_arr, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;
  if (pt_arr.arr == nullptr)
    return NO_PT_ARR;

  int rc = 0;
  rc = model_fread_con_len(con_arr.len, f);
  if (!rc)
  {
    rc = con_arr_alloc(con_arr.arr, con_arr.len);
    for (size_t i = 0; !rc && i < con_arr.len; ++i)
      rc = model_fread_connection(con_arr.arr[i], pt_arr, f);
  }

  return rc;
}

static int read_connections(model_t &dst, FILE *f)
{
  if (f == nullptr)
    return IO_BAD_STREAM;

  return model_fread_connections(dst->con_arr, dst->pt_arr, f);
}

int create_model_from_file(model_t &dst, const char *filename)
{
  if (filename == nullptr)
    return IO_BAD_FILENAME;

  FILE *f = fopen(filename, "r");
  if (f == nullptr)
    return IO_BAD_FILENAME;

  int rc = 0;

  rc = read_points(dst, f);
  if (!rc)
    rc = read_connections(dst, f);

  if (rc)
    destroy_model(dst);

  fclose(f);
  return rc;
}

static int model_fprint_points(const pt_arr_t pt_arr, FILE *f)
{
  if (pt_arr.arr == nullptr)
    return NO_PT_ARR;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;

  if (fprintf(f, "%zu\n", pt_arr.len) < 0)
    rc = PRINT_ERROR;

  if (!rc)
    for (size_t i = 0; !rc && i < pt_arr.len; ++i)
    {
      point_t pt = pt_arr.arr[i];
      if (fprintf(f, "%.6lf %.6lf %.6lf\n", pt->x, pt->y, pt->z) < 0)
        rc = PRINT_ERROR;
    }

  return rc;
}

static int model_fprint_connections(const con_arr_t con_arr, const pt_arr_t pt_arr, FILE *f)
{
  if (con_arr.arr == nullptr)
    return NO_CON_ARR;
  if (pt_arr.arr == nullptr)
    return NO_PT_ARR;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;

  size_t con_len = con_arr.len;
  if (fprintf(f, "%zu\n", con_len) < 0)
    rc = PRINT_ERROR;

  if (!rc)
    for (size_t i = 0; !rc && i < con_len; ++i)
    {
      connection_t con = con_arr.arr[i];
      if (fprintf(f, "%zu %zu\n",
                  model_get_point_index(pt_arr, con->p1),
                  model_get_point_index(pt_arr, con->p2) < 0))
        rc = PRINT_ERROR;
    }

  return rc;
}

int write_model_to_file(const model_t gr, const char *filename)
{
  if (gr == nullptr)
    return NO_MODEL;

  if (filename == nullptr)
    return IO_BAD_FILENAME;

  FILE *f = fopen(filename, "w");
  if (f == nullptr)
    return IO_BAD_FILENAME;

  int rc = 0;

  rc = model_fprint_points(gr->pt_arr, f);
  if (!rc)
    rc = model_fprint_connections(gr->con_arr, gr->pt_arr, f);

  return rc;
}
