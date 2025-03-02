#include "solve.h"


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
            if (buf[len_buf - 1] == '\n') buf[--len_buf] = '\0';
            is_approach = t8_recursion(buf, s1, s2, len_s, len_buf);

            if (is_approach)
            {
                i++;
                fprintf(fw, "%s\n", buf);
            }
        }

        *r = i;
        fclose(fw);
    }

    fclose(fp);

    return SUCCESS;
}

bool t8_recursion(const char* buf, const char* s1, const char* s2, const size_t len_s, const size_t len_buf)
{
	if (len_s == 0) return (len_buf == 0);
	else if (len_buf == 0) return false; 
    
	if (buf[0] == s2[0])
	{
                if (s1[0] == '1') if (t8_recursion(buf + 1, s1, s2, len_s, len_buf - 1)) return true;
                if (t8_recursion(buf + 1, s1 + 1, s2 + 1, len_s - 1, len_buf - 1)) return true;
	}
	return false;
}
