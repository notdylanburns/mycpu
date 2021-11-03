#ifndef _OP_H_GUARD_
#define _OP_H_GUARD_

#include "arg.h"

struct opconf_t {
    char *opc;
    uint8_t num_args;
    enum argtype_t *args;
};

#define Op(o, n, a) (struct opconf_t){ .opc = #o, .num_args = n, .args = a }

extern struct opconf_t OPMATRIX[];

#endif