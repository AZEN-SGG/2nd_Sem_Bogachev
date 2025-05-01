#include <stdio.h>
#include <time.h>
#include "solve.h"
#include "make_f.h"

int main(int argc, char*argv[]){
    int m, k;
    double t, res;
    int ret;
    double a, b, eps;
    double (*f)(double);
    if (!(argc == 6 && sscanf(argv[1], "%lf", &a) == 1 && sscanf(argv[2], "%lf", &b) == 1 && sscanf(argv[3], "%lf", &eps) == 1 && sscanf(argv[4], "%d", &m) == 1 && sscanf(argv[5], "%d", &k) == 1)){
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
    t = clock();
    ret = task10(f, a, b, eps, m, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (ret >= 0){
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], 10, res, f(res), ret, c(), t);
    }
    else{
        printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], 10, c(), t);
    }
    return 0;
}