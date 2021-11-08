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

                if (!asm_line(line, num_words, &env))
                    goto nomem;

                for (char **w = line; *w; w++)
                    free(*w);
                free(line);
                
                line = NULL;
                num_words = 0;
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
                while (*c != '\n') c++;
                break;

            case ':':
                if (num_words > 1) {
                    fprintf(stderr, "Syntax Error: Label names may not contain spaces\n");
                    goto cleanup;
                } else if (num_words == 0) {
                    fprintf(stderr, "Syntax Error: Empty label\n");
                    goto cleanup;
                }

                if (!add_label(&env, line[0]))
                    goto nomem;

                break;
        
            default:
                if (!add_character(*c, &word, &len_word))
                    goto nomem;
                break;
        }
    }

    //resolve label placeholders using label table

nomem:
    fprintf(stderr, "malloc failed...\n");

cleanup:
    for (char **w = line; *w; w++)
        free(*w);
    free(line);

    free(env.words);

    for (size_t i = 0; i < env.num_labels; i++)
        free(env.labels[i]);
    free(env.labels);

    for (size_t i = 0; i < env.num_placeholders; i++)
        free(env.tbc[i]);
    free(env.tbc);

    return NULL;

}