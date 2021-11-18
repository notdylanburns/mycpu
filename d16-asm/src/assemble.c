#include "assemble.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "asmerror.h"
#include "asminclude.h"
#include "instruction.h"
#include "label.h"
#include "macro.h"
#include "utils.h"

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

                uint32_t a;
                if (!get_label(env, arg, &a)) {
                    if (!add_label(env, arg))
                        goto nomem;
                } else {
                    print_err(env, LABEL_ERROR, "Redefinition of label", STARTOF(0), ENDOF(0));
                    goto cleanup;
                }
                
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
    struct IncludedBy *by = new_include(filename, 0, 0);
    if (by == NULL) {
        internal_err("malloc failed...");
        return NULL;
    }
    
    struct ASM env = { 
        .address=0x00000000, 
        .num_words=0, .words=NULL, 
        .num_labels=0, .labels=NULL,
        .num_placeholders=0, .tbc=NULL,
        .lines=NULL, .cur_line=NULL,
        .by=by, .abs_line=0,
    };

    char *dup, *src, *cpy = strdup(source);
    if (cpy == NULL)
        goto nomem;

    src = cpy;

    char *nl;

    do {
        nl = strchr(src, '\n');
        if (nl != NULL)
            *nl = '\0';    

        env.num_lines++;
        char **tmp = realloc(env.lines, env.num_lines * sizeof(char *));
        if (tmp == NULL)
            goto nomem;

        env.lines = tmp;

        dup = strdup(src);
        if (dup == NULL)
            goto nomem;

        env.lines[env.num_lines - 1] = dup;

        src = nl + 1;

    } while (nl != NULL);

    env.by->remaining = env.num_lines;

    for (env.abs_line = 0; env.abs_line < env.num_lines; env.abs_line++) {
        env.by->line++;
        env.by->remaining--;

        env.cur_line = env.lines[env.abs_line];

        if (!assemble_line(&env, env.cur_line))
            goto cleanup;

        while (env.by != NULL && env.by->remaining == 0) {
            struct IncludedBy *parent = env.by->parent;
            free(env.by->fp);
            free(env.by);
            env.by = parent;
        }
    }

    for (size_t i = 0; i < env.num_placeholders; i++) {
        uint32_t addr;
        if (!get_label(&env, env.tbc[i]->label, &addr)) {
            //env.abs_line = env.tbc[i]->line;
            //print_err(&env, LABEL_ERROR, "Unknown label");
            internal_err("Label undefined, no error handling yet");
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

    for (size_t i = 0; i < env.num_lines; i++)
        free(env.lines[i]);
    free(env.lines);
    free(cpy);

    destroy_include(env.by);

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
    for (size_t i = 0; i < env.num_lines; i++)
        free(env.lines[i]);
    free(env.lines);
    free(cpy);

    destroy_include(env.by);

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