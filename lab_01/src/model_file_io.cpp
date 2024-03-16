#include "model_file_io.hpp"

typedef struct {
  size_t i1;
  size_t i2;
} index_pair_t;

static int model_fread_pt_len(OUT size_t &pt_len, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &pt_len) != 1)
    return FILE_BAD_PT_LEN;

  return ALL_OK;
}

static int model_fread_point(OUT point_t &pt, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = ALL_OK;

  pt = alloc_point();
  if (pt == nullptr)
    rc = NO_MEMORY;
  else {
    if (fscanf(f, "%lf%lf%lf", &(pt->x), &(pt->y), &(pt->z)) != 3)
      rc = FILE_BAD_PT;
    if (rc)
      destroy_point(pt);
  }

  return rc;
}

static int pt_arr_alloc(OUT point_t *&pt_arr, size_t pt_len) {
  pt_arr = (point_t *)calloc(pt_len, sizeof(point_t));
  int rc = ALL_OK;
  if (pt_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int con_arr_alloc(OUT connection_t *&con_arr, size_t con_len) {
  con_arr = (connection_t *)calloc(con_len, sizeof(connection_t));
  int rc = ALL_OK;
  if (con_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int pair_arr_alloc(OUT index_pair_t *&pair_arr, size_t pairs_len) {
  pair_arr = (index_pair_t *)calloc(pairs_len, sizeof(index_pair_t));
  int rc = ALL_OK;
  if (pair_arr == nullptr)
    rc = NO_MEMORY;
  return rc;
}

static int model_fread_points(VAR point_t *&data, size_t pt_len, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;
  if (data == nullptr)
    return NO_MEMORY;

  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < pt_len; ++i)
    rc = model_fread_point(data[i], f);

  return rc;
}

static int model_fread_con_len(OUT size_t &con_len, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  if (fscanf(f, "%zu", &con_len) != 1)
    return FILE_BAD_CON_LEN;

  return ALL_OK;
}

static int fread_con_index(OUT size_t &i, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = ALL_OK;
  if (fscanf(f, "%zu", &i) != 1)
    rc = FILE_BAD_CON;

  return rc;
}

static int model_fread_pair(OUT index_pair_t &conns, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = fread_con_index(conns.i1, f);
  if (!rc)
    rc = fread_con_index(conns.i2, f);

  return rc;
}

static int model_fread_points(OUT pt_arr_t &dst, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = model_fread_pt_len(dst.len, f);
  if (!rc) {
    rc = pt_arr_alloc(dst.data, dst.len);
    if (!rc)
      rc = model_fread_points(dst.data, dst.len, f);
    if (rc) {
      free(dst.data);
      dst.data = nullptr;
      dst.len = 0;
    }
  }

  return rc;
}

static int wrap_fread_pairs(VAR index_pair_t *pair_arr, size_t len, FILE *f) {
  if (pair_arr == nullptr)
    return NO_MEMORY;

  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = model_fread_pair(pair_arr[i], f);

  return rc;
}

static int model_fread_pairs(OUT index_pair_t *&pair_arr, VAR size_t &len,
                             FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = model_fread_con_len(len, f);
  if (!rc) {
    rc = pair_arr_alloc(pair_arr, len);
    if (!rc) {
      rc = wrap_fread_pairs(pair_arr, len, f);
      if (rc)
        free(pair_arr);
    }
  }

  return rc;
}

static int init_connections(OUT con_arr_t &con_arr, const index_pair_t *pairs,
                            size_t pairs_len) {
  if (!pairs)
    return NO_MEMORY;

  con_arr.len = pairs_len;
  return con_arr_alloc(con_arr.data, con_arr.len);
}

static connection_t form_connection(const point_t *pt_arr, size_t max_index,
                                    index_pair_t i_pair) {
  if (pt_arr == nullptr)
    return nullptr;
  if (i_pair.i1 >= max_index || i_pair.i2 >= max_index)
    return nullptr;

  return create_connection(pt_arr[i_pair.i1], pt_arr[i_pair.i2]);
}

static int model_form_connections(VAR con_arr_t con_arr,
                                  const index_pair_t *pairs,
                                  const pt_arr_t pt_arr) {
  if (pairs == nullptr)
    return NO_MEMORY;
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;
  if (con_arr.data == nullptr)
    return NO_CON_ARR;

  int rc = ALL_OK;

  for (size_t i = 0; !rc && i < con_arr.len; ++i) {
    con_arr.data[i] = form_connection(pt_arr.data, pt_arr.len, pairs[i]);
    if (con_arr.data[i] == nullptr)
      rc = NO_MEMORY;
  }

  return rc;
}

static int model_create_connections_from_pairs(VAR con_arr_t &con_arr,
                                               index_pair_t *pairs,
                                               size_t pairs_len) {
  if (pairs == nullptr)
    return IO_WRITE_ERROR;

  return init_connections(con_arr, pairs, pairs_len);
}

static int model_init_conns_from_file(VAR con_arr_t &con_arr,
                                      const pt_arr_t pt_arr, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;

  index_pair_t *pairs = nullptr;
  size_t pairs_len;

  int rc = model_fread_pairs(pairs, pairs_len, f);
  if (!rc) {
    rc = model_create_connections_from_pairs(con_arr, pairs, pairs_len);
    if (!rc) {
      rc = model_form_connections(con_arr, pairs, pt_arr);
      if (rc)
        destroy_con_arr(con_arr);
    }
    free(pairs);
  }

  return rc;
}

int create_model_from_file(OUT model_t &dst, const char *filename) {
  if (filename == nullptr)
    return IO_BAD_FILENAME;

  FILE *f = fopen(filename, "r");
  if (f == nullptr)
    return IO_BAD_FILENAME;

  int rc = ALL_OK;

  dst = alloc_model();
  if (dst == nullptr)
    rc = NO_MEMORY;
  else {
    rc = model_fread_points(dst->pt_arr, f);
    if (!rc)
      rc = model_init_conns_from_file(dst->con_arr, dst->pt_arr, f);
    if (rc)
      destroy_model(dst);
  }

  fclose(f);
  return rc;
}

static int fprint_point(const point_t pt, FILE *f) {
  if (!pt)
    return MODEL_BAD_POINT;
  if (!f)
    return IO_BAD_STREAM;
  if (fprintf(f, "%.6lf %.6lf %.6lf\n", pt->x, pt->y, pt->z) < 0)
    return PRINT_ERROR;
  return ALL_OK;
}

static int wrap_fprint_points(const point_t *data, size_t len, FILE *f) {
  if (data == nullptr)
    return NO_PT_ARR;
  if (f == nullptr)
    return IO_BAD_STREAM;
  int rc = ALL_OK;
  for (size_t i = 0; !rc && i < len; ++i)
    rc = fprint_point(data[i], f);
  return rc;
}

static int model_fprint_points(const pt_arr_t pt_arr, FILE *f) {
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = ALL_OK;

  if (fprintf(f, "%zu\n", pt_arr.len) < 0)
    rc = PRINT_ERROR;

  if (!rc)
    wrap_fprint_points(pt_arr.data, pt_arr.len, f);

  return rc;
}

static int con_to_ip(index_pair_t &dst, const connection_t con,
                     const pt_arr_t pt_arr) {
  if (con == nullptr)
    return FILE_BAD_CON;
  int rc = ALL_OK;
  rc = model_get_point_index(dst.i1, pt_arr, con->p1);
  if (!rc)
    rc = model_get_point_index(dst.i2, pt_arr, con->p2);
  return rc;
}

static int fprint_index_pair(const index_pair_t pair, FILE *f) {
  if (f == nullptr)
    return IO_BAD_STREAM;
  if (fprintf(f, "%zu %zu\n", pair.i1, pair.i2) < 0)
    return PRINT_ERROR;
  return ALL_OK;
}

static int model_fprint_connections(const con_arr_t con_arr,
                                    const pt_arr_t pt_arr, FILE *f) {
  if (con_arr.data == nullptr)
    return NO_CON_ARR;
  if (pt_arr.data == nullptr)
    return NO_PT_ARR;
  if (f == nullptr)
    return IO_BAD_STREAM;

  int rc = ALL_OK;

  size_t con_len = con_arr.len;
  if (fprintf(f, "%zu\n", con_len) < 0)
    rc = PRINT_ERROR;

  for (size_t i = 0; !rc && i < con_len; ++i) {
    index_pair_t ip;
    rc = con_to_ip(ip, con_arr.data[i], pt_arr);
    if (!rc)
      rc = fprint_index_pair(ip, f);
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

  int rc = ALL_OK;

  rc = model_fprint_points(gr->pt_arr, f);
  if (!rc)
    rc = model_fprint_connections(gr->con_arr, gr->pt_arr, f);

  return rc;
}
