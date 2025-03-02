#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

void t2_solve(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *));
int check(char **a, int n, int (*cmp)(const char *, const char *));

#endif
