#include <math.h>
#include "solve.h"
#include "massiv_io.h"

int task01(double x0, int n, double* x, double* y, double*znach){
    int i, j;
    double xi, xj, output = 0;
    double chisl = 0, znam = 1;
    for (i = 0; i < n; i++){
        xi = x[i];
        chisl = 1;
        znam = 1;
        for (j = 0; j < i; j++){
            xj = x[j];
            chisl = chisl * (x0 - xj);
            znam = znam * (xi - xj);
            //printf("%d %d: x[%d] = %e xi: %e xj: %e\n", i, j, i, x[i], xi, xj);
            //printf("%e\n", xj / (xj - xi));
        }
        for (j = i + 1; j < n; j++){
            xj = x[j];
            chisl = chisl * (x0 - xj);
            znam = znam * (xi - xj);
            //printf("%d %d: x[%d] = %e xi: %e xj: %e\n", i, j, i, x[i], xi, xj);
            //printf("%e\n", xj / (xj - xi));
        }
        if (sravn_el(znam, 0)){ // произойдёт деление на ноль, отменяем
            return 1;
        }
        output += (y[i] * chisl) / znam;
    }
    *znach = output;
    return 0;
}

int task02(double x0, int n, double* x, double* y, double* znach){
    int i, m;
    double p;
    double pred_el, razn, tek_el;
    (void)x0;
    /*
    printf("do x:\n");
    for (i = 0; i < n; i++){
        printf("%lf\n", x[i]);
    }
    printf("do y:\n");
    for (i = 0; i < n; i++){
        printf("%lf\n", y[i]);
    }
    */
    for (m = 1; m < n; m++){
        pred_el = y[n - 1];
        for (i = n - 1; i >= m; i--){
            tek_el = y[i - 1];
            razn = x[i] - x[i - m];
            if (sravn_el(razn, 0)){
                return 1;
            }
            y[i] = (pred_el - tek_el) / razn;
            pred_el = tek_el;
        }
        /*
        printf("posle %d:\n", m);
        for (i = 0; i < n; i++){
            printf("%lf\n", y[i]);
        }
        */
    }

    p = 0;
    for (i = n - 1; i >= 1; i--){
        p = (p + y[i]) * (x0 - x[i - 1]);
    }
    p = p + y[0];
    *znach = p;
    return 0;
}

int task03(double x0, int n, double* x, double* y, double*znach){
    int i, m;
    double sled_el, razn, tek_el;
    (void)x0;

    /*
    printf("do x:\n");
    for (i = 0; i < n; i++){
        printf("%lf\n", x[i]);
    }
    printf("do y:\n");
    for (i = 0; i < n; i++){
        printf("%lf\n", y[i]);
    }
    */

    for (m = 1; m < n; m++){
        tek_el = y[0];
        for (i = 0; i < n - m; i++){
            sled_el = y[i + 1];
            razn = x[i + m] - x[i];
            /*
            printf("sled = %lf\n", sled_el);
            printf("tek = %lf\n", tek_el);
            printf("%lf\n", razn);
            */
            if (sravn_el(razn, 0)){
                return 1;
            }
            y[i] = (sled_el * (x0 - x[i]) - tek_el * (x0 - x[i + m])) / razn;
            tek_el = sled_el;
        }
        /*
        //printf("posle %d:\n", m);
        for (i = 0; i < n; i++){
            //printf("%lf\n", y[i]);
        }
        //printf("-----\n");
        */
    }
    *znach = y[0];
    return 0;
}

