#include "parse.h"

#include <stdio.h>

#include "value.h"

bool parse_imm(struct ASM *env, uint16_t *word, char *w) {
    (void)env;
    switch (get_type(w)) {
        case V_IMM:
            if (!value16(w, word)) {
                fprintf(stderr, "Syntax Error: Invalid constant: %s\n", w);
                return false;
            }
            return true;
        
        default:
            fprintf(stderr, "Syntax Error: %s expected immediate argument\n", w);
            return false;
    }
}

bool parse_a16(struct ASM *env, uint16_t *word, char *w) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value16(w + 1, word)) {
                fprintf(stderr, "Syntax Error: Invalid address: %s\n", w);
                return false;
            }
            return true;

        case V_LBL:
            uint32_t dword;
            if (!get_label(env, w, &dword)) {
                if (!add_label_ph(env, w, 16)) {
                    fprintf(stderr, "malloc failed...\n");
                    return false;
                }
            } else
                *word = (uint16_t)(dword & 0x0000ffff);
            return true;
        
        default:
            fprintf(stderr, "Syntax Error: %s expected address argument\n", w);
            return false;
    }
}

bool parse_a32(struct ASM *env, uint32_t *dword, char *w) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value32(w + 1, dword)) {
                fprintf(stderr, "Syntax Error: Invalid address: %s\n", w);
                return false;
            }
            return true;

        case V_LBL:
            if (!get_label(env, w, dword))
                if (!add_label_ph(env, w, 32)) {
                    fprintf(stderr, "malloc failed...\n");
                    return false;
                }
            return true;
        
        default:
            fprintf(stderr, "Syntax Error: %s expected address argument\n", w);
            return false;
    }
}