#ifndef _MATRIX_H_GUARD_
#define _MATRIX_H_GUARD_

#include <stdbool.h>

#include "address.h"

struct AddrMode {
    const char *X;
    bool V;
};

struct Opcode {
    const char *N;
    struct AddrMode M[ADDR_MODES];
};

extern const int MATRIX_LEN;
extern const struct Opcode MATRIX[];

#endif