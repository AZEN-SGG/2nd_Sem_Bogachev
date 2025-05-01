#include "math.h"
#include "solve.h"
#include <stdio.h> // УБРАТЬ

inline int sravn_el(double x1, double x2){
    double eps = 1e-16;
    return fabs(x1 - x2) <= eps * fmax(fabs(x1), fabs(x2));
}

int task01(double (*f)(double), double a, double b, double eps, int m, double* x){
    int it, mon;
    double c = (a + b) / 2;
    double dlina_otrezka;
    double znach_a, znach_b, znach_c;
    znach_a = f(a);
    znach_b = f(b);
    mon = 1;
    if (znach_a > znach_b){
        mon = -1;
    }
    dlina_otrezka = b - a;
    if ((znach_a > 0 && znach_b > 0) || (znach_a < 0 && znach_b < 0)){
        return -1;
    }
    for (it = 1; it <= m; it++){
        if (dlina_otrezka < fmin(EPS, eps)){ // Считаем, ято метод не применим
            return -1;
        }
        dlina_otrezka *= 0.5;
        c = a + dlina_otrezka;
        znach_c = f(c);

        if (fabs(znach_c) < eps){
            *x = c;
            return it;
        }
        if (znach_c * mon > 0){
            b = c;
            znach_b = znach_c;
        }
        else {
            a = c;
            znach_a = znach_c;
        }
    }
    return -1; // За все итерации ничего путного
}

int task02(double (*f)(double), double (*df)(double), double x0, double eps, int m, double* x){
    int it;
    double znach_x0;
    double znach_pr_x0;
    double dop_x0;
    znach_x0 = f(x0);
    znach_pr_x0 = df(x0);
    for (it = 1; it <= m; it++){
        // УСЛОВИЯ ЗАВЕРШЕНИЯ
        if (fabs(znach_x0) < eps){ // Если значение в точке ~ноль
            *x = x0;
            return it;
        }
        dop_x0 = x0 - (znach_x0 / znach_pr_x0);
        if (fabs(dop_x0 - x0) < fmin(EPS, eps)){ // Считаем, что метод не применим
            return -1;
        }
        if (sravn_el(znach_pr_x0, 0)){ // Если значение произвдной 0, то метод не применим
            return -1;
        }
        x0 = dop_x0;
        znach_x0 = f(x0);
        znach_pr_x0 = df(x0);
    }
    return -1; // За все итерации ничего путного
}

int task03(double (*f)(double), double a, double b, double eps, int m, double* x){ // Если что-то не работает, то это метод не очень :)
    int it, mon;
    double c;
    double znach_c;
    double znach_a = f(a);
    double znach_b = f(b);
    mon = 1;
    if (znach_a > znach_b){
        mon = -1;
    }
    if ((znach_a > 0 && znach_b > 0) || (znach_a < 0 && znach_b < 0)){
        return -1;
    }
    for (it = 1; it <= m; it++){
        if (sravn_el(znach_b - znach_a, 0)){
            return -1;
        }
        if (fabs(b - a) < fmin(eps, EPS)){
            return -1;
        }
        c = a - (f(a) * (b - a) / (znach_b - znach_a));
        znach_c = f(c);
        if (c < a || c > b){ // c за пределами отрезка
            return -1;
        }
        if (znach_c < eps){
            *x = c;
            return it;
        }
        if (znach_c * mon > 0){ // С помощью значения "монотонности" проще написать проверку
            b = c;
            znach_b = znach_c;
        }
        else {
            a = c;
            znach_a = znach_c;
        }
    }
    return -1; // За все итерации ничего путного
}


int task04(double (*f)(double), double a, double b, double eps, int m, double* x){
    int it;
    double znach_c;
    double c;
    double znach_a = f(a);
    double znach_b = f(b);
    for (it = 1; it <= m; it++){
        //printf("a: %e f(a): %e\n", a, znach_a);
        //printf("b: %e f(b): %e\n", b, znach_b);
        if (sravn_el(znach_b - znach_a, 0)){
            return -1;
        }
        c = b - (znach_b * (b - a) / (znach_b - znach_a));
        znach_c = f(c); 
        if (fabs(znach_c) < eps){
            *x = b;
            return it;
        }
        if (fabs(b - a) < fmin(EPS, eps)){
            return -1; 
        }
        a = b;
        znach_a = znach_b;
        b = c;
        znach_b = znach_c;
    }
    return -1; // За все итерации ничего путного
}