double task04(double x0, int n, double* x, double* y, double* d, double*znach){
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

double task06(double x0, double eps){ // ПРОТЕСТИРОВАТЬ
    int is_minus = 0;
    double output;
    double coss, sinn;
    (void)eps;
    //printf("ist cos: %lf\n", cos(x0));
    x0 = fabs(x0);
    if (x0 >= 2 * M_PI){
        x0 = fmod(x0, 2 * M_PI);
    }
    //printf("ist cos: %lf\n", cos(x0));
    if (x0 >= M_PI){
        is_minus = 1;
        x0 = fmod(x0, M_PI);
    }
    //printf("ist cos: %lf\n", cos(x0));
    //printf("x0:%lf\n", x0);
    if (x0 > 1){
        /*
        printf("ist cos / 2: %lf\n", cos(x0 / 2));
        printf("x0 / 2:%lf\n", x0 / 2);
        printf("cos: %lf\n", calculate_cos(x0 / 2, eps) * calculate_cos(x0 / 2, eps));
        printf("sin: %lf\n", calculate_sin(x0 / 2, eps) * calculate_sin(x0 / 2, eps));
        */
        coss = calculate_cos(x0 / 2, eps);
        sinn = calculate_sin(x0 / 2, eps);
        output = coss * coss - sinn * sinn;
    }
    else{
        output = calculate_cos(x0, eps);
    }
    if (is_minus) output = output * (-1);
    return output;
}

double task05(double x0, double eps){ // ПРОТЕСТИРОВАТЬ
    int is_minus = 0;
    double output;
    //printf("ist sin: %lf\n", sin(x0));
    if (x0 < 0){
        is_minus = 1;
        x0 = fabs(x0);
    }
    if (x0 >= 2 * M_PI){
        x0 = fmod(x0, 2 * M_PI);
    }
    //printf("ist sin: %lf\n", sin(x0));
    if (x0 >= M_PI){
        is_minus = (is_minus + 1) % 2;
        x0 = fmod(x0, M_PI);
    }
    //printf("ist sin: %lf\n", sin(x0));
    //printf("x0:%lf\n", x0);
    if (x0 > 1){
        /*
        printf("ist sin / 2: %lf\n", sin(x0 / 2));
        printf("x0 / 2:%lf\n", x0 / 2);
        printf("cos: %lf\n", calculate_cos(x0 / 2, eps));
        printf("sin: %lf\n", calculate_sin(x0 / 2, eps));
        */
        output = 2 * calculate_cos(x0 / 2, eps) * calculate_sin(x0 / 2, eps);
    }
    else{
        output = calculate_sin(x0, eps);
    }
    if (is_minus) output = output * (-1);
    return output;
}

double calculate_cos(double x0, double eps){ // ПРОТЕСТИРОВАТЬ
    int i, chet;
    double output = 0;
    double slag = 1;
    for (i = 0, chet = 0;;i+=2, chet++){
        // printf("slag: %lf\n", slag);
        if (chet % 2 == 0){
            output += slag;
        }
        else {
            output -= slag;
        }
        // printf("output: %lf\n", output);
        slag = slag * x0 * x0;
        slag = slag / ((i + 1) * (i + 2));
        if (fabs(slag) < eps) break;
    }
    return output;
}

double calculate_sin(double x0, double eps){ // ПРОТЕСТИРОВАТЬ
    int i, chet;
    double output = 0;
    double slag = x0;
    for (i = 1, chet = 0;;i+=2, chet++){
        //printf("slag: %lf\n", slag);
        if (chet % 2 == 0){
            output += slag;
        }
        else {
            output -= slag;
        }
        //printf("output: %lf\n", output);
        slag = slag * x0 * x0;
        slag = slag / ((i + 1) * (i + 2));
        if (fabs(slag) < eps) break;
    }
    return output;
}

double task07(double x0, double eps){ // ПРОТЕСТИРОВАТЬ
    double chel_ch;
    double dr_ch;
    double output = 1;
    int i;
    if (x0 >= 0){
        chel_ch = floor(x0);
        dr_ch = x0 - chel_ch;
        for (i = 1; i <= chel_ch; i++){
            output *= M_E;
        }
    }
    else{
        chel_ch = ceil(x0);
        dr_ch = x0 - chel_ch;
        for (i = -1; i >= chel_ch; i--){
            output /=M_E;
        }
    }
    //printf("%lf %lf\n", chel_ch, dr_ch);
    dr_ch = calculate_exp(dr_ch, eps);
    return output * dr_ch;
}

double calculate_exp(double x0, double eps){
    int i;
    double output = 0;
    double slag = 1;
    for (i = 1; ;i++){
        //printf("slag: %lf\n", slag);
        //printf("output: %lf\n", output);
        output += slag;
        slag = slag * x0;
        slag = slag / i;
        if (fabs(slag) < eps) break;
    }
    return output;
}

double task08(double x0, double eps){ // ПРОТЕСТИРОВАТЬ ЭТО И ФУНКЦИИ НИЖЕ
    int b = 0;
    double ch;
    double a;
    double output;
    if (x0 >= 0.5){
        ch = st_2(x0, &b);
        a = x0 / ch;
        output = calculate_log(a, eps) + b * M_LN2;
        //printf("a: %lf b: %d\n", a, b);
    }
    else {
        a = x0;
        output = calculate_log(a, eps);
    }
    return output;
}

double st_2(double x, int *c){ // ПРОТЕСТИРОВАТЬ
    int d_x;
    double output = 1.;
    if (x >= 1.){
        d_x = x;
        output = 1;
        while (output <= d_x){
            output *= 2;
            *c += 1;
        }
        *c += 1;
        return 2 *output;
    }
    else { // предполагаем, что сюда меньше 0,5 не попадает
        *c = 1;
        output = 2;
        return output;
    }
}


double calculate_log(double z, double eps){ // ПРОТЕСТИРОВАТЬ
    double x = (z - 1) / (z + 1);
    int i;
    double output = 0;
    double slag = x;
    for (i = 1; ;i+= 2){
        output += slag / i;
        slag = slag * x * x;
        if (fabs(slag) < eps) break;
    }
    return 2 * output;
}