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
    enum ADDR_MODE a;
    uint8_t r1, r2;
};

extern struct Instruction *new_instruction(char *opcode, enum ADDR_MODE a);
extern void destroy_instruction(struct Instruction *i);
extern bool get_opcode(struct Instruction *i, uint16_t *op);
extern bool asm_line(char **line, size_t linesize, struct ASM *env);
extern struct Instruction *get_instruction(char **line, size_t linesize);

#endif