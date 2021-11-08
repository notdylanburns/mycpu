#include "instruction.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

struct Instruction *new_instruction(char *opcode, enum ADDR_MODE a) {
    struct Instruction *i = malloc(sizeof(struct Instruction));
    i->opcode = opcode;
    i->a = a;
    i->r1 = 0;
    i->r2 = 0;
    return i;
}

void destroy_instruction(struct Instruction *i) {
    free(i);
}

static uint16_t format(const char *o, uint8_t r1, uint8_t r2) {
    uint16_t n = 0;
    int e = 3;
    for (const char *c = o; *c && e >= 0; c++) {
        if ('0' <= *c && *c <= '9')
            n += ((*c - '0') << (4 * e));
        else if ('A' <= *c && *c <= 'F')
            n += ((*c - 'A' + 10) << (4 * e));
        else if (*c == 'R' || *c == 'X')
            n += r1 << (4 * e);
        else if (*c == 'Y')
            n += r2 << (4 * e);
        
        e--;
    }
    return n;
}

bool get_opcode(struct Instruction *inst, uint16_t *op) {
    for (int i = 0; i < MATRIX_LEN; i++) {
        if (!strcmp(inst->opcode, MATRIX[i].N)) {
            if (MATRIX[i].M[inst->a].V) {
                *op = (uint16_t)format(MATRIX[i].M[inst->a].X, inst->r1, inst->r2);
                return true;
            } else {
                fprintf(stderr, "Syntax Error: %s has no addressing mode: %s\n", MATRIX[i].N, MODES[inst->a]);
                return false;
            }
        }
    }
    fprintf(stderr, "Syntax Error: No such opcode: %s\n", inst->opcode);
    return false;
}

static bool parse_imm(struct ASM *env, uint16_t *word, char *w) {
    (void)env;
    switch (get_type(w)) {
        case V_IMM:
            if (!value16(w + 1, word)) {
                fprintf(stderr, "Syntax Error: Invalid constant: %s\n", w);
                return false;
            }
            return true;
        
        default:
            fprintf(stderr, "Syntax Error: %s expected immediate argument\n", w);
            return false;
    }
}

static bool parse_a16(struct ASM *env, uint16_t *word, char *w) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value16(w + 1, word)) {
                fprintf(stderr, "Syntax Error: Invalid address: %s\n", w);
                return false;
            }
            return true;

        case V_LBL:
            uint32_t dword;
            if (!get_label(env, w, &dword))
                add_label_ph(env, w, 16);
            else
                *word = (uint16_t)(dword & 0x0000ffff);
        
        default:
            fprintf(stderr, "Syntax Error: %s expected address argument\n", w);
            return false;
    }
}

static bool parse_a32(struct ASM *env, uint32_t *dword, char *w) {
    switch (get_type(w)) {
        case V_ADR:
            if (!value32(w + 1, dword)) {
                fprintf(stderr, "Syntax Error: Invalid address: %s\n", w);
                return false;
            }
            return true;

        case V_LBL:
            if (!get_label(env, w, dword))
                add_label_ph(env, w, 32);
        
        default:
            fprintf(stderr, "Syntax Error: %s expected address argument\n", w);
            return false;
    }
}

