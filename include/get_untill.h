#include <stdio.h>

char* get_untill_delim(FILE* fp, char* delimiters, int delimiters_count, char* stop_cause);
char* csv_get_untill_delim(FILE* fp, char* stop_cause);
void set_dimensions(FILE* fp, size_t* pcol, size_t* prow);