#include <stdlib.h>
#include <stdio.h>

#include <logger/logger.h>

#include "assemble.h"
#include "number.h"

int main(int argc, char **argv) {
    if (argc < 2)
        lfatal(DefaultLogger, 1, "Usage: d16a [filename]");

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL)
        lfatalf(DefaultLogger, 1, "No such file: %s", argv[1]);
    
    fseek(src, 0, SEEK_SET);
    size_t len = ftell(src);
    rewind(src);

    char content[len];
    if (fread(content, 1, len, src) != len)
        lfatalf(DefaultLogger, 1, "Error reading file: %s", argv[1]);

    assemble(content, len);
}