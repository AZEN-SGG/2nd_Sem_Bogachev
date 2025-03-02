#include <stdio.h>
#include <time.h>
#include <string.h>
#include "io_status.h"
#include "solve.h"

io_status task1(const char* f_in, const char* f_out, const char* s, int* res);

io_status task1(const char* f_in, const char* f_out, const char* s, int* res)
{
    if (s == NULL) return ERROR_PATTERN;
    else
    {
        size_t len_s = strlen(s);
        io_status status;
        char s1[len_s + 1], s2[len_s + 1];
        memset(s1, 0, len_s + 1);
        memset(s2, 0, len_s + 1);
        status = t1_process_s(s, s1, s2, len_s);
        if (status != SUCCESS) return status;
        return t1_process_file(f_in, f_out, s1, s2, res);
    }
}

int main(int argc, char* argv[])
{
    int task = 1;
    io_status ret;
    const char *f_in, *f_out, *s;
    int res = 0;
    double t;
    if (argc != 4)
    {
        printf("Usage: %s <f_in> <f_out> <s>\n", argv[0]);
        return 1;
    }
    f_in = argv[1];
    f_out = argv[2];
    s = argv[3];
    t = clock();
    ret = task1(f_in, f_out, s, &res);
    t = (clock() - t) / CLOCKS_PER_SEC;
    switch (ret)
    {
    case SUCCESS:
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
        break;
    case ERROR_OPEN:
        printf("Can not open %s\n", f_out);
        return 1;
    case ERROR_READ:
        printf("Can not read %s\n", f_out);
        return 2;
    case ERROR_PATTERN:
        printf("Error in pattern %s\n", s);
        return 3;
    }
    return 0;
}
