#include "assemble.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "asmerror.h"
#include "instruction.h"
#include "label.h"
#include "macro.h"
#include "utils.h"

static bool add_char(char **s, char c) {
    size_t len = (*s == NULL) ? 0 : strlen(*s);

    char *tmp = realloc(*s, len + 2);
    if (tmp == NULL)
        return false;

    *s = tmp;
    (*s)[len] = c;
    (*s)[len + 1] = '\0';
    return true;
}

static bool add_arg(char *arg, char ***argv, size_t *argc) {
    (*argc)++;
    char **tmp = realloc(*argv, *argc * sizeof(char *));
    if (tmp == NULL)
        return false;

    *argv = tmp;
    (*argv)[*argc - 1] = arg;
    return true;
}

bool assemble_line(struct ASM *env, char *line) {
    char **argv = NULL;
    size_t argc = 0;

    char *arg = NULL;

    if (!strcmp(line, ""))
        return true;

    for (char *c = line; *c; c++) {
        switch (*c) {
            case ' ':
                if (arg != NULL)
                    if (!add_arg(arg, &argv, &argc))
                        goto nomem;
                    
                arg = NULL;
                break;
            
            case ':':
                if (argc != 0) {
                    print_err(env, LABEL_ERROR, "Label may not contain a space", STARTOF(0), ENDOF(argc));
                    goto cleanup;
                }

                if (!add_label(env, arg))
                    goto nomem;
                
                free(arg);
                arg = NULL;
                break;

            case ';':
                while (*c != '\0') c++;
                goto start_asm;

            case '!':
                if (argc != 0) {
                    print_err(env, SYNTAX_ERROR, "Macro must be at the start of the line", STARTOF(0), ENDOF(argc));
                }
                while (*c != '\0' && *c != ';') {
                    if (!add_char(&arg, *c))
                        goto nomem;

                    c++;
                }
                
                if (!run_macro(arg, env))
                    goto cleanup;

                free(arg);
                arg = NULL;
                return true;

            default:
                if (!add_char(&arg, *c))
                    goto nomem;
                break;
        }
    }
start_asm:
    if (arg != NULL)
        if (!add_arg(arg, &argv, &argc))
            goto nomem;

    arg = NULL;
    if (argc > 0)
        if (!asm_line(env, argv, argc))
            goto cleanup;

    for (size_t i = 0; i < argc; i++)
        free(argv[i]);
    free(argv);

    return true;

nomem:
    internal_err("malloc failed...");

cleanup:
    if (arg != NULL)
        free(arg);

    for (size_t i = 0; i < argc; i++)
        free(argv[i]);
    free(argv);

    return false;
}

uint16_t *assemble(char *filename, const char *source, size_t *words) {
   
    struct ASM env = { 
        .address=0x00000000, 
        .num_words=0, .words=NULL, 
        .num_labels=0, .labels=NULL,
        .num_placeholders=0, .tbc=NULL,
        .file=filename, .lineno=0,
        .cur_line=NULL,
    };

    char *src, *cpy = strdup(source);
    src = cpy;
    char **lines = NULL;
    size_t line_count = 0;

    char *nl;

    do {
        nl = strchr(src, '\n');
        if (nl != NULL)
            *nl = '\0';    

        line_count++;
        char **tmp = realloc(lines, line_count * sizeof(char *));
        if (tmp == NULL)
            goto nomem;

        lines = tmp;
        lines[line_count - 1] = src;

        src = nl + 1;

    } while (nl != NULL);


    for (size_t l = 0; l < line_count; l++) {
        env.lineno++;
        env.cur_line = lines[l];

        if (!assemble_line(&env, lines[l]))
            goto cleanup;
    }

    for (size_t i = 0; i < env.num_placeholders; i++) {
        uint32_t addr;
        if (!get_label(&env, env.tbc[i]->label, &addr)) {
            //env.lineno = env.tbc[i]->line;
            //print_err(&env, LABEL_ERROR, "Unknown label");
        } else {
            switch (env.tbc[i]->opts) {
                case LO_16:
                    env.words[env.tbc[i]->address] = (uint16_t)(addr & 0x0000ffff);
                    break;
                case HI_16:
                    env.words[env.tbc[i]->address] = (uint16_t)((addr & 0xffff0000) >> 16);
                    break;
                case BITS_32:
                    env.words[env.tbc[i]->address] = (uint16_t)((addr & 0xffff0000) >> 16);
                    env.words[env.tbc[i]->address + 1] = (uint16_t)(addr & 0x0000ffff);
                    break;
            }
        }
    }

    free(lines);
    free(cpy);

    for (size_t i = 0; i < env.num_labels; i++) {
        free(env.labels[i]->label);
        free(env.labels[i]);
    }
    free(env.labels);

    for (size_t i = 0; i < env.num_placeholders; i++) {
        free(env.tbc[i]->label);
        free(env.tbc[i]);
    }
    free(env.tbc);

    *words = env.num_words;
    return env.words;

nomem:
    internal_err("malloc failed...");

cleanup:
    free(lines);
    free(cpy);

    for (size_t i = 0; i < env.num_labels; i++) {
        free(env.labels[i]->label);
        free(env.labels[i]);
    }
    free(env.labels);

    for (size_t i = 0; i < env.num_placeholders; i++) {
        free(env.tbc[i]->label);
        free(env.tbc[i]);
    }
    free(env.tbc);

    return NULL;

}