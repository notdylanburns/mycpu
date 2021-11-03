#ifndef _ARG_H_GUARD_
#define _ARG_H_GUARD_

#include <stdlib.h>
#include <stdint.h>

enum argtype_t {
    ARG_R,
    ARG_IMM,
    ARG_M16,
    ARG_A16,
};

struct arg_t {
    enum argtype_t type;
    union {
        uint8_t r;      // 0-f prefixed by %
        uint16_t imm;   // 16 bit int prefixed by ' 
        uint16_t m16;   // 16 bit address prefixed by * 
        uint16_t a16;   // 16 bit int
    } value;
};

extern struct arg_t *new_arg(enum argtype_t type);

#endif