#include "asmerror.h"

#include <stdio.h>
#include <string.h>

static const char *STR_ERROR[] = {
    "Macro Error",
    "Syntax Error",
    "Label Error",
};

/*
struct AsmError {
    size_t line_no;
    char **line;
    char *file;
    enum ERROR_TYPE t;
    uint32_t address;
    char *msg;
};
*/

long start_of(char *line, size_t w) {
    size_t count = 0;
    bool broken = false;
    for (char *c = line; *c; c++) {
        if (broken && *c == ' ') {
            count++;
            broken = false;
        }

        if (*c != ' ') {
            broken = true;
            if (count == w)
                return (c - line);
        }
    }
    return -1;
}

long end_of(char *line, size_t w) {
    long start = start_of(line, w);
    if (start < 0)
        return start;

    for (char *c = line + start + 1; *c; c++) {
        if (*c == ' ')
            return (c - line) - 1;
    }
    return strlen(line) - 1;
}

void print_err(struct ASM *env, enum ERROR_TYPE t, char *msg, size_t estart, size_t eend) {
    /*
        Assembly resulted in an error
            at stdio.inc line 3
            at main.s line 1
        =============================
        00000000:    mov %0 #$12lk
                            ^^^^^^
        Syntax Error: Invalid integer literal
    */
    if (estart < 0) {
        internal_err("estart passed with a value less than 0");
        return;
    }

    size_t indent = strspn(env->cur_line, " ");
    fprintf(stderr, "Assembly resulted in an error\n");
    fprintf(stderr, "    at %s line %lu\n", env->file, env->lineno);
    //for (struct From **f = env->from; *f; f++)
    //    fprintf(stderr, "    at %s line %lu", (*f)->file, (*f)->lineno);
    fprintf(stderr, "=============================\n");
    fprintf(stderr, "%08x:    %s\n", env->address, env->cur_line + indent);
    if (eend >= estart) {
        fprintf(stderr, "             %*s", (int)(estart - indent), "");
        for (size_t i = estart - indent; i <= (eend - indent); i++)
            fprintf(stderr, "^");
    }
    
    fprintf(stderr, "\n%s: %s\n", STR_ERROR[t], msg);
}

void internal_err(char *msg) {
    fprintf(stderr, "Internal Error: %s\n", msg) ;
}