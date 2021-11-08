#ifndef _ASMENV_H_GUARD_
#define _ASMENV_H_GUARD_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct Label {
    char *label;
    uint32_t address; 
};

struct LabelPlaceholder {
    uint32_t address;
    char *label;
    uint8_t bits; // 16 or 32 
};

struct ASM {
    uint32_t address; // can be set with !org directive
    uint16_t *words;
    size_t num_words;
    struct Label **labels;
    size_t num_labels;
    struct LabelPlaceholder **tbc;
    size_t num_placeholders;
};

extern bool add_words(struct ASM *env, uint16_t *words, size_t num);
extern bool add_label(struct ASM *env, char *l);
extern bool get_label(struct ASM *env, char *l, uint32_t *address);
extern bool add_label_ph(struct ASM *env, char *l, uint8_t bits);

#endif