#include "solve.h"

/* ======================================= */
/* ========== TASK 1 (Задание 1) ========= */
/* ======================================= */

io_status t1_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    size_t i;
    int j;
    for (i = 0, j = 0; i < len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = 0;
                s2[j++] = s[++i];
            }
        }
        else if ((s[i] == '^') && (i == 0))
        {
            s1[j] = '1';
            s2[j++] = s[++i];
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t1_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach = t1_process_string(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                /* Исправленная проверка на '\n': */
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);
    return SUCCESS;
}

bool t1_process_string(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    if (len_buf < len_s) return false;

    if (s1[0] == '1')
    {
        size_t i;
        for (i = 0; i < len_s; ++i)
        {
            if (buf[i] != s2[i]) return false;
        }
    }
    else
    {
        char* s_pointer = strstr(buf, s2);
        if (!s_pointer) return false;
    }

    return true;
}

/* ======================================= */
/* ========== TASK 2 (Задание 2) ========= */
/* ======================================= */

io_status t2_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    size_t i;
    int j;
    for (i = 0, j = 0; i < len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = 0;
                s2[j++] = s[++i];
            }
        }
        else if ((s[i] == '$') && (i + 1 == len_s))
        {
            if (j != 0)
            {
                s1[j - 1] = '1';
            }
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t2_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            /* Исправленная проверка на '\n' + уменьшение len_buf: */
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';

            is_approach = t2_process_string(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                /* Здесь снова, если вдруг ещё раз проверяется: */
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);
    return SUCCESS;
}

bool t2_process_string(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    if (len_buf < len_s) return false;

    if (s1[len_s - 1] == '1')
    {
        size_t i;
        /* Проверка с конца строки */
        for (i = len_buf - 1; i > len_buf - len_s - 1; --i)
        {
            if (buf[i] != s2[i - (len_buf - len_s)]) return false;
        }
    }
    else
    {
        char* s_pointer = strstr(buf, s2);
        if (!s_pointer) return false;
    }

    return true;
}

/* ======================================= */
/* ========== TASK 3 (Задание 3) ========= */
/* ======================================= */

