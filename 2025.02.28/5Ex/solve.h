#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

void t5_solve(char **a, int n, int (*cmp)(const char *, const char *));
int minimum(char **a, int n, int (*cmp)(const char *, const char *));

#endif