int task05(double (*f)(double), double a, double c, double eps, int m, double* x){
    double w;
    double b, d;
    double razd_razn;
    double podkor_vyr;
    double znach_a, znach_b, znach_c, znach_d;
    int znak, it;
    b = (a + c) / 2;
    znach_a = f(a);
    znach_b = f(b);
    znach_c = f(c);
    for (it = 1; it <= m; it++){
        //printf("a: %lf b: %lf c: %lf\n", a, b, c);
        //printf("f(a): %lf f(b): %lf f(c): %lf\n", znach_a, znach_b, znach_c);
        if (fabs(b - c) < EPS || fabs(a - c) < EPS || fabs(a - b) < EPS){
            return -1;
        }
        w = (znach_b - znach_c) / (b - c) + (znach_a - znach_c) / (a - c) - (znach_a - znach_b) / (a - b);
        if (w < 0){
            znak = -1;
        }
        else{
            znak = 1;
        }
        razd_razn = ((znach_a - znach_b) / (a - b) - (znach_b - znach_c) / (b - c)) / (a - c);
        podkor_vyr = w * w - 4 * razd_razn;
        if (podkor_vyr < 0) podkor_vyr = 0;
        d = c - 2 * znach_c / (w + znak * sqrt(podkor_vyr));
        znach_d = f(d);
        //printf("d: %lf f(d): %lf\n", d, znach_d);
        if (fabs(znach_d) < eps){
            *x = d;
            return it;
        }
        if (fabs(d - c) < fmin(EPS, eps)){
            return -1;
        }
        a = b;
        znach_a = znach_b;
        b = c;
        znach_b = znach_c;
        c = d;
        znach_c = znach_d;
    }
    return -1; // За все итерации ничего путного
}

int task06(double (*f)(double), double deg, double* d, double a, double b, double eps, int m, double* x){ // Недоделана
    (void)f;
    (void)deg;
    (void)d;
    (void)a;
    (void)b;
    (void)eps;
    (void)m;
    (void)x;
    return -1;
}

double task04_09(double x0, int n, double* x, double* y, double* d, double*znach){ // Недоделана
    int i, m;
    double p;
    double pred_el, razn, tek_el;
    int double_n = 2 * n;
    (void)x0;
    (void)n;
    (void)x;
    (void)y;
    (void)d;
    (void)*znach;
    (void)m;
    /*
    printf("y:\n");
    for (i = 0; i<n;i++){
        printf("%lf\n", y[i]);
    }
    printf("d:\n");
    for (i = 0; i<n;i++){
        printf("%lf\n", d[i]);
    }
    */
    pred_el = y[n - 1];
    m = 1;
    for (i = n - 1; i > 0; i--){
        if (2 * i - 2 >= n){
            d[(2 * i) % n] = (d[(2 * i) % n] - d[(2 * i - 2) % n]) / (x[i % n] - x[(i - 1) % n]); 
        }
        else if (2 * i >= n && 2 * i - 2 < n){
            d[(2 * i) % n] = (d[(2 * i) % n] - y[2 * i - 2]) / (x[i % n] - x[(i - 1) % n]); 
        }
        else{
            y[2 * i] = (y[2 * i] - y[2 * i - 2]) / (x[i] - x[i - 1]); 
        }
    }
    for (m = 2; m < double_n; m++){
        // printf("----\n");
        for (i = double_n - 1; i >= m; i--){
            if (i - 1 >= n){
                pred_el = d[i % n];
                tek_el = d[(i - 1) % n];
                razn = x[(i - m) / 2] - x[i / 2];
                if (sravn_el(razn, 0)) return 1;
                d[i % n] = (pred_el - tek_el) / razn;
            }
            else if (i == n){
                pred_el = d[i % n];
                tek_el = y[i - 1];
                razn = x[(i - m) / 2] - x[i / 2];
                if (sravn_el(razn, 0)) return 1;
                d[i % n] = (pred_el - tek_el) / razn;
            }
            else{
                pred_el = y[i];
                tek_el = y[i - 1];
                razn = x[(i - m) / 2] - x[i / 2];
                if (sravn_el(razn, 0)) return 1;
                y[i] = (pred_el - tek_el) / razn;
            }
        }
        p = 0;
        for (i = double_n - 1; i >= 1; i--){
            if (i >= n){
                p = (p + d[i % n]) * (x0 - x[(i - 1) / 2]);
            }
            else{
                p = (p + y[i]) * (x0 - x[(i - 1) / 2]);
            }
        }
        p = p + y[0];
        *znach = p;
        return 0;
    }
    /*
    printf("y:\n");
    for (i = 0; i < n; i++){
        printf("%lf\n", y[i]);
    }
    */
    // Пересчитываем первичную фазу
    return 0;
}

int task07(double (*f)(double), double x0, double eps, int m, double* x){
    int it;
    double znach_x0 = x0;
    for (it = 1; it <= m; it++){
        printf("x0: %lf\n", x0);
        znach_x0 = f(x0);
        if (fabs(znach_x0 - x0) < eps){
            *x = x0;
            return it;
        }
        x0 = znach_x0;
    }
    return -1;
}

