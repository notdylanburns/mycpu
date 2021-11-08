#ifndef _ADDRESS_H_GUARD_
#define _ADDRESS_H_GUARD_

#define ADDR_MODES 16

enum ADDR_MODE {
    IMP,        // Implied          (ie no operands)
    IMM,        // Immediate        (nnnn)
    A16,        // 16 bit address   (*nnnn)
    A32,        // 32 bit address   (*nnnnnnnn)
    REG,        // Register         (%n)

    A16_IMM,    // 16 bit address + Immediate
    A16_REG,    // 16 bit address + Register

    A32_IMM,    // 32 bit address + Immediate
    A32_REG,    // 32 bit address + Register 

    REG_IMM,    // Register + Immediate 
    REG_A16,    // Register + 16 bit address
    REG_A32,    // Register + 32 bit address
    REG_REG,    // Register + Register
};

extern const char *MODES[];
extern const char WORDS[];

#endif