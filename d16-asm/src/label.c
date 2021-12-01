#include "asmenv.h"
#include "label.h"

#include <string.h>

struct ASM;

bool add_label(struct ASM *env, char *l) {
    struct Label *label = malloc(sizeof(struct Label));
    if (label == NULL)
        return false;

    label->label = calloc(1, strlen(l) + 1);
    if (label->label == NULL) {
        free(label);
        return false;
    }
    strcpy(label->label, l);
    label->address = env->address;

    struct Label **tmp = realloc(env->labels, (env->num_labels + 1) * sizeof(struct Label *));
    if (tmp == NULL) {
        free(label);
        return false;
    }
    env->labels = tmp;
    env->labels[(env->num_labels)++] = label;
    return true;
}

bool get_label(struct ASM *env, char *l, uint32_t *address) {
    for (size_t i = 0; i < env->num_labels; i++)
        if (!strcmp(env->labels[i]->label, l)) {
            *address = env->labels[i]->address;
            return true;
        }

    return false;
}

bool add_label_ph(struct ASM *env, char *l, size_t line, size_t word, enum LabelOpts opts) {
    struct LabelPlaceholder *lph = malloc(sizeof(struct LabelPlaceholder));
    if (lph == NULL)
        return false;

    lph->label = calloc(1, strlen(l) + 1);
    if (lph->label == NULL) {
        free(lph);
        return false;
    }
    strcpy(lph->label, l);
    lph->address = env->address;

    struct LabelPlaceholder **tmp = realloc(env->tbc, (env->num_placeholders + 1) * sizeof(struct LabelPlaceholder *));
    if (tmp == NULL) {
        free(lph);
        return false;
    }
    env->tbc = tmp;
    lph->opts = opts;
    lph->line = line;
    lph->word = word;
    env->tbc[(env->num_placeholders)++] = lph;
    return true;
}