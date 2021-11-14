#ifndef _PARSE_H_GUARD_
#define _PARSE_H_GUARD_

#include <stdint.h>
#include <stdbool.h>

#include "asmenv.h"

extern bool parse_imm(struct ASM *env, uint16_t *word, char *w, size_t index);
extern bool parse_a16(struct ASM *env, uint16_t *word, char *w, size_t index);
extern bool parse_a32(struct ASM *env, uint32_t *dword, char *w, size_t index);

#endif