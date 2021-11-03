#ifndef _NUMBER_H_GUARD_
#define _NUMBER_H_GUARD_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    uint16_t v16;
    bool valid;
} number16_t;

typedef struct {
    uint32_t v32;
    bool valid;
} number32_t;

extern number16_t value16(char *str);
extern number32_t value32(char *str);

#endif