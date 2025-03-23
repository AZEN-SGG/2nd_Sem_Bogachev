#include "array.h"


io_status process_s(const char* s, char* s1, char* s2, const size_t len_s)
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
                    s1[j++-1] = '1';
                } else
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

io_status process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, const char* t, int* r)
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
            if (buf[len_buf - 1] == '\n') buf[--len_buf] = '\0';
            is_approach = process_string(buf, s1, s2, t, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if (buf[len_buf - 1] == '\n') buf[len_buf - 1] = '\0';
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool process_string(const char* buf, const char* s1, const char* s2, const char* t, const size_t len_s,
                    const size_t len_buf)
{
    if (len_buf < len_s) return false;
    else
    {
        if (s1[len_s - 1] == '1')
        {
            size_t i, last_space = len_buf, per_sim = len_s - 1; // Percent of similarity
            for (i = len_buf - 1; i < i + 2; --i) // i < i + 2 - size_t всегда положительный -> закончится когда случится переход от -1 к -2, а они сильно больше 0
            {
                if (is_space(buf[i], t))
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

bool is_space(char symbol, const char* t)
{
    int i;
    for (i = 0; t[i] != '\0'; ++i)
    {
        if (t[i] == symbol) return true;
    }

    return false;
}
