#ifndef _ASMERROR_H_GUARD_
#define _ASMERROR_H_GUARD_

#include <stdint.h>

#include "asmenv.h"

enum ERROR_TYPE {
    MACRO_ERROR,
    SYNTAX_ERROR,
    LABEL_ERROR,
    INCLUDE_ERROR,
};

extern long start_of(char *line, size_t w);
extern long end_of(char *line, size_t w);
extern void print_err(struct ASM *env, enum ERROR_TYPE t, char *msg, size_t estart, size_t eend);
extern void internal_err(char *msg);

#endif