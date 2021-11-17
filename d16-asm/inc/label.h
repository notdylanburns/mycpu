#ifndef _LABEL_H_GUARD_
#define _LABEL_H_GUARD_

#include <stdbool.h>

#include "asmenv.h"

extern bool add_label(struct ASM *env, char *l);
extern bool get_label(struct ASM *env, char *l, uint32_t *address);
extern bool add_label_ph(struct ASM *env, char *l, size_t line, size_t word, enum LabelOpts opts);

#endif