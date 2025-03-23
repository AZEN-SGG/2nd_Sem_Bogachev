#ifndef ARRAY
#define ARRAY

#define LEN 1234

#include <stdio.h>
#include <stdlib.h>

#include "io_status.h"

io_status read_array(char *a[], int n, const char * name);
void free_array(char **a, int n);
void print_array(char **a, int n, int m);
int delete_string(char ** a, int n, int i);

#endif
