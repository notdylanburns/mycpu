#ifndef _INSTRUCTION_H_GUARD_
#define _INSTRUCTION_H_GUARD_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "address.h"
#include "asmenv.h"
#include "matrix.h"

struct Instruction {
    char *opcode;
    size_t a;
    uint8_t r1, r2;
};

extern struct Instruction *new_instruction(char *opcode, struct AddrMode a);
extern void destroy_instruction(struct Instruction *i);
extern bool get_opcode(struct Instruction *i, uint16_t *op, size_t argc, struct ASM *env);
extern bool asm_line(struct ASM *env, char **argv, size_t argc);
extern struct Instruction *get_instruction(struct ASM *env, char **line, size_t linesize);

#endif