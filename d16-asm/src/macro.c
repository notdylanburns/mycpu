#include "macro.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "asmenv.h"
#include "asmerror.h"
#include "asminclude.h"
#include "asmstring.h"
#include "conditional.h"
#include "label.h"
#include "symbol.h"
#include "value.h"
#include "utils.h"

static bool _macro_org(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (!value32(argv[1], &(env->address))) {
        print_err(env, MACRO_ERROR, "Invalid integer literal", STARTOF(1), ENDOF(1));
        return false;
    }

    return true;
}

static bool _macro_dw(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    uint16_t word;
    uint32_t addr;
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!get_label(env, argv[1], &addr)) {
                if (!add_label_ph(env, argv[1], env->by->line, 1, LO_16))
                    return false;
            } else
                word = (addr & 0x0000ffff);
            break;
        
        default:
            if (!value16(argv[1], &word)) {
                print_err(env, MACRO_ERROR, "Invalid integer literal", STARTOF(1), ENDOF(1));
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
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    uint32_t dword;
    uint16_t a[2];
    switch (get_type(argv[1])) {
        case V_LBL:
            if (!add_label_ph(env, argv[1], env->by->line, 1, BITS_32))
                return false;
            break;
        
        default:
            if (!value32(argv[1], &dword)) {
                print_err(env, MACRO_ERROR, "Invalid integer literal", STARTOF(1), ENDOF(1));
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

static bool _macro_wstr(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (get_type(argv[1]) == V_STR) {
        size_t len;
        if (!word_len(argv[1], &len, STR_WIDE)) {
            print_err(env, MACRO_ERROR, "Invalid string literal", STARTOF(1), ENDOF(1));
            return false;
        }

        uint16_t words[len];

        if (!strval(argv[1], words, STR_WIDE)) {
            print_err(env, MACRO_ERROR, "Invalid string literal", STARTOF(1), ENDOF(1));
            return false;
        }

        if (!add_words(env, words, len)) {
            internal_err("malloc failed...");
            return false;
        }
    
    } else {
        print_err(env, MACRO_ERROR, "Expected string literal", STARTOF(1), ENDOF(1));
        return false;
    }

    return true;
}

static bool _macro_bstr(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (get_type(argv[1]) == V_STR) {
        size_t len;
        if (!word_len(argv[1], &len, STR_BYTE)) {
            print_err(env, MACRO_ERROR, "Invalid string literal", STARTOF(1), ENDOF(1));
            return false;
        }

        uint16_t words[len];

        if (!strval(argv[1], words, STR_BYTE)) {
            print_err(env, MACRO_ERROR, "Invalid string literal", STARTOF(1), ENDOF(1));
            return false;
        }

        if (!add_words(env, words, len)) {
            internal_err("malloc failed...");
            return false;
        }
    
    } else {
        print_err(env, MACRO_ERROR, "Expected string literal", STARTOF(1), ENDOF(1));
        return false;
    }

    return true;
}

static bool _macro_inc(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (env->by->n >= 255) {
        print_err(env, MACRO_ERROR, "Maximum include depth reached", STARTOF(0), ENDOF(1));
    }

    char *fp;

    if (!strraw(argv[1], &fp)) {
        print_err(env, MACRO_ERROR, "Expected raw string literal", STARTOF(1), ENDOF(1));
        return false;
    }

    FILE *f = fopen(fp, "r");
    if (f == NULL) {
        print_err(env, INCLUDE_ERROR, "No such file", STARTOF(1), ENDOF(1));
        return false;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    char buf[len + 1];
    buf[len] = '\0';

    if (fread(buf, 1, len, f) != len) {
        fclose(f);
        internal_err("Error reading file...");
        goto cleanup;
    }
    fclose(f);

    char *dup, *src, *cpy = strdup(buf);
    if (cpy == NULL)
        goto nomem;
        
    src = cpy;

    char *nl;
    size_t num_lines = 0;
    char **lines = NULL;

    do {
        nl = strchr(src, '\n');
        if (nl != NULL)
            *nl = '\0';    

        num_lines++;
        char **tmp = realloc(lines, num_lines * sizeof(char *));
        if (tmp == NULL)
            goto nomem;

        lines = tmp;
        dup = strdup(src);
        if (dup == NULL)
            goto nomem;

        lines[num_lines - 1] = dup;

        src = nl + 1;

    } while (nl != NULL);

    struct IncludedBy *by = new_include(fp, env->by->n + 1, num_lines);
    if (by == NULL)
        goto nomem;

    by->parent = env->by;
    env->by = by;

    if (!add_lines(env, lines, num_lines)) 
        goto nomem;

    free(lines);
    free(cpy);
    return true;

nomem:
    internal_err("malloc failed...");

cleanup:
    for (size_t i = 0; i < num_lines; i++)
        free(lines[i]);
    free(lines);
    free(cpy);

    return false;
}

static bool _macro_embed(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    char *fp;

    if (!strraw(argv[1], &fp)) {
        print_err(env, MACRO_ERROR, "Expected raw string literal", STARTOF(1), ENDOF(1));
        return false;
    }

    FILE *f = fopen(fp, "r");
    if (f == NULL) {
        print_err(env, INCLUDE_ERROR, "No such file", STARTOF(1), ENDOF(1));
        return false;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    uint8_t buf[len];

    if (fread(buf, 1, len, f) != len) {
        fclose(f);
        internal_err("Error reading file...");
        return false;
    }
    fclose(f);

    size_t wordlen = (len / 2) + (len & 1);
    uint16_t words[wordlen];
    bool step = false;
    uint8_t hi_byte = 0;
    for (size_t i = 0; i < len; i++) {
        if (step)
            words[i / 2] = (hi_byte << 8) | (buf[i] & 0xff);
        else
            hi_byte = buf[i];
        step = !step;
    }

    if (len & 1)
        words[len / 2] = (hi_byte << 8) & 0xff00;
    else
        words[len / 2] = 0x0000;

    if (!add_words(env, words, wordlen)) {
        internal_err("malloc failed...");
        return false;
    }

    return true;
}

static bool _macro_define(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (!get_symbol(env, argv[1]))
        if (!add_symbol(env, argv[1]))
            return false;

    return true;
}

static bool _macro_undef(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    if (!get_symbol(env, argv[1]))
        if (!remove_symbol(env, argv[1]))
            return false;

    return true;
}

static bool _macro_ifdef(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    // if we're currently skipping, skip again. else evaluate the condition
    struct Conditional *c = new_conditional((env->ifs != NULL && env->ifs->skip) ? true : !get_symbol(env, argv[1]));
    if (c == NULL) {
        internal_err("malloc failed...");
        return false;
    }

    c->parent = env->ifs;
    env->ifs = c;

    return true;
}

static bool _macro_ifndef(struct ASM *env, size_t argc, char **argv) {
    if (argc < 2) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 2) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(2), ENDOF(argc - 1));
        return false;
    }

    // if we're currently skipping, skip again. else evaluate the condition
    struct Conditional *c = new_conditional((env->ifs != NULL && env->ifs->skip) ? true : get_symbol(env, argv[1]));
    if (c == NULL) {
        internal_err("malloc failed...");
        return false;
    }

    c->parent = env->ifs;
    env->ifs = c;

    return true;
}

static bool _macro_endif(struct ASM *env, size_t argc, char **argv) {
    if (argc < 1) {
        print_err(env, MACRO_ERROR, "Too few arguments", STARTOF(0), ENDOF(argc - 1));
        return false;
    } else if (argc > 1) {
        print_err(env, MACRO_ERROR, "Too many arguments", STARTOF(1), ENDOF(argc - 1));
        return false;
    }

    env->ifs = destroy_conditional(env->ifs);

    return true;
}

struct MACRO {
    char *name;
    bool (*action)(struct ASM *, size_t, char **);
    bool can_skip;
};

static const struct MACRO *MACROS[] = {
    &(struct MACRO){ "!org"         , &_macro_org       , true  },
    &(struct MACRO){ "!dw"          , &_macro_dw        , true  },
    &(struct MACRO){ "!word"        , &_macro_dw        , true  },
    &(struct MACRO){ "!ddw"         , &_macro_ddw       , true  },
    &(struct MACRO){ "!dword"       , &_macro_ddw       , true  },
    &(struct MACRO){ "!str"         , &_macro_wstr      , true  },
    &(struct MACRO){ "!wstr"        , &_macro_wstr      , true  },
    &(struct MACRO){ "!bstr"        , &_macro_bstr      , true  },
    &(struct MACRO){ "!inc"         , &_macro_inc       , true  },
    &(struct MACRO){ "!include"     , &_macro_inc       , true  },
    &(struct MACRO){ "!embed"       , &_macro_embed     , true  },
    &(struct MACRO){ "!define"      , &_macro_define    , true  },
    &(struct MACRO){ "!undef"       , &_macro_undef     , true  },
    &(struct MACRO){ "!ifdef"       , &_macro_ifdef     , false },
    &(struct MACRO){ "!ifndef"      , &_macro_ifndef    , false },
    &(struct MACRO){ "!endif"       , &_macro_endif     , false },
    NULL,
};

bool run_macro(char *macro, struct ASM *env) {
    char **argv = NULL;
    size_t argc = 0;
    char *arg = NULL;
    char escape = false;

    for (char *c = macro; *c; c++) {
        switch (*c) {
            case ' ':
            case '\t':
            case '\f':
            case '\v':
            case '\r':
                if (arg != NULL)
                    if (!add_arg(arg, &argv, &argc))
                        goto nomem;

                arg = NULL;
                break;
            
            case '"':
                if (!add_char(&arg, *c))
                    goto nomem;

                if (!escape) {
                    c++;
                    while (*c != '"') {
                        if (*c == '\0') {
                            print_err(env, SYNTAX_ERROR, "Unterminated string literal", STARTOF(argc + 1), ENDOF(argc + 1));
                            goto cleanup;
                        } else {
                            if (!add_char(&arg, *c))
                                goto nomem;
                        }
                        c++;
                    }
                    if (!add_char(&arg, *c))
                        goto nomem;

                    size_t new_len, estart, elen;
                    if (!resolve_escaped(arg, &new_len, &estart, &elen)) {
                        print_err(env, SYNTAX_ERROR, "Invalid escape sequence", estart, estart + elen);
                        goto cleanup;
                    }

                    char *tmp_arg = realloc(arg, new_len);
                    if (tmp_arg == NULL)
                        goto nomem;
                    
                    arg = tmp_arg;

                }
                break;

            case '\'':
                escape = true;
            default:
                if (!add_char(&arg, *c))
                    goto nomem;
        }
        escape = false;
    }

    if (arg != NULL) 
        if (!add_arg(arg, &argv, &argc))
            goto nomem;

    for (const struct MACRO **m = MACROS; *m; m++)
        if (!strcmp(argv[0], (*m)->name)) {
            if (env->ifs == NULL || !(env->ifs->skip) || !((*m)->can_skip))
                if (!(*m)->action(env, argc, argv))
                    goto cleanup;
            
            if (argv != NULL) {
                for (size_t i = 0; i < argc; i++)
                    free(argv[i]);
                free(argv);
            }
            return true;
        }
    
    print_err(env, MACRO_ERROR, "Invalid macro", STARTOF(0), ENDOF(0));
    goto cleanup;

nomem:
    internal_err("malloc failed...");

cleanup:
    free(arg);
    free(argv);
    return false;

}