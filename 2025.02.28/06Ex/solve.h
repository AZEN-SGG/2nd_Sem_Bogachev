#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>

void t6_solve(char **a, int n, int (*cmp)(const char *, const char *));
int find(char **arr, int n, char *a, int (*cmp)(const char *, const char *));
void append(char **arr, int n, char *a, int index);

#endif
