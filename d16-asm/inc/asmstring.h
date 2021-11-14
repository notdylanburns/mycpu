#ifndef _ASMSTRING_H_GUARD_
#define _ASMSTRING_H_GUARD_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

extern bool word_len(char *value, size_t *len);
extern bool strval(char *value, uint16_t *v);

#endif