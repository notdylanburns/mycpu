#ifndef _CONDITIONAL_H_GUARD_
#define _CONDITIONAL_H_GUARD_

#include <stdbool.h>
#include <stdlib.h>

struct Conditional {
    struct Conditional *parent;
    bool skip;
};

extern struct Conditional *new_conditional(bool skip);
extern struct Conditional *destroy_conditional(struct Conditional *c);

#endif