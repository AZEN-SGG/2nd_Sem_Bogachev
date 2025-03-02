#ifndef SOLVE_H
#define SOLVE_H

#include <stddef.h>
#include "array.h"
#include "sort.h"

// Headers from 1Ex
int t1_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *));

// Headers from 2Ex
void t2_solve(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *));

// Headers from 3Ex
int t3_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *));

// Headers from 4Ex
void t4_solve(char **a, int n, int (*cmp)(const char *, const char *));

// Headers from 5Ex
void t5_solve(char **a, int n, int (*cmp)(const char *, const char *));
int minimum(char **a, int n, int (*cmp)(const char *, const char *));

// Headers from 6Ex
void t6_solve(char **a, int n, int (*cmp)(const char *, const char *));
int t6_find(char **arr, int n, char *a, int (*cmp)(const char *, const char *));
void t6_append(char **arr, int n, char *a, int index);

// Headers from 7Ex
void t7_solve(char **a, int n, int (*cmp)(const char *, const char *));
int t7_find(char **arr, int n, char *a, int (*cmp)(const char *, const char *));
void t7_append(char **arr, int n, char *a, int index);

// Headers from 8Ex
void t8_solve(char **a, char **b, int n, int (*cmp)(const char *, const char *));
void unite(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *));

// Headers from 9Ex
void t9_solve(char **a, int n, int (*cmp)(const char *, const char *));
int findIndex(char **a, int n, char *x, int (*cmp)(const char *, const char *));

#endif
