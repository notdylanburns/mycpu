#include "assemble.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "instruction.h"
#include "macro.h"

static bool add_character(char c, char **word, size_t *len) {
    (*len)++;
    char *tmp = realloc(*word, (*len + 1) * sizeof(char));
    if (tmp == NULL) 
        return false;

    *word = tmp;
    (*word)[*len - 1] = c;
    (*word)[*len] = '\0';
    return true;
}

static bool add_word(char *w, char ***line, size_t *len) {
    (*len)++;
    char **tmp = realloc(*line, (*len + 1) * sizeof(char *));
    if (tmp == NULL)
        return false;

    *line = tmp;
    (*line)[*len - 1] = w;
    (*line)[*len] = NULL;
    return true;
}

uint16_t *assemble(const char *source, size_t *words) {
    //split the source into lines, and strip them down into opcodes and arguments

    struct ASM env = { 
        .address=0x00000000, 
        .num_words=0, .words=NULL, 
        .num_labels=0, .labels=NULL,
        .num_placeholders=0, .tbc=NULL,
    };

    char **line = NULL;
    size_t num_words = 0;
    char *word = NULL;
    size_t len_word = 0;

    char *macro = NULL;
    size_t len_macro = 0;

    for (const char *c = source; *c; c++) {
        switch (*c) {
            case '\n':
                if (word != NULL)
                    if (!add_word(word, &line, &num_words))
                        goto nomem;

                if (line != NULL) {
                    if (!asm_line(line, num_words, &env))
                        goto cleanup;

                    for (size_t i = 0; i < num_words; i++)
                        free(line[i]);
                    free(line);
                }

                line = NULL;
                word = NULL;
                num_words = 0;
                len_word = 0;
                break;

            case ' ':
                if (word == NULL)
                    break;

                if (!add_word(word, &line, &num_words))
                    goto nomem;

                word = NULL;
                len_word = 0;
                break;

            case '!':
                while (*c != '\n' && *c != ';') {
                    if (!add_character(*c, &macro, &len_macro)) {
                        free(macro);
                        goto nomem;
                    }
                    c++;
                }
                
                if (!run_macro(macro, &env))
                    goto cleanup;

                break;

            case ';':
                while (*c != '\n' && (c - source != strlen(source))) c++;
                c--;
                break;

            case ':':
                if (num_words > 0) {
                    fprintf(stderr, "Syntax Error: Label names may not contain spaces\n");
                    goto cleanup;
                } else if (len_word == 0) {
                    fprintf(stderr, "Syntax Error: Empty label\n");
                    goto cleanup;
                }

                if (!add_label(&env, word))
                    goto nomem;

                free(word);
                word = NULL;
                len_word = 0;

                break;
        
            default:
                if (!add_character(*c, &word, &len_word))
                    goto nomem;
                break;
        }
    }

    //resolve label placeholders using label table
    uint32_t address;
    for (size_t i = 0; i < env.num_placeholders; i++) {
        if (!get_label(&env, env.tbc[i]->label, &address)) {
            fprintf(stderr, "Syntax Error: No such label: %s\n", env.tbc[i]->label);
            goto cleanup;
        }

        env.words[env.tbc[i]->address] = address & 0x0000ffff;
        if (env.tbc[i]->bits == 32) {
            env.words[env.tbc[i]->address] = address & 0x0000ffff;
            env.words[env.tbc[i]->address + 1] = (address & 0xffff0000) >> 16;
        }
    }

    if (line != NULL)
        for (char **w = line; *w; w++)
            free(*w);
    free(line);

    for (size_t i = 0; i < env.num_labels; i++) {
        free(env.labels[i]->label);
        free(env.labels[i]);
    }
    free(env.labels);

    for (size_t i = 0; i < env.num_placeholders; i++)
        free(env.tbc[i]);
    free(env.tbc);

    *words = env.num_words;
    return env.words;

nomem:
    fprintf(stderr, "malloc failed...\n");

cleanup:
    if (line != NULL)
        for (size_t i = 0; i < num_words; i++)
            free(line[i]);
    free(line);

    free(env.words);

    for (size_t i = 0; i < env.num_labels; i++) {
        free(env.labels[i]->label);
        free(env.labels[i]);
    }
    free(env.labels);

    for (size_t i = 0; i < env.num_placeholders; i++)
        free(env.tbc[i]);
    free(env.tbc);

    return NULL;

}