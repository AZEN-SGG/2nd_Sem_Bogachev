#ifndef SOLVE
#define SOLVE

#include <string.h>
#include <stdbool.h>

#include "array.h"

#define INF 97
#define EXTR 122
#define TO_UPPER 32

#define LOWER(a) (INF <= a && a <= EXTR)

int t1_solve(char **arr, int n, char *s);
int t2_solve(char **arr, int n, char *s);
int t3_solve(char **arr, int n, char *s);
int t4_solve(char **arr, int n, char *s);
int t5_solve(char **arr, int n, char *s);
bool check(char *a, char *s);
int t6_solve(char **arr, int n, char *s);
int t7_solve(char **arr, int n, char *s);
int t8_solve(char **arr, int n, char *s);
bool is_inside(char *a, char *s);
int ccmp(char a, char s);

#endif