int task08(double (*f)(double), double a, double b, double eps, int m, double* x){ // ЧЕРЕЗ ****, НО ВРОДЕ РАБОТАЕТ
    // ДОПИСАТЬ ВЫВОД ЗНАЧЕНИЯ ПОСЛЕ ИНТЕРАЦИЙ эт про чо?
    int i, it;
    double h;
    double tek_tochka, tek_znach, sled_tochka = 0, sled_znach = 0;
    double t_kr, znach_kr;
    h = b - a;
    tek_tochka = a;
    tek_znach = f(tek_tochka);
    if (tek_znach > f(b)){
        znach_kr = tek_znach;
        t_kr = a;
    }
    else{
        znach_kr = f(b);
        t_kr = b;
    }
    for (it = 0; it < m / 10; it++){
        if (it % 2 == 0){
            h = h * 0.1;
            //printf("h_c: %e\n", h);
            if (fabs(h) < eps){
                if (tek_znach > sled_znach){
                    if (tek_znach > znach_kr){
                        *x = tek_tochka;
                    }
                    else{
                        *x = t_kr;
                    }
                }
                else{
                    if (sled_znach > znach_kr){
                        *x = sled_tochka;
                    }
                    else {
                        *x = t_kr;
                    }
                }
                return it + 1;
            }
            for (i = 1; i <= 10; i++){
                //printf("tek: %lf %lf\n", tek_tochka, tek_znach);
                sled_tochka = a + i * h;
                sled_znach = f(sled_tochka);
                if (tek_znach > sled_znach){
                    break;
                }
                if (i == 10) break;
                tek_tochka = sled_tochka;
                tek_znach = sled_znach;
            }
            a = tek_tochka;
            b = sled_tochka;
            //printf("new a: %lf b: %lf\n", a, b);
            //printf("---------\n");
        }
        else {
            h = h * 0.1;
            //printf("h_n: %e\n", h);
            if (fabs(h) < eps){
                if (tek_znach > sled_znach){
                    if (tek_znach > znach_kr){
                        *x = tek_tochka;
                    }
                    else{
                        *x = t_kr;
                    }
                }
                else{
                    if (sled_znach > znach_kr){
                        *x = sled_tochka;
                    }
                    else {
                        *x = t_kr;
                    }
                }
                return it + 1;
            }
            for (i = 1; i <= 10; i++){
                //printf("tek: %lf %lf\n", tek_tochka, tek_znach);
                tek_tochka = b - i * h;
                tek_znach = f(sled_tochka);
                if (tek_znach < sled_znach){
                    break;
                }
                sled_tochka = tek_tochka;
                sled_znach = tek_znach;
            }
            a = tek_tochka;
            b = sled_tochka;
            //printf("new a: %lf b: %lf\n", a, b);
            //printf("---------\n");
        }
    }
    *x = (a + b) / 2;
    return it + 1;
}

int task09(double (*f)(double), double a, double b, double eps, int m, double* x){ // ПРОТЕСТИРОВАТЬ
    double znach_x1, znach_x2;
    double x1, x2;
    int it;
    double razn;
    //double golden_ratio = (1 + sqrt(5)) / 2; // не пригодилося :)
    for (it = 1; it <= m; it++){
        razn = 0.5 * (sqrt(5) - 1) * (b - a);
        x1 = b - razn;
        x2 = a + razn;
        znach_x1 = f(x1);
        znach_x2 = f(x2);
        if (znach_x1 < znach_x2) a = x1;
        else b = x2;
        if (fabs(a - b) < eps){
            *x = (a + b) / 2;
            return it;
        }
    }
    *x = (a + b) / 2;
    return it;
}

int task10(double (*f)(double), double a, double c, double eps, int m, double* x){ // НЕ РАБОТАЕТ
    double w;
    double b, d;
    double razd_razn;
    double podkor_vyr;
    double znach_a, znach_b, znach_c, znach_d;
    int znak, it;
    b = (a + c) / 2;
    znach_a = -fabs(f(a));
    znach_b = -fabs(f(b));
    znach_c = -fabs(f(c));
    for (it = 1; it <= m; it++){
        //printf("a: %lf b: %lf c: %lf\n", a, b, c);
        //printf("f(a): %lf f(b): %lf f(c): %lf\n", znach_a, znach_b, znach_c);
        if (fabs(b - c) < EPS || fabs(a - c) < EPS || fabs(a - b) < EPS){
            return -1;
        }
        w = (znach_b - znach_c) / (b - c) + (znach_a - znach_c) / (a - c) - (znach_a - znach_b) / (a - b);
        if (w < 0){
            znak = -1;
        }
        else{
            znak = 1;
        }
        razd_razn = ((znach_a - znach_b) / (a - b) - (znach_b - znach_c) / (b - c)) / (a - c);
        podkor_vyr = w * w - 4 * razd_razn;
        if (podkor_vyr < 0) podkor_vyr = 0;
        d = c - 2 * znach_c / (w + znak * sqrt(podkor_vyr));
        znach_d = -fabs(f(d));
        //printf("d: %lf f(d): %lf\n", d, znach_d);
        if (fabs(znach_d) < eps){
            *x = d;
            return it;
        }
        if (fabs(d - c) < EPS){
            *x = d;
            return it;
        }
        a = b;
        znach_a = znach_b;
        b = c;
        znach_b = znach_c;
        c = d;
        znach_c = znach_d;
    }
    // ВОЗМОЖНО, УБРАТЬ!!!
    *x = c;
    return it;
}