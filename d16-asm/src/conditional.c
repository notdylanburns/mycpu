#include "conditional.h"

struct Conditional *new_conditional(bool skip) {
    struct Conditional *c = malloc(sizeof(struct Conditional));
    if (c == NULL)
        return NULL;

    c->parent = NULL;
    c->skip = skip;

    return c;
}

struct Conditional *destroy_conditional(struct Conditional *c) {
    if (c == NULL)
        return NULL;
        
    struct Conditional *tmp = c->parent;
    free(c);
    return tmp;
}