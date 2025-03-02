#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

void t8_solve(char **a, char **b, int n, int (*cmp)(const char *, const char *));
void unite(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *));

#endif
