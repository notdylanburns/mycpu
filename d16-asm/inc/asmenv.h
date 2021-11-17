#ifndef _ASMENV_H_GUARD_
#define _ASMENV_H_GUARD_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "asminclude.h"

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

struct ASM {
    uint32_t address; // can be set with !org directive
    uint16_t *words;
    size_t num_words;
    struct Label **labels;
    size_t num_labels;
    struct LabelPlaceholder **tbc;
    size_t num_placeholders;
    char **lines;
    size_t num_lines;
    char *cur_line;
    size_t abs_line;
    struct IncludedBy *by;
};

extern bool add_words(struct ASM *env, uint16_t *words, size_t num);
extern bool add_lines(struct ASM *env, char **lines, size_t num);

#endif