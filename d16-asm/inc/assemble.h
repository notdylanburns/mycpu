#ifndef _ASSEMBLE_H_GUARD_
#define _ASSEMBLE_H_GUARD_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "line.h"

typedef struct {
    char *str;
    char **args;
} instr_t;

extern uint16_t *assemble(char *src, size_t len);

#endif