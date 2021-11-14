#ifndef _LABEL_H_GUARD_
#define _LABEL_H_GUARD_

#include <stdbool.h>

#include "asmenv.h"

enum LabelOpts {
    LO_16,
    HI_16,
    BITS_32,
};

struct Label {
    char *label;
    uint32_t address; 
};

struct LabelPlaceholder {
    uint32_t address;
    size_t line;
    size_t word;
    char *label;
    enum LabelOpts opts;
};

extern bool add_label(struct ASM *env, char *l);
extern bool get_label(struct ASM *env, char *l, uint32_t *address);
extern bool add_label_ph(struct ASM *env, char *l, size_t line, size_t word, enum LabelOpts opts);

#endif