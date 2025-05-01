#include <math.h>
#include <stdio.h> // УБРАТЬ!!!
#include "make_f.h"

static int count = 0;

inline double f0(double x){
    (void)x;
    count++;
    return 1;
}

inline double f1(double x){
    count++;
    return x - 10e100; 
}

inline double f2(double x){
    count++;
    return 4 - x * x; 
}

inline double f3(double x){
    double kv = x * x;
    count++;
    return kv * x + 3 * kv + 16;
}

inline double f4(double x){
    double kv = x * x;
    count++;
    return 3 - 2 * kv - kv * kv; 
}

inline double f5(double x){
    count++;
    return sqrt(fabs(x) + 1) - 2; 
}

inline double f6(double x){
    count++;
    return sqrt(sqrt(fabs(x) + 1) + 1) - 2; 
}

// Производные

inline double df0(double x){
    (void)x;
    return 0; 
}

inline double df1(double x){
    (void)x;
    return 1; 
}

inline double df2(double x){
    return -2 * x; 
}

inline double df3(double x){
    return 3 * x * x + 6 * x; // ОПТИМИЗИРОВАТЬ 
}

inline double df4(double x){
    return -4 * x * (1 + x * x); // ПЕРЕПРОВЕРИТЬ
}

inline double df5(double x){
    int sgn = 1;
    if (x < 0){
        sgn = -1;
    }
    return sgn * 0.5 / sqrt(fabs(x) + 1); // ПЕРЕПРОВЕРИТЬ
}

inline double df6(double x){
    int sgn = 1;
    double vyr;
    if (x < 0){
        sgn = -1;
    }
    vyr = sqrt(fabs(x) + 1);
    return sgn * 0.25 / (vyr * sqrt(vyr + 1)); // ПЕРЕПРОВЕРИТЬ
}

inline double f7(double x){ // УДАЛИТЬ!!!
    return x * x * x - 30 * x * x + 2552; 
}

int c(void){
    return count;
}