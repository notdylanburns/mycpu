#ifndef _ASMENV_H_GUARD_
#define _ASMENV_H_GUARD_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct ASM {
    uint32_t address; // can be set with !org directive
    uint16_t *words;
    size_t num_words;
    struct Label **labels;
    size_t num_labels;
    struct LabelPlaceholder **tbc;
    size_t num_placeholders;
    size_t lineno;
    char *file;
    char *cur_line;
};

extern bool add_words(struct ASM *env, uint16_t *words, size_t num);

#endif