#include <stdlib.h>
#include <stdio.h>

#include "assemble.h"
#include "endianness.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "No input file specified...\n");
        return 1;
    } else if (argc < 3) {
        fprintf(stderr, "No output file specified...\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL) {
        fprintf(stderr, "No such file '%s'\n", argv[1]);
        return 1;
    }

    fseek(src, 0, SEEK_END);
    long len = ftell(src);
    rewind(src);

    char cont[len + 1];
    cont[len] = '\0';

    if (fread(cont, 1, len, src) != len) {
        fprintf(stderr, "Error while reading '%s'\n", argv[1]);
        return 1;
    }

    fclose(src);

    size_t wc;
    uint16_t *words = assemble(cont, &wc);

    if (words == NULL)
        return 1;

    FILE *output = fopen(argv[2], "wb+");
    if (output == NULL) {
        fprintf(stderr, "No such file '%s'\n", argv[2]);
        return 1;
    }

    if (get_endianness() == BE) {
        if (fwrite(words, 2, wc, output) != wc) {
            fprintf(stderr, "Error while writing '%s'\n", argv[2]);
            return 1;
        }
    } else {
        uint8_t bytes[2 * wc];
        for (size_t i = 0; i < wc; i++) {
            uint16_t w = words[i];
            bytes[2 * i] = w & 0xffff0000;
            bytes[(2 * i) + 1] = w & 0x0000ffff;
        }
        if (fwrite(bytes, 1, 2 * wc, output) != (2 * wc)) {
            fprintf(stderr, "Error while writing '%s'\n", argv[2]);
            return 1;
        }
    }

    return 0;
}