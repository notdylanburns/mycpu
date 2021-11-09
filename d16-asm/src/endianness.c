#include "endianness.h"

enum ENDIANNESS get_endianness() {
    short x = 1;
    char *y = (char *)&x;

    return *y ? LE : BE;
}