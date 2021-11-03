#ifndef _LINE_H_GUARD_
#define _LINE_H_GUARD_

#include <stdlib.h>
#include <stdint.h>

#include <arg.h>

struct line_t {
    char opc[4];
    uint8_t num_args;
    struct arg_t **args;
};

extern struct line_t **get_lines(char *src, size_t len);

#endif