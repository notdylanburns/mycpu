#include "asmenv.h"

#include <string.h>

bool add_words(struct ASM *env, uint16_t *words, size_t num) {
    if ((env->address + num) > env->num_words) {
        uint16_t *tmp = realloc(env->words, (env->address + num) * sizeof(uint16_t));
        if (tmp == NULL)
            return false;

        env->words = tmp;
        memset(env->words + env->num_words, 0, (env->address + num) - env->num_words);
        env->num_words = (env->address + num);
    }

    for (size_t i = 0; i < num; i++)
        env->words[env->address + i] = words[i];

    env->address += num;
    return true;
}

bool add_lines(struct ASM *env, char **lines, size_t num) {
    char **tmp = realloc(env->lines, (env->num_lines + num) * sizeof(char *));
    if (tmp == NULL) {
        free(env->lines);
        env->lines = NULL;
        return false;
    }
    
    env->lines = tmp;
    memcpy(env->lines + env->abs_line + num + 1, env->lines + env->abs_line + 1, ((env->num_lines - env->abs_line) - 1) * sizeof(char *));
    env->num_lines += num;

    for (size_t i = 0; i < num; i++) 
        env->lines[env->abs_line + i + 1] = lines[i];

    return true;
}