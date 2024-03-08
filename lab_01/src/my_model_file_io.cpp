#include "my_model_file_io.h"

static void destroy_point_arr(point_t *&arr, size_t len) {
  if (arr == nullptr)
    return;

  for (size_t i = 0; i < len; ++i)
    destroy_point(arr[i]);
  free(arr);
}

static void destroy_con_arr(connection_t *&arr, size_t len) {
  if (arr == nullptr)
    return;

  for (size_t i = 0; i < len; ++i)
    destroy_connection(arr[i]);
  free(arr);
}

static int model_fread_pt_len(FILE *f, size_t &pt_len) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &pt_len) != 1)
    return FILE_BAD_PT_LEN;

  return 0;
}

static int model_fread_point(FILE *f, point_t &pt) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (pt != nullptr)
    return PT_NOT_NULL;

  double x, y, z;
  int rc = 0;

  if (fscanf(f, "%lf%lf%lf", &x, &y, &z) != 3)
    rc = FILE_BAD_PT;

  if (!rc) {

    pt = create_point(x, y, z);
    if (pt == nullptr)
      rc = NO_MEMORY;
  }

  return rc;
}

static int pt_arr_alloc(point_t *&pt_arr, size_t pt_len) {
  pt_arr = (point_t *)calloc(pt_len, sizeof(point_t));
  int rc = 0;
  if (pt_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int model_fread_points(FILE *f, point_t *&pt_arr, size_t pt_len) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;

  if (!rc)
    for (size_t i = 0; !rc && i < pt_len; ++i) {
      rc = model_fread_point(f, pt_arr[i]);
      if (rc)
        destroy_point_arr(pt_arr, i);
    }

  return rc;
}

static int model_fread_con_len(FILE *f, size_t &con_len) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &con_len) != 1)
    return FILE_BAD_CON_LEN;

  return 0;
}

static int fread_con_index(FILE *f, size_t &i, size_t max) {
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

static int model_fread_connection(FILE *f, connection_t &con,
                                  const pt_arr_t pt_arr) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (con != nullptr)
    return CON_NOT_NULL;

  if (pt_arr.arr == nullptr)
    return NO_PT_ARR;

  size_t i1, i2;
  int rc = fread_con_index(f, i1, pt_arr.len);
  if (!rc) {
    rc = fread_con_index(f, i2, pt_arr.len);
    if (!rc) {
      con = create_connection(pt_arr.arr[i1], pt_arr.arr[i2]);
      if (con == nullptr)
        rc = NO_MEMORY;
    }
  }

  return rc;
}

static int model_fread_connections(FILE *f, con_arr_t &con_arr,
                                   const pt_arr_t pt_arr) {
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
    for (size_t i = 0; !rc && i < con_arr.len; ++i) {
      rc = model_fread_connection(f, con_arr.arr[i], pt_arr);
      if (rc)
        destroy_con_arr(con_arr.arr, i);
    }

  return rc;
}

static int read_points(point_t *&pt_arr, size_t &len, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;
  rc = model_fread_pt_len(f, len);
  if (!rc)
    rc = model_fread_points(f, pt_arr, len);

  return rc;
}

static int read_connections(connection_t *&con_arr, size_t &len, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;
  rc = model_fread_con_len(f, len);
  if (!rc)
    rc = model_fread_connections(f, con_arr, len);

  return rc;
}

int create_model_from_file(model_t &dst, const char *filename) {
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

static int model_fprint_points(const model_t gr, FILE *f) {
  if (gr == nullptr)
    return NO_MODEL;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;

  size_t pt_len = model_get_pt_len(gr);
  if (fprintf(f, "%zu\n", pt_len) < 0)
    rc = PRINT_ERROR;

  if (!rc)
    for (size_t i = 0; !rc && i < pt_len; ++i) {
      point_t pt = model_get_point(gr, i);
      if (fprintf(f, "%.6lf %.6lf %.6lf\n", point_get_x(pt), point_get_y(pt),
                  point_get_z(pt)) < 0)
        rc = PRINT_ERROR;
    }

  return rc;
}

static int model_fprint_connections(const model_t gr, FILE *f) {
  if (gr == nullptr)
    return NO_MODEL;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = 0;

  size_t con_len = model_get_con_len(gr);
  if (fprintf(f, "%zu\n", con_len) < 0)
    rc = PRINT_ERROR;

  if (!rc)
    for (size_t i = 0; !rc && i < con_len; ++i) {
      connection_t con = model_get_connection(gr, i);
      if (fprintf(f, "%zu %zu\n",
                  model_get_point_index(gr, connection_get_p1(con)),
                  model_get_point_index(gr, connection_get_p2(con))) < 0)
        rc = PRINT_ERROR;
    }

  return rc;
}

int write_model_to_file(const model_t gr, const char *filename) {
  if (gr == nullptr)
    return NO_MODEL;

  if (filename == nullptr)
    return IO_BAD_FILENAME;

  FILE *f = fopen(filename, "w");
  if (f == nullptr)
    return IO_BAD_FILENAME;

  int rc = 0;

  rc = model_fprint_points(gr, f);
  if (!rc)
    rc = model_fprint_connections(gr, f);

  return rc;
}
