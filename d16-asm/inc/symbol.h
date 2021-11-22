#ifndef _SYMBOL_H_GUARD_
#define _SYMBOL_H_GUARD_

#include <stdbool.h>

#include "asmenv.h"

extern bool add_symbol(struct ASM *env, char *sym);
extern bool get_symbol(struct ASM *env, char *sym);
extern bool remove_symbol(struct ASM *env, char *sym);

#endif