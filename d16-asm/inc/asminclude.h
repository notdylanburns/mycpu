#ifndef _ASMINCLUDE_H_GUARD_
#define _ASMINCLUDE_H_GUARD_

#include <stdlib.h>

struct IncludedBy {
    char *fp;
    struct IncludedBy *parent;
    size_t n;
    size_t line;
    size_t remaining;
};

extern struct IncludedBy *new_include(char *filepath, size_t n, size_t num_lines);
extern void destroy_include(struct IncludedBy *by);
extern size_t get_lineno(struct IncludedBy *by);

#endif