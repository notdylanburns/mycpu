#include "macro.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "asmerror.h"
#include "label.h"
#include "value.h"
#include "utils.h"

/*
    "!org",             // takes a 32 bit address
    "!word", "!dw",     // takes a 16 bit constant
    "!dword", "!ddw",   // takes a 32 bit constant
*/

static bool _macro_org(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "!org expects 1 argument", argv[0], argc);
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "!org expects 1 argument", argv[0], argc);
        return false;
    }

    if (!value32(argv[1], &(env->address))) {
        print_err(env, MACRO_ERROR, "Invalid argument '%s' for %s", argv[1], argv[0]);
        return false;
    }

    return true;
}

static bool _macro_dw(struct ASM *env, size_t argc, char **argv) {
    if (argc != 2) {
        print_err(env, MACRO_ERROR, "%s expects 1 argument (got %lu)", argv[0], argc);
        return false;
    }

    uint16_t word;
    uint32_t addr;
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!get_label(env, argv[1], &addr)) {
                if (!add_label_ph(env, argv[1], env->lineno, 1, LO_16))
                    return false;
            } else
                word = (addr & 0x0000ffff);
            break;
        
        default:
            if (!value16(argv[1], &word)) {
                print_err(env, MACRO_ERROR, "Invalid argument '%s' for %s", argv[1], argv[0]);
                return false;
            }
            break;
    }

    if (!add_words(env, &word, 1)) {
        internal_err("malloc failed...");
        return false;
    }

    return true;
}

static bool _macro_ddw(struct ASM *env, size_t argc, char **argv) {
    if (argc != 2) {
        print_err(env, MACRO_ERROR, "%s expects 1 argument (got %lu)", argv[0], argc);
        return false;
    }

    uint32_t dword;
    uint16_t a[2];
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!add_label_ph(env, argv[1], env->lineno, 1, BITS_32))
                return false;
            break;
        
        default:
            if (!value32(argv[1], &dword)) {
                print_err(env, MACRO_ERROR, "Invalid argument '%s' for %s", argv[1], argv[0]);
                return false;
            }
            break;
    }

    a[0] = (uint16_t)((dword & 0xffff0000) >> 16);
    a[1] = (uint16_t)((dword & 0x0000ffff));
    if (!add_words(env, a, 2)) {
        internal_err("malloc failed...");
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
        internal_err("NULL pointer from strtok...");
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
    
    print_err(env, MACRO_ERROR, "Invalid macro", STARTOF(0), ENDOF(0));
    goto cleanup;

nomem:
    internal_err("malloc failed...");

cleanup:
    free(argv);
    return false;

}