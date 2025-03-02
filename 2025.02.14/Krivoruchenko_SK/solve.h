#ifndef SOLVE_H
#define SOLVE_H

#include "io_status.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ========== TASK 1 (Исходный код из первого задания) ========== */
io_status t1_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t1_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t1_process_string(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

/* ========== TASK 2 ========== */
io_status t2_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t2_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t2_process_string(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

/* ========== TASK 3 ========== */
io_status t3_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t3_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, const char *t, int *r);
bool      t3_process_string(const char *buf, const char *s1, const char *s2, const char *t,
                              const size_t len_s, const size_t len_buf);
bool      t3_is_space(char symbol, const char *t);

/* ========== TASK 4 ========== */
io_status t4_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t4_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, const char *t, int *r);
bool      t4_process_string(const char *buf, const char *s1, const char *s2, const char *t,
                              const size_t len_s, const size_t len_buf);

/* ========== TASK 6 ========== */
io_status t6_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t6_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t6_process_string(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

/* ========== TASK 7 ========== */
io_status t7_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t7_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t7_start(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

/* ========== TASK 8 ========== */
io_status t8_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t8_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t8_recursion(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

/* ========== TASK 9 ========== */
io_status t9_process_s(const char *s, char *s1, char *s2, const size_t len_s);
io_status t9_process_file(const char *f_in, const char *f_out, const char *s1, const char *s2, int *r);
bool      t9_start(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);
bool      t9_recursion(const char *buf, const char *s1, const char *s2, const size_t len_s, const size_t len_buf);

#endif // SOLVE_H
