#ifndef ARRAY_H
#define ARRAY_H

#include "io_status.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

io_status t7_process_s(const char * s, char * s1, char * s2, const size_t len_s);
io_status t7_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r);
bool t7_start(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf);

#endif
