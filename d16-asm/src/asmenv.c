#include "asmenv.h"

#include <string.h>

bool add_words(struct ASM *env, uint16_t *words, size_t num) {
    uint16_t *tmp = realloc(env->words, env->num_words + num);
    if (tmp == NULL)
        return false;

    env->words = tmp;
    for (size_t i = 0; i < num; i++) {
        env->words[env->num_words + i] = words[i];
    }

    env->num_words += num;
    env->address += num;
    return true;
}

bool add_label(struct ASM *env, char *l) {
    struct Label *label = malloc(sizeof(struct Label));
    if (label == NULL)
        return false;

    label->label = l;
    label->address = env->address;

    (env->num_labels)++;
    struct Label **tmp = realloc(env->labels, env->num_labels * sizeof(struct Label *));
    if (tmp == NULL) {
        free(label);
        return false;
    }
    env->labels = tmp;
    env->labels[env->num_labels - 1] = label;
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

bool add_label_ph(struct ASM *env, char *l, uint8_t bits) {
    struct LabelPlaceholder *lph = malloc(sizeof(struct LabelPlaceholder));
    if (lph == NULL)
        return false;

    lph->label = l;
    lph->address = env->num_words;

    (env->num_placeholders)++;
    struct LabelPlaceholder **tmp = realloc(env->tbc, env->num_placeholders * sizeof(struct LabelPlaceholder *));
    if (tmp == NULL) {
        free(lph);
        return false;
    }
    env->tbc = tmp;
    env->tbc[env->num_placeholders - 1] = lph;
    return true;
}