#include "address.h"

const char *MODES[] = {
    "implied",
    "nnnn",
    "*nnnn",
    "*nnnnnnnn",
    "%r",
    "*nnnn nnnn",
    "*nnnn %r",
    "*nnnnnnnn nnnn",
    "*nnnnnnnn %r",
    "%r nnnn",
    "%r *nnnn",
    "%r *nnnnnnnn",
    "%r %r",
};

const char WORDS[] = {
    1,
    2,
    2,
    3,
    1,
    2,
    1,
    4,
    3,
    2,
    2,
    3,
    1,
};