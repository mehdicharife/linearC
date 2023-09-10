#include <stdlib.h>
#include <stdbool.h>
#include "../include/get_untill.h"
#include "../include/utils.h"



char* get_untill_delim(FILE* fp, char* delimiters, int delimiters_count, char* stop_cause_delimiter) {
    if(fgetc(fp) == EOF) { return NULL; } else { fseek(fp, -1, SEEK_CUR); }

    int char_count = 0;
    char curr_char;
    int spaces_before_count = 0;
    int spaces_after_count = 0;
    bool inside_quotes = false;
    char* stop_cause_delimiter_safe = (stop_cause_delimiter == NULL) ? malloc(sizeof(char)) : stop_cause_delimiter;
    int offset;


    do {
        curr_char = fgetc(fp);
        if(((get_char_index(delimiters, delimiters_count, curr_char) != -1) && !inside_quotes) || 
             curr_char == EOF) { *stop_cause_delimiter_safe = curr_char;  break; }

        if(curr_char == '\"') { inside_quotes = !inside_quotes; }
        if(curr_char == ' ') {
            if(char_count == 0) {
                spaces_before_count++;
                continue;
            }
            spaces_after_count++;
        } else {
            if(spaces_after_count) {
                spaces_after_count = 0;
            }
        }

        char_count++;
        
    } while(true);
    
    char_count = char_count - spaces_after_count;
    offset = -char_count - spaces_after_count - (feof(fp) ? 0 : 1);
    int seeking_successfull = !fseek(fp, offset, SEEK_CUR);
    if(!seeking_successfull) { perror("couldn't seek"); }
   

    char* ret = malloc((char_count + 1)*sizeof(char));
    fgets(ret, char_count + 1, fp);
    fgetc(fp);
    return ret;
}


char* csv_get_untill_delim(FILE* fp, char* stop_cause_delimiter) {
    static size_t delimiters_count = 2;
    static char* delimiters = NULL;
    if(delimiters == NULL) {
         delimiters = malloc(delimiters_count*sizeof(char));
         delimiters[0] = ',';
         delimiters[1] = '\n';
    }

    return get_untill_delim(fp, delimiters, delimiters_count, stop_cause_delimiter);
}


void set_dimensions(FILE* fp, size_t* prow, size_t* pcol) {
    rewind(fp);

    char stop_cause;
    char* curr_str;
    *pcol = 0;
    *prow = 0;

    while((curr_str = csv_get_untill_delim(fp, &stop_cause)) != NULL) {
        if(stop_cause == '\n' || stop_cause == EOF) { *prow = *prow + 1; }
    }
    rewind(fp);

    while((curr_str = csv_get_untill_delim(fp, &stop_cause)) != NULL) {
        *pcol = *pcol + 1;
        if(stop_cause == EOF || stop_cause == '\n') {
            break;
        }
    }

    rewind(fp);
}