bool asm_line(char **line, size_t linesize, struct ASM *env) {
    struct Instruction *i = get_instruction(line, linesize);
    if (i == NULL)
        goto cleanup;

    uint16_t op;
    if (!get_opcode(i, &op))
        goto cleanup;

    if (!add_words(env, &op, 1))
        goto nomem;
    
    linesize--;
    line++;

    uint16_t word;
    uint32_t dword;
    uint16_t a[2];
    switch (i->a) {
        case IMM:
            if (!parse_imm(env, &word, line[0]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;

        case A16:
        case A16_REG:
            if (!parse_a16(env, &word, line[0]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;

        case A32:
        case A32_REG:
            if (!parse_a32(env, &dword, line[0]))
                goto cleanup;
            a[0] = (uint16_t)(dword & 0xffff0000) >> 12; 
            a[1] = (uint16_t)(dword & 0x0000ffff);
            if (!add_words(env, a, 2))
                goto nomem;
            free(i);
            return true;

        case A16_IMM:
            if (!parse_a16(env, &word, line[0]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            if (!parse_imm(env, &word, line[1]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;

        case A32_IMM:
            if (!parse_a32(env, &dword, line[0]))
                goto cleanup;
            a[0] = (uint16_t)(dword & 0xffff0000) >> 12; 
            a[1] = (uint16_t)(dword & 0x0000ffff);
            if (!add_words(env, a, 2))
                goto nomem;
            if (!parse_imm(env, &word, line[1]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;

        case REG_IMM:
            if (!parse_imm(env, &word, line[1]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;

        case REG_A16:
            if (!parse_a16(env, &word, line[1]))
                goto cleanup;
            if (!add_words(env, &word, 1))
                goto nomem;
            free(i);
            return true;
        
        case REG_A32:
            if (!parse_a32(env, &dword, line[1]))
                goto cleanup;
            a[0] = (uint16_t)(dword & 0xffff0000) >> 12; 
            a[1] = (uint16_t)(dword & 0x0000ffff);
            if (!add_words(env, a, 2))
                goto nomem;
            free(i);
            return true;

        default: // imp, reg, reg_reg
            free(i);
            return true;
    }

nomem:
    fprintf(stderr, "malloc failed...\n");

cleanup:
    free(i);

    return false;
}

struct Instruction *get_instruction(char **line, size_t linesize) {
    enum ADDR_MODE a;
    uint8_t r1 = 0, r2 = 0;
    if (linesize == 0) {
        fprintf(stderr, "Empty line being parsed...\n");
    };
    char *opcode = line[0];
    if (linesize == 1) { // imp
        a = IMP;
    } else if (linesize == 2) { // imm, a16, a32, reg
        switch (get_type(line[1])) {
            case V_IMM:
                a = IMM;
                break;
            case V_LBL:
                a = A32;
                break;
            case V_ADR:
                uint32_t addr;
                if (!value32(line[1] + 1, &addr)) {
                    fprintf(stderr, "Syntax Error: Invalid address: %s\n", line[1]);
                    return NULL;
                }
                if ((addr & 0x0000ffff) == addr) 
                    a = A16;
                else
                    a = A32; 
                break;
            case V_REG:
                if (strlen(line[1]) != 2 || !get_register(line[1][1], &r1)) {
                    fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[1]);
                    return NULL;
                }
                a = REG;
                break;
        }
    } else if (linesize == 3) {
        enum VAL_TYPE t = get_type(line[2]);
        switch (get_type(line[1])) {
            case V_IMM:
                fprintf(stderr, "Syntax Error: Invalid combination of addressing modes: %s and %s\n", line[1], line[2]);
                return NULL;
            case V_LBL:
                if (t == V_REG) {
                    if (strlen(line[2]) != 2 || !get_register(line[2][1], &r1)) {
                        fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[2]);
                        return NULL;
                    }
                    a = A32_REG;
                } else if (t == V_IMM) {
                    a = A32_IMM;
                } else {
                    fprintf(stderr, "Syntax Error: Invalid combination of addressing modes: %s and %s\n", line[1], line[2]);
                    return NULL;
                }
                break;
            case V_ADR:
                uint32_t addr;
                if (!value32(line[1] + 1, &addr)) {
                    fprintf(stderr, "Syntax Error: Invalid address: %s\n", line[1]);
                    return NULL;
                }
                if ((addr & 0x0000ffff) == addr) 
                    if (t == V_REG) {
                        if (strlen(line[2]) != 2 || !get_register(line[2][1], &r1)) {
                            fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[2]);
                            return NULL;
                        }
                        a = A16_REG;
                    } else if (t == V_IMM) {
                        a = A16_IMM;
                    } else {
                        fprintf(stderr, "Syntax Error: Invalid combination of addressing modes: %s and %s\n", line[1], line[2]);
                        return NULL;
                    }
                else
                    if (t == V_REG) {
                        if (strlen(line[2]) != 2 || !get_register(line[2][1], &r1)) {
                            fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[2]);
                            return NULL;
                        }
                        a = A32_REG;
                    } else if (t == V_IMM) {
                        a = A32_IMM;
                    } else {
                        fprintf(stderr, "Syntax Error: Invalid combination of addressing modes: %s and %s\n", line[1], line[2]);
                        return NULL;
                    }
                break;
            case V_REG:
                if (strlen(line[1]) != 2 || !get_register(line[1][1], &r1)) {
                    fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[1]);
                    return NULL;
                }
                if (t == V_REG) {
                    if (strlen(line[2]) != 2 || !get_register(line[2][1], &r2)) {
                        fprintf(stderr, "Syntax Error: Invalid register: %s\n", line[2]);
                        return NULL;
                    }
                    a = REG_REG;
                } else if (t == V_IMM)
                    a = REG_IMM;
                else if (t == V_ADR) {
                    uint32_t addr;
                    if (!value32(line[2] + 1, &addr)) {
                        fprintf(stderr, "Syntax Error: Invalid address: %s\n", line[2]);
                        return NULL;
                    }
                    if ((addr & 0x0000ffff) == addr) 
                        a = REG_A16;
                    else
                        a = REG_A32;
                } else {
                    fprintf(stderr, "Syntax Error: Invalid combination of addressing modes: %s and %s\n", line[1], line[2]);
                    return NULL;
                }
                break;
        }
    } else {
        fprintf(stderr, "Syntax Error: Too many arguments for opcode: %s", line[0]);
        return NULL;
    }

    struct Instruction *i = new_instruction(opcode, a);
    if (i == NULL) {
        fprintf(stderr, "malloc failed...\n");
        return NULL;
    }

    i->r1 = r1; i->r2 = r2;
    return i;
}