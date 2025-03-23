#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

int t3_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *));

#endif
