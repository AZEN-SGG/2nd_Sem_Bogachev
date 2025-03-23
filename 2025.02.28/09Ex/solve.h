#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

void t9_solve(char **a, int n, int (*cmp)(const char *, const char *));
int findIndex(char **a, int n, char *x, int (*cmp)(const char *, const char *));

#endif
