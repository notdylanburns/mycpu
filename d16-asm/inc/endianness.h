#ifndef _ENDIANNESS_H_GUARD_
#define _ENDIANNESS_H_GUARD_

enum ENDIANNESS {
    LE,
    BE,
};

extern enum ENDIANNESS get_endianness();

#endif