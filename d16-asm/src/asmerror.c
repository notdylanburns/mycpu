#include "asmerror.h"

#include <stdio.h>
#include <string.h>

static const char *STR_ERROR[] = {
    "Macro Error",
    "Syntax Error",
    "Label Error",
    "Include Error",
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

    if (estart < 0) {
        internal_err("estart passed with a value less than 0");
        return;
    }

    size_t indent = strspn(env->cur_line, " ");
    fprintf(stderr, "\n\033[1;37mAssembly resulted in an error\033[0;32m\n");
    struct IncludedBy *by = env->by;
    while (by != NULL) {
        fprintf(stderr, "    at %s line %lu\n", by->fp, by->line);
        by = by->parent;
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "\033[1;36m%08x:\033[0;37m    %.*s\033[1;35m%.*s\033[0;37m%s\n", env->address, (int)(estart - indent), env->cur_line + indent, (int)(1 + eend - estart), env->cur_line + estart, 1 + env->cur_line + eend);
    if (eend >= estart) {
        fprintf(stderr, "             %*s\033[1;31m", (int)(estart - indent), "");
        for (size_t i = estart - indent; i <= (eend - indent); i++)
            fprintf(stderr, "^");
    }
    
    fprintf(stderr, "\n\033[1;37m%s: %s\033[1;31m\n", STR_ERROR[t], msg);
}

void internal_err(char *msg) {
    fprintf(stderr, "\033[1;37mInternal Error: \033[1;31m%s\033[0;37m\n", msg);
}

void fatal_err(char *fmt, ...) {
    fprintf(stderr, "\033[1;37md16asm: \033[1;31m");
    
    va_list arg;
    va_start(arg, fmt);

    vfprintf(stderr, fmt, arg);
    va_end(arg);

    fprintf(stderr, "\033[0;37m\n");
}