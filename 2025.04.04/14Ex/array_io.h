#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#include "io_status.h"
#include "init_f.h"

io_status read_matrix(double *a, int n, const char *name);
void print_matrix(const double *a, int n, int p);
void init_matrix(double *a, int n, int k);
void init_identity_matrix(double *a, int n;)

#endif
