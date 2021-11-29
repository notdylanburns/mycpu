#include "instruction.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "asmerror.h"
#include "address.h"
#include "label.h"
#include "parse.h"
#include "utils.h"
#include "value.h"

struct Instruction *new_instruction(char *opcode, struct AddrMode a) {
    struct Instruction *i = malloc(sizeof(struct Instruction));
    i->opcode = opcode;
    i->a = TO_ADDR_INDEX(a.arg1, a.arg2);

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

bool get_opcode(struct Instruction *inst, uint16_t *op, size_t argc, struct ASM *env) {
    for (int i = 0; i < MATRIX_LEN; i++) {
        if (!strcmp(inst->opcode, MATRIX[i].N)) {
            if (MATRIX[i].M[inst->a].V) {
                *op = (uint16_t)format(MATRIX[i].M[inst->a].X, inst->r1, inst->r2);
                return true;
            } else {
                print_err(env, SYNTAX_ERROR, "Invalid addressing mode", STARTOF(1), ENDOF(argc - 1));
                return false;
            }
        }
    }
    print_err(env, SYNTAX_ERROR, "Invalid opcode", STARTOF(0), ENDOF(0));
    return false;
}

bool asm_line(struct ASM *env, char **argv, size_t argc) {
    struct Instruction *i = get_instruction(env, argv, argc);
    if (i == NULL)
        goto cleanup;

    uint16_t op = 0;
    if (!get_opcode(i, &op, argc, env))
        goto cleanup;

    if (!add_words(env, &op, 1))
        goto nomem;

    enum ADDR_MODE a1 = (i->a / NUM_ADDR_MODES), 
                   a2 = (i->a % NUM_ADDR_MODES);

    destroy_instruction(i);
    i = NULL;

    uint16_t word = 0;
    uint32_t dword = 0;
    uint16_t a[2] = {0, 0};
    switch (a1) {
        case IMM:
            if (!parse_imm(env, &word, argv[1], 1))
                return false;
            if (!add_words(env, &word, 1))
                goto nomem;
            break;
        
        case A16:
            if (!parse_a16(env, &word, argv[1], 1))
                return false;
            if (!add_words(env, &word, 1))
                goto nomem;
            break;

        case A32:
            if (!parse_a32(env, &dword, argv[1], 1))
                return false;
            a[0] = (uint16_t)((dword & 0xffff0000) >> 16);
            a[1] = (uint16_t)(dword & 0x0000ffff);
            if (!add_words(env, a, 2))
                goto nomem;
            break;

        case IMP:
            if (a2 != IMP) {
                internal_err("a1 is IMP, but a2 is not");
                return false;
            }
        default: // imp, reg, ind
            break;
    }

    switch (a2) {
        case IMM:
            if (!parse_imm(env, &word, argv[2], 2))
                return false;
            if (!add_words(env, &word, 1))
                goto nomem;
            break;
        
        case A16:
            if (!parse_a16(env, &word, argv[2], 2))
                return false;
            if (!add_words(env, &word, 1))
                goto nomem;
            break;

        case A32:
            if (!parse_a32(env, &dword, argv[2], 2))
                return false;
            a[0] = (uint16_t)((dword & 0xffff0000) >> 16);
            a[1] = (uint16_t)(dword & 0x0000ffff);
            if (!add_words(env, a, 2))
                goto nomem;
            break;

        default: // imp, reg, ind
            break;
    }

    return true;

nomem:
    internal_err("malloc failed...");

cleanup:
    if (i != NULL)
        destroy_instruction(i);

    return false;
}

struct Instruction *get_instruction(struct ASM *env, char **line, size_t linesize) {
    if (linesize == 0) {
        internal_err("Empty line being parsed...");
        return NULL;
    }

#define MAX_ARGS 2
    uint8_t r_args[MAX_ARGS];
    size_t num_regs = 0;
    enum ADDR_MODE a[MAX_ARGS] = {IMP, IMP};
    char *opcode = line[0];
    if (linesize == 1) { // imp
        a[0] = IMP;
        a[1] = IMP;
    } else if (linesize > (MAX_ARGS + 1)) { 
        print_err(env, SYNTAX_ERROR, "Too many arguments", STARTOF(MAX_ARGS + 1), ENDOF(linesize - 1));
        return NULL;
    } else {
#undef MAX_ARGS
        uint32_t addr = 0;
        for (size_t i = 1; i < linesize; i++) {
            switch (get_type(line[i])) {
                case V_IMM:
                    a[i - 1] = IMM;
                    break;
                
                case V_ADR:
                    if (!value32(line[i], &addr)) {
                        print_err(env, SYNTAX_ERROR, "Invalid address literal", STARTOF(i), ENDOF(i));
                        return NULL;
                    }
                    if ((addr & 0xffff0000) == (env->address& 0xffff0000)) 
                        a[i - 1] = A16;
                    else
                        a[i - 1] = A32; 
                    break;

                case V_REG:
                    if (strlen(line[i]) != 2 || !get_register(line[i][1], r_args + (num_regs++))) {
                        print_err(env, SYNTAX_ERROR, "Invalid register literal", STARTOF(i), ENDOF(i));
                        return NULL;
                    }
                    a[i - 1] = REG;
                    break;

                case V_LBL:
                    if (!get_label(env, line[i], &addr))
                        if ((addr & 0xffff0000) == (env->address & 0xffff0000))
                            a[i - 1] = A16;
                        else
                            a[i - 1] = A32; 
                    else
                        a[i - 1] = A32;
                    break;

                case V_LLO:
                case V_LHI:
                    a[i - 1] = IMM;
                    break;

                case V_IND:
                    if (strlen(line[i]) != 2 || !get_register(line[i][1], r_args + (num_regs++))) {
                        print_err(env, SYNTAX_ERROR, "Invalid indirect register literal", STARTOF(i), ENDOF(i));
                        return NULL;
                    }
                    a[i - 1] = IND;
                    break;

                default:
                    print_err(env, SYNTAX_ERROR, "Invalid argument", STARTOF(i), ENDOF(i));
                    return NULL;
            }
        }
    }

    struct Instruction *i = new_instruction(opcode, (struct AddrMode){ .arg1=a[0], .arg2=a[1] });
    if (i == NULL) {
        internal_err("malloc failed...");
        return NULL;
    }

    i->r1 = r_args[0]; i->r2 = r_args[1];
    return i;
}