#ifndef _ADDRESS_H_GUARD_
#define _ADDRESS_H_GUARD_

enum ADDR_MODE {
    IMP,        // Implied              (ie no operands)
    IMM,        // Immediate            (#nnnn)
    A16,        // 16 bit address       (nnnn)
    A32,        // 32 bit address       (nnnnnnnn)
    REG,        // Register             (%n)
    IND,        // Indirect register    (*n)
    NUM_ADDR_MODES, // number of modes
};

#define TO_ADDR_INDEX(m1, m2) (size_t)((m1 * NUM_ADDR_MODES) + m2)

struct AddrMode {
    enum ADDR_MODE arg1;
    enum ADDR_MODE arg2;
};

extern const char *MODES[];

#endif