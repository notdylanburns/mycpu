#include <stdlib.h>
#include <stdio.h>

#include "assemble.h"

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

    FILE *output = fopen(argv[2], "wb+");
    if (output == NULL) {
        fprintf(stderr, "No such file '%s'\n", argv[2]);
        return 1;
    }
    if (fwrite(words, 2, wc, output) != wc) {
        fprintf(stderr, "Error while writing '%s'\n", argv[2]);
        return 1;
    }

    return 0;
}