#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "solve.h"
#include "make_f.h"

int main(int argc, char*argv[]){
    double *d;
    int m, k, deg;
    double t, res;
    int ret;
    double a, b, eps;
    double (*f)(double);
    if (!(argc == 7 && sscanf(argv[1], "%d", &deg) == 1 && sscanf(argv[2], "%lf", &a) == 1 && sscanf(argv[3], "%lf", &b) == 1 && sscanf(argv[4], "%lf", &eps) == 1 && sscanf(argv[5], "%d", &m) == 1 && sscanf(argv[6], "%d", &k) == 1)){
        printf("Usage %s\n", argv[0]);
        return 1;
    }
    if (b <= a){
        printf("[a;b] not segment\n");
        return 4;
    }
    if (!(0 <= k && k <= 6)){
        printf("k - number of formula doesn't match options\n");
        return 2;
    }
    if (m <= 0){
        printf("Number of iterations must be positive number\n");
        return 3;
    }
    if (deg <= 0){
        printf("deg < 0 is no\n");
        return 5;
    }
    switch (k){
        case (0):
            f = f0;
            break;
        case (1):
            f = f1;
            break;
        case (2):
            f = f2;
            break;
        case (3):
            f = f3;
            break;
        case (4):
            f = f4;
            break;
        case (5):
            f = f5;
            break;
        case (6):
            f = f6;
            break;
    }
    // создаём массив d
    d = (double *)malloc(3 * (deg + 1) * sizeof(double));
    if (!d){
        printf("No pamyat\n");
        return 2;
    }
    t = clock();
    ret = task06(f, deg, d, a, b, eps, m, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (ret >= 0){
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], 6, res, f(res), ret, c(), t);
    }
    else{
        printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], 6, c(), t);
    }
    free(d);
    return 0;
}