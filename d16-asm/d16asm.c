#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "inc/asmerror.h"
#include "inc/assemble.h"
#include "inc/endianness.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fatal_err("No input file specified...");
        return 1;
    } else if (argc < 3) {
        fatal_err("No output file specified...");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        fatal_err("No such file '%s'", argv[1]);
        return 1;
    }

    fseek(src, 0, SEEK_END);
    long len = ftell(src);
    rewind(src);

    char cont[len + 1];
    cont[len] = '\0';

    if (fread(cont, 1, len, src) != len) {
        fclose(src);
        fatal_err("Error while reading '%s'", argv[1]);
        return 1;
    }

    fclose(src);

    size_t wc = 0;
    uint16_t *words = assemble(argv[1], cont, &wc);

    if (words == NULL)
        return 1;

    FILE *output = fopen(argv[2], "w+");
    if (output == NULL) {
        fatal_err("Unable to create output '%s'", argv[2]);
        goto cleanup;
    }

    if (get_endianness() == BE) {
        if (fwrite(words, 2, wc, output) != wc) {
            fclose(output);
            fatal_err("Error while writing '%s'", argv[2]);
            goto cleanup;
        }
    } else {
        uint8_t bytes[2 * wc];
        for (size_t i = 0; i < wc; i++) {
            uint16_t w = words[i];
            bytes[2 * i] = (w & 0xff00) >> 8;
            bytes[(2 * i) + 1] = w & 0x00ff;
        }
        if (fwrite(bytes, 1, 2 * wc, output) != (2 * wc)) {
            fclose(output);
            fatal_err("Error while writing '%s'", argv[2]);
            goto cleanup;
        }
    }

    fclose(output);
    free(words);
    return 0;

cleanup:
    if (output != NULL)
        fclose(output);
    free(words);
    return 1;
}