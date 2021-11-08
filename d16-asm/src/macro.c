#include "macro.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

/*
    "!org",             // takes a 32 bit address
    "!word", "!dw",     // takes a 16 bit constant
    "!dword", "!ddw",   // takes a 32 bit constant
*/

bool run_macro(char *macro, struct ASM *env) {
    char *m = strtok(macro, " ");
    if (m == NULL) {
        fprintf(stderr, "NULL pointer from strtok...\n");
        return false;
    }

    char **argv = NULL;
    size_t argc = 0;
    char *a = strtok(NULL, " ");
    while (a != NULL) {
        char **tmp = realloc(argv, (++argc) * sizeof(char *));
        if (tmp == NULL) {
            free(argv);
            fprintf(stderr, "malloc failed...\n");
            return false;
        }
        argv = tmp;
        argv[argc - 1] = a;
        a = strtok(NULL, " ");
    }


    if (!strcmp(m, "!org")) {
        if (argc != 1) {
            fprintf(stderr, "Macro Error: !org expects 1 argument\n");
            return false;
        }

        if (get_type(argv[0]) != V_IMM || !value32(argv[0], &(env->address))) {
            fprintf(stderr, "Macro Error: !org expects a constant\n");
            return false;
        }
        return true;
    } else if (!strcmp(m, "!word") || !strcmp(m, "!dw")) {
        if (argc != 1) {
            fprintf(stderr, "Macro Error: %s expects 1 argument\n", m);
            return false;
        }

        uint16_t word;
        if (get_type(argv[0]) != V_IMM || !value16(argv[0], &word)) {
            fprintf(stderr, "Macro Error: %s expects a constant\n", m);
            return false;
        }

        if (!add_words(env, &word, 1)) {
            fprintf(stderr, "malloc failed...\n");
            return false;
        }

        return true;
    } else if (!strcmp(m, "!dword") || !strcmp(m, "!ddw")) {
        if (argc != 1) {
            fprintf(stderr, "Macro Error: %s expects 1 argument\n", m);
            return false;
        }

        uint32_t dword;
        if (get_type(argv[0]) != V_IMM || !value32(argv[0], &dword)) {
            fprintf(stderr, "Macro Error: %s expects a constant\n", m);
            return false;
        }

        uint16_t words[] = { (dword & 0xffff0000) >> 16, (dword & 0x0000ffff) };
        if (!add_words(env, words, 2)) {
            fprintf(stderr, "malloc failed...\n");
            return false;
        }

        return true;
    } else {
        fprintf(stderr, "Macro Error: Unknown macro: %s\n", m);
        return false;
    }

}