#include "asmerror.h"

#include <stdio.h>
#include <string.h>

static const char *STR_ERROR[] = {
    "Macro Error",
    "Syntax Error",
    "Label Error",
};

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
            at /home/mk41/mycpu/d16-asm/tests/src/macros.S line 11

        00000000:    mov %0 #$12lk
                            ^^^^^^
        Syntax Error: Invalid integer literal
    */
    if (estart < 0) {
        internal_err("estart passed with a value less than 0");
        return;
    }

    size_t indent = strspn(env->cur_line, " ");
    fprintf(stderr, "\n\033[1;37mAssembly resulted in an error\033[0;32m\n");
    fprintf(stderr, "    at %s line %lu\n", env->file, env->lineno);
    //for (struct From **f = env->from; *f; f++)
    //    fprintf(stderr, "    at %s line %lu", (*f)->file, (*f)->lineno);
    fprintf(stderr, "\n");
    fprintf(stderr, "\033[1;36m%08x:\033[0;37m    %.*s\033[1;35m%.*s\033[0;37m%s\n", env->address, (int)(estart - indent), env->cur_line + indent, (int)(1 + eend - estart), env->cur_line + estart, 1 + env->cur_line + eend);
    if (eend >= estart) {
        fprintf(stderr, "             %*s\033[1;31m", (int)(estart - indent), "");
        for (size_t i = estart - indent; i <= (eend - indent); i++)
            fprintf(stderr, "^");
    }
    
    fprintf(stderr, "\n\033[1;37m%s: %s\033[0;37m\n", STR_ERROR[t], msg);
}

void internal_err(char *msg) {
    fprintf(stderr, "Internal Error: %s\n", msg) ;
}