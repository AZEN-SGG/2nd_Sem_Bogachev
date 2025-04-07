#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#include <stdbool.h>
#include "io_status.h"
#include "init_f.h"

io_status read_matrix(double *a, int n, const char *name, bool transpose);
void print_matrix(const double *a, int n, int p, bool transpose);
void init_matrix(double *a, int n, int k, bool transpose);
void init_identity_matrix(double *a, int n);
int read_or_init_matrix(double *a, char *name, int k, int n, bool transpose);

#endif
