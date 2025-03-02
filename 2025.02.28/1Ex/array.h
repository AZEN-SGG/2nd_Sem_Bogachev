#ifndef ARRAY_H
#define ARRAY_H

#include "io_status.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

io_status read_array(char *a[], int n, const char *name);
void free_array(char **a, int n);
void print_array(char **a, int n, int m);

#endif
