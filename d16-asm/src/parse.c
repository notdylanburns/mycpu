#include "parse.h"

#include <stdio.h>

#include "asmenv.h"

#include "asmerror.h"
#include "label.h"
#include "value.h"
#include "utils.h"

struct ASM;

bool parse_imm(struct ASM *env, uint16_t *word, char *w, size_t index) {
    uint32_t dword = 0;
    switch (get_type(w)) {
        case V_IMM:
            if (!value16(w + 1, word)) {
                print_err(env, SYNTAX_ERROR, "Invalid integer literal", STARTOF(index), ENDOF(index));
                return false;
            }
            return true;

        case V_LLO:
            if (!get_label(env, w + 1, &dword)) {
                if (!add_label_ph(env, w + 1, env->by->line, index, LO_16)) {
                    internal_err("malloc failed...");
                    return false;
                }
            } else
                *word = (uint16_t)(dword & 0x0000ffff);
            return true;

        case V_LHI:
            if (!get_label(env, w + 1, &dword)) {
                if (!add_label_ph(env, w + 1, env->by->line, index, HI_16)) {
                    internal_err("malloc failed...");
                    return false;
                }
            } else
                *word = (uint16_t)((dword & 0xffff0000) >> 16);
            return true;
        
        default:
            print_err(env, SYNTAX_ERROR, "Expected immediate argument", STARTOF(index), ENDOF(index));
            return false;
    }
}

bool parse_a16(struct ASM *env, uint16_t *word, char *w, size_t index) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value16(w, word)) {
                print_err(env, SYNTAX_ERROR, "Invalid address literal", STARTOF(index), ENDOF(index));
                return false;
            }
            return true;

        case V_LBL:
            uint32_t dword;
            if (!get_label(env, w, &dword)) {
                if (!add_label_ph(env, w, env->by->line, index, LO_16)) {
                    internal_err("malloc failed...");
                    return false;
                }
            } else
                *word = (uint16_t)(dword & 0x0000ffff);
            return true;
        
        default:
            print_err(env, SYNTAX_ERROR, "Expected address argument", STARTOF(index), ENDOF(index));
            return false;
    }
}

bool parse_a32(struct ASM *env, uint32_t *dword, char *w, size_t index) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value32(w, dword)) {
                print_err(env, SYNTAX_ERROR, "Invalid address literal", STARTOF(index), ENDOF(index));
                return false;
            }
            return true;

        case V_LBL:
            if (!get_label(env, w, dword))
                if (!add_label_ph(env, w, env->by->line, index, BITS_32)) {
                    internal_err("malloc failed...");
                    return false;
                }
            return true;
        
        default:
            print_err(env, SYNTAX_ERROR, "Expected address argument", STARTOF(index), ENDOF(index));
            return false;
    }
}