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
            bool is_approach = process_string(buf, s1, s2, t, len_s, len_buf);

            if (is_approach)
            {
                i++;
                if ((len_buf > 0) && (buf[len_buf - 1] == '\n')) buf[len_buf - 1] = '\0';
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
        if (s1[0] == '1')
        {
            int last_space = -1, i;
            size_t per_sim = 0; // Percent of similarity
            for (i = 0; i < (int)len_buf; ++i)
            {
                if (is_space(buf[i], t))
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

bool is_space(char symbol, const char* t)
{
    int i;
    for (i = 0; t[i] != '\0'; ++i)
    {
        if (t[i] == symbol) return true;
    }

    return false;
}
