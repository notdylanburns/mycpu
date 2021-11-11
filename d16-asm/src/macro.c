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

static bool _macro_org(struct ASM *env, size_t argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Macro Error: %s expects 1 argument (got %lu)\n", argv[0], argc);
        return false;
    }

    if (!value32(argv[1], &(env->address))) {
        fprintf(stderr, "Macro Error: Invalid argument '%s' for %s\n", argv[0], argv[1]);
        return false;
    }

    return true;
}

static bool _macro_dw(struct ASM *env, size_t argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Macro Error: %s expects 1 argument (got %lu)\n", argv[0], argc);
        return false;
    }

    uint16_t word;
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!add_label_ph(env, argv[1], 16))
                return false;
            break;
        
        default:
            if (!value16(argv[1], &word)) {
                fprintf(stderr, "Macro Error: Invalid argument '%s' for %s\n", argv[1], argv[0]);
                return false;
            }
            break;
    }

    if (!add_words(env, &word, 1)) {
        fprintf(stderr, "malloc failed...\n");
        return false;
    }

    return true;
}

static bool _macro_ddw(struct ASM *env, size_t argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Macro Error: %s expects 1 argument (got %lu)\n", argv[0], argc);
        return false;
    }

    uint32_t dword;
    uint16_t a[2];
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!add_label_ph(env, argv[1], 32))
                return false;
            break;
        
        default:
            if (!value32(argv[1], &dword)) {
                fprintf(stderr, "Macro Error: Invalid argument '%s' for %s\n", argv[1], argv[0]);
                return false;
            }
            break;
    }

    a[0] = (uint16_t)((dword & 0xffff0000) >> 12);
    a[1] = (uint16_t)((dword & 0x0000ffff));
    if (!add_words(env, a, 2)) {
        fprintf(stderr, "malloc failed...\n");
        return false;
    }

    return true;
}

struct MACRO {
    char *name;
    bool (*action)(struct ASM *, size_t, char **);
};

static const struct MACRO *MACROS[] = {
    &(struct MACRO){ "!org"  , &_macro_org },
    &(struct MACRO){ "!dw"   , &_macro_dw  },
    &(struct MACRO){ "!word" , &_macro_dw  },
    &(struct MACRO){ "!ddw"  , &_macro_ddw },
    &(struct MACRO){ "!dword", &_macro_ddw },
    NULL,
};

bool run_macro(char *macro, struct ASM *env) {
    char **argv = malloc(sizeof(char *));
    if (argv == NULL)
        goto nomem;
    
    *argv = strtok(macro, " ");
    if (*argv == NULL) {
        fprintf(stderr, "NULL pointer from strtok...\n");
        goto cleanup;
    }

    size_t argc = 1;
    char *a = strtok(NULL, " ");
    while (a != NULL) {
        char **tmp = realloc(argv, (++argc) * sizeof(char *));
        if (tmp == NULL)
            goto nomem;

        argv = tmp;
        argv[argc - 1] = a;
        a = strtok(NULL, " ");
    }

    for (const struct MACRO **m = MACROS; *m; m++)
        if (!strcmp(argv[0], (*m)->name)) {
            if (!(*m)->action(env, argc, argv))
                goto cleanup;
            free(argv);
            return true;
        }
    
    fprintf(stderr, "Macro Error: No such macro: %s\n", argv[0]);
    goto cleanup;

nomem:
    fprintf(stderr, "malloc failed...\n");

cleanup:
    free(argv);
    return false;

}