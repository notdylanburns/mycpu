#ifndef _UTILS_H_GUARD_
#define _UTILS_H_GUARD_

#include <stdlib.h>
#include <stdbool.h>

#include "asmerror.h"

#define STARTOF(n) start_of(env->cur_line, n)
#define ENDOF(n) end_of(env->cur_line, n)

extern bool add_char(char **s, char c);
extern bool add_arg(char *arg, char ***argv, size_t *argc);

#endif