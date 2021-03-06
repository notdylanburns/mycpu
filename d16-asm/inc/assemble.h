#ifndef _ASSEMBLE_H_GUARD_
#define _ASSEMBLE_H_GUARD_

#include <stdlib.h>
#include <stdint.h>

#include "asmenv.h"

extern uint16_t *assemble(char *filename, const char *source, size_t *words);

#endif