#include "symbol.h"

#include <string.h>

bool add_symbol(struct ASM *env, char *sym) {
    char *cpy = strdup(sym);
    if (cpy == NULL)
        return false;

    char **tmp = realloc(env->symbols, (env->num_symbols + 1) * sizeof(char *));
    if (tmp == NULL)
        return false;

    env->symbols = tmp;
    env->symbols[(env->num_symbols)++] = cpy;
    return true;
}

bool get_symbol(struct ASM *env, char *sym) {
    for (size_t i = 0; i < env->num_symbols; i++) {
        if (!strcmp(env->symbols[i], sym))
            return true;
    }

    return false;
}

bool remove_symbol(struct ASM *env, char *sym) {
    for (size_t i = 0; i < env->num_symbols; i++) {
        if (!strcmp(env->symbols[i], sym)) {
            free(env->symbols[i]);
            env->symbols[i] = env->symbols[env->num_symbols - 1];
            char **tmp = realloc(env->symbols, (env->num_symbols - 1) * sizeof(char *));
            if (tmp == NULL)
                return false;
            
            (env->num_symbols)--;
            return true;
        }
    }

    return true;
}