io_status t3_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    size_t i;
    int j;
    for (i = 0, j = 0; i < len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == len_s) return ERROR_PATTERN;
            else if ((i == 0) && (s[i + 1] == '<'))
            {
                s1[j] = '1';
                i++;
            }
            else
            {
                if (s1[j] != '1') s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else
        {
            if (s1[j] != '1') s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t3_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, const char* t, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach = t3_process_string(buf, s1, s2, t, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);
    return SUCCESS;
}

bool t3_process_string(const char* buf, const char* s1, const char* s2, const char* t,
                       const size_t len_s, const size_t len_buf)
{
    if (len_buf < len_s) return false;
    else
    {
        if (s1[0] == '1')
        {
            int last_space = -1, i;
            size_t per_sim = 0; // Percent of similarity
            for (i = 0; i < (int)len_buf; ++i)
            {
                if (t3_is_space(buf[i], t))
                {
                    last_space = i;
                    per_sim = 0;
                }
                else
                {
                    if (buf[i] == s2[per_sim])
                    {
                        if ((i == last_space + 1) || (per_sim))
                        {
                            if (++per_sim == len_s)
                            {
                                return true;
                            }
                        }
                    }
                    else
                    {
                        per_sim = 0;
                    }
                }
            }

            return false;
        }
        else
        {
            if (strstr(buf, s2)) return true;
            else return false;
        }
    }
}

bool t3_is_space(char symbol, const char* t)
{
    int i;
    for (i = 0; t[i] != '\0'; ++i)
    {
        if (t[i] == symbol) return true;
    }

    return false;
}

/* ======================================= */
/* ========== TASK 4 (Задание 4) ========= */
/* ======================================= */

io_status t4_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    size_t i;
    int j;
    for (i = 0, j = 0; i < len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == len_s) return ERROR_PATTERN;
            else if ((i == len_s - 2) && (s[i + 1] == '>'))
            {
                if (j > 0)
                {
                    s1[j++ - 1] = '1';
                }
                else
                {
                    s1[j++] = '1';
                }
            }
            else
            {
                s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t4_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, const char* t, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';
            is_approach = t4_process_string(buf, s1, s2, t, len_s, len_buf);

            if (is_approach)
            {
                i++;
                /* Проверка повторно (если была) */
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t4_process_string(const char* buf, const char* s1, const char* s2, const char* t,
                       const size_t len_s, const size_t len_buf)
{
    if (len_buf < len_s) return false;
    else
    {
        if (s1[len_s - 1] == '1')
        {
            size_t i, last_space = len_buf, per_sim = len_s - 1; // Percent of similarity
            /* Обратный цикл, используя size_t */
            for (i = len_buf - 1; i < i + 2; --i)
            {
                if (t3_is_space(buf[i], t)) // используем t3_is_space, чтобы логику не менять
                {
                    last_space = i;
                    per_sim = len_s - 1;
                }
                else
                {
                    if (buf[i] == s2[per_sim])
                    {
                        if ((i == last_space - 1) || ((per_sim + 1) < len_s))
                        {
                            if (per_sim-- == 0)
                            {
                                return true;
                            }
                        }
                    }
                    else
                    {
                        per_sim = len_s - 1;
                    }
                }
            }

            return false;
        }
        else
        {
            if (strstr(buf, s2)) return true;
            else return false;
        }
    }
}

/* ======================================= */
/* ========== TASK 6 (Задание 6) ========= */
/* ======================================= */

io_status t6_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    size_t i;
    int j;
    for (i = 0, j = 0; i < len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else if (s[i] == '.')
        {
            s1[j] = '1';
            s2[j++] = '.';
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t6_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';
            is_approach = t6_process_string(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                /* Повторная проверка на всякий случай */
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t6_process_string(const char* buf, const char* s1, const char* s2, const size_t len_s,
                       const size_t len_buf)
{
    if (len_buf < len_s) return false;
    if (s1[0] == '1' || buf[0] == s2[0])
    {
        int j;
        for (j = 1; j < (int)len_s; ++j)
        {
            if ((buf[j] != s2[j]) && (s1[j] == '0'))
            {
                break;
            }
        }

        if (j == (int)len_s && j == (int)len_buf) return true;
    }

    return false;
}

/* ======================================= */
/* ========== TASK 7 (Задание 7) ========= */
/* ======================================= */

io_status t7_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    int i;
    int j;
    for (i = 0, j = 0; i < (int)len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == (int)len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else if ((s[i] == '?') && (j != 0))
        {
            s1[j - 1] = '1';
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t7_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';
            is_approach = t7_start(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t7_start(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    bool is_approach = false;
    size_t char_s = sizeof(char);
    if (len_s == 0)
    {
        if (len_buf == 0) return true;
        return false;
    }
    else if (len_buf == 0) return false;

    if (buf[0] == s2[0])
    {
        is_approach = t7_start(buf + char_s, s1 + char_s, s2 + char_s, len_s - 1, len_buf - 1);
        if (is_approach) return true;
    }
    if (s1[0] == '1')
    {
        is_approach = t7_start(buf, s1 + char_s, s2 + char_s, len_s - 1, len_buf);
        if (is_approach) return true;
    }

    return false;
}

/* ======================================= */
/* ========== TASK 8 (Задание 8) ========= */
/* ======================================= */

io_status t8_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    int i, j;
    for (i = 0, j = 0; i < (int)len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == (int)len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else if ((s[i] == '+') && (j != 0))
        {
            s1[j - 1] = '1';
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t8_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';
            is_approach = t8_start(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t8_start(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    size_t char_s = sizeof(char);
    if (buf[0] == s2[0])
    {
        if (s1[0] == '1')
        {
            if (t8_recursion(buf + char_s, s1, s2, len_s, len_buf - 1)) return true;
        }
        if (len_buf == 0 && len_s == 0) return true;
        if (t8_recursion(buf + char_s, s1 + char_s, s2 + char_s, len_s - 1, len_buf - 1)) return true;
    }

    return false;
}

bool t8_recursion(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    size_t char_s = sizeof(char);
    if (len_s == 0) return true;
    else if (len_buf == 0) return false;
    else
    {
        int i;
        for (i = 0; i < (int)len_buf; ++i)
        {
            if (buf[i] == s2[i])
            {
                if (s1[i] == '1')
                {
                    if (t8_recursion(buf + (i + 1) * char_s, s1 + i * char_s, s2 + i * char_s, len_s - i,
                                     len_buf - (i + 1)))
                        return true;
                }
                if ((i + 1) == (int)len_s)
                {
                    if (i + 1 == (int)len_buf) return true;
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        return false;
    }
}

/* ======================================= */
/* ========== TASK 9 (Задание 9) ========= */
/* ======================================= */

io_status t9_process_s(const char* s, char* s1, char* s2, const size_t len_s)
{
    int i, j;
    for (i = 0, j = 0; i < (int)len_s; ++i)
    {
        if (s[i] == '\\')
        {
            if (i + 1 == (int)len_s) return ERROR_PATTERN;
            else
            {
                s1[j] = '0';
                s2[j++] = s[++i];
            }
        }
        else if ((s[i] == '*') && (j != 0))
        {
            s1[j - 1] = '1';
        }
        else
        {
            s1[j] = '0';
            s2[j++] = s[i];
        }
    }

    s2[j] = '\0';

    return SUCCESS;
}

io_status t9_process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
{
    FILE* fp = fopen(f_in, "r");
    if (!fp) return ERROR_OPEN;
    else
    {
        char buf[LEN] = {0};
        size_t len_s = strlen(s2);
        FILE* fw = fopen(f_out, "w");
        int i;

        if (!fw)
        {
            fclose(fp);
            return ERROR_OPEN;
        }
        for (i = 0; fgets(buf, sizeof(buf), fp);)
        {
            size_t len_buf = strlen(buf);
            bool is_approach;
            if (len_buf > 0 && buf[len_buf - 1] == '\n')
                buf[--len_buf] = '\0';
            is_approach = t9_start(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if (len_buf > 0 && buf[len_buf - 1] == '\n')
                    buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t9_start(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    size_t char_s = sizeof(char);
    if (buf[0] == s2[0])
    {
        if (s1[0] == '1')
        {
            if (t9_recursion(buf + char_s, s1, s2, len_s, len_buf - 1)) return true;
            else if (t9_recursion(buf, s1 + char_s, s2 + char_s, len_s - 1, len_buf)) return true;
        }
        if (len_buf == 0 && len_s == 0) return true;
        return t9_recursion(buf + char_s, s1 + char_s, s2 + char_s, len_s - 1, len_buf - 1);
    }
    if (s1[0] == '1') return t9_recursion(buf, s1 + char_s, s2 + char_s, len_s - 1, len_buf);

    return false;
}

bool t9_recursion(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    size_t char_s = sizeof(char);
    if (len_s == 0)
    {
        if (len_buf == 0) return true;
        return false;
    }
    else if (len_buf == 0) return false;
    else
    {
        int i;
        for (i = 0; i < (int)len_buf; ++i)
        {
            if (buf[i] == s2[i])
            {
                if (s1[i] == '1')
                {
                    if (t9_recursion(buf + (i + 1) * char_s, s1 + i * char_s, s2 + i * char_s,
                                     len_s - i, len_buf - (i + 1)))
                        return true;
                    else if (t9_recursion(buf + i * char_s, s1 + (i + 1) * char_s, s2 + (i + 1) * char_s,
                                          len_s - (i + 1), len_buf - i))
                        return true;
                }
            }
            else
            {
                if (s1[i] == '1')
                {
                    /* Здесь два return подряд в оригинале - оставляем как есть */
                    return (t9_recursion(buf + i * char_s, s1 + (i + 1) * char_s, s2 + (i + 1) * char_s,
                                         len_s - (i + 1), len_buf - i));
                    return true;
                }
                return false;
            }
        }

        if (i == (int)len_s) return true;
        return false;
    }
}
