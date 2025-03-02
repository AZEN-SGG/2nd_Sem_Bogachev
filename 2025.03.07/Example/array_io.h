#ifndef ARRAY_IO_H
#define ARRAY_IO_H

io_status read_matrix(double *a, int n, int m, const char *name);
void print_matrix(const double *a, int n, int m, int p);
void init_matrix(double *a, int n, int m);

#endif
