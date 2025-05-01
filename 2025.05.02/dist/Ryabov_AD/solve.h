#define EPS (1e-16)

int task01(double (*f)(double), double a, double b, double eps, int m, double* x);
int task02(double (*f)(double), double (*df)(double), double x0, double eps, int m, double* x);
int task03(double (*f)(double), double a, double b, double eps, int m, double* x);
int task04(double (*f)(double), double a, double b, double eps, int m, double* x);
int task05(double (*f)(double), double a, double b, double eps, int m, double* x);
int task06(double (*f)(double), double deg, double* d, double a, double b, double eps, int m, double* x);
int task07(double (*f)(double), double x0, double eps, int m, double* x);
int task08(double (*f)(double), double a, double b, double eps, int m, double* x);
int task09(double (*f)(double), double a, double b, double eps, int m, double* x);
int task10(double (*f)(double), double a, double b, double eps, int m, double* x);

int sravn_el(double x1, double x2);

double task04_09(double x0, int n, double* x, double* y, double* d, double*znach);