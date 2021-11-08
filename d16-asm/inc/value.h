#ifndef _VALUE_H_GUARD_
#define _VALUE_H_GUARD_

#include <stdbool.h>
#include <stdint.h>

enum VAL_TYPE {
    V_IMM,      // $nnnn (16 bit literal)
    V_ADR,      // *$nnnn or *$nnnnnnnn (16 or 32 bit address)
    V_REG,      // %n (register)
    V_LBL,      // label, abcdef
};

extern enum VAL_TYPE get_type(char *value);
extern bool value16(char *value, uint16_t *v);
extern bool value32(char *value, uint32_t *v);
extern bool get_register(char n, uint8_t *r);

#endif