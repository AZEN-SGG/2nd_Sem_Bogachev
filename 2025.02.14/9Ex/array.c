#include "array.h"


io_status process_s(const char* s, char* s1, char* s2, const size_t len_s)
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

io_status process_file(const char* f_in, const char* f_out, const char* s1, const char* s2, int* r)
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
            if (len_buf > 0 && buf[len_buf - 1] == '\n') buf[--len_buf] = '\0';
            is_approach = start(buf, s1, s2, len_s, len_buf);

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

bool start(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
    size_t char_s = sizeof(char);
    if (buf[0] == s2[0])
    {
        if (s1[0] == '1')
        {
            if (recursion(buf + char_s, s1, s2, len_s, len_buf - 1)) return true;
            else if (recursion(buf, s1 + char_s, s2 + char_s, len_s - 1, len_buf)) return true;
        }
        if (len_buf == 0 && len_s == 0) return true;
        return recursion(buf + char_s, s1 + char_s, s2 + char_s, len_s - 1, len_buf - 1);
    }
    if (s1[0] == '1') return recursion(buf, s1 + char_s, s2 + char_s, len_s - 1, len_buf);

    return false;
}

bool recursion(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
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
                    if (recursion(buf + (i + 1) * char_s, s1 + i * char_s, s2 + i * char_s, len_s - i,
                                  len_buf - (i + 1)))
                        return true;
                    else if (recursion(buf + i * char_s, s1 + (i + 1) * char_s, s2 + (i + 1) * char_s, len_s - (i + 1),
                                       len_buf - i))
                        return true;
                }
            }
            else
            {
                if (s1[i] == '1')
                {
                    return (recursion(buf + i * char_s, s1 + (i + 1) * char_s, s2 + (i + 1) * char_s, len_s - (i + 1),
                                      len_buf - i));
                    return true;
                }
                return false;
            }
        }

        if (i == (int)len_s) return true;
        return false;
    }
}
