#ifndef _ASMSTRING_H_GUARD_
#define _ASMSTRING_H_GUARD_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

enum STR_TYPE {
    STR_WIDE,
    STR_BYTE,
};

extern bool word_len(char *value, size_t *len, enum STR_TYPE t);
extern bool strval(char *value, uint16_t *v, enum STR_TYPE t);
extern bool strraw(char *value, char **v);

#endif