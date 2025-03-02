#include "array.h"


io_status process_s(const char * s, char * s1, char * s2, const size_t len_s) {
	size_t i;
	int j;
	for (i = 0, j = 0; i < len_s; ++i) {
		if (s[i] == '\\') {
			if (i + 1 == len_s) return ERROR_PATTERN;
			else {
				s1[j] = 0;
				s2[j++] = s[++i];
			}
		} else if ((s[i] == '^') && (i == 0)) {
			s1[j] = '1';
			s2[j++] = s[++i];
		} else {
			s1[j] = '0';
			s2[j++] = s[i];
		}
	}

	s2[j] = '\0';

	return SUCCESS;
}

io_status process_file(const char * f_in, const char * f_out, const char * s1, const char * s2, int * r) {
	FILE * fp = fopen(f_in, "r");
	if (!fp) return ERROR_OPEN;
	else {
		char buf[LEN] = {0};
		size_t len_s = strlen(s2);
		FILE * fw = fopen(f_out, "w");
		int i;

		if (!fw) {fclose(fp); return ERROR_OPEN;}
		for (i = 0; fgets(buf, sizeof(buf), fp);) {
			size_t len_buf = strlen(buf);
			bool is_approach = process_string(buf, s1, s2, len_s, len_buf);

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

bool process_string(const char * buf, const char * s1, const char * s2, const size_t len_s, const size_t len_buf) {	
	if (len_buf < len_s) return false;
	
	if (s1[0] == '1') {
		size_t i;
		for (i = 0; i < len_s; ++i) {
			if (buf[i] != s2[i]) return false;
		}
	} else {
		char * s_pointer = strstr(buf, s2);
		if (!s_pointer) return false;
	}

	return true;
}

