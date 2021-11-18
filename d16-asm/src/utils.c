#include "utils.h"

#include <stdbool.h>
#include <string.h>

bool add_char(char **s, char c) {
    size_t len = (*s == NULL) ? 0 : strlen(*s);

    char *tmp = realloc(*s, len + 2);
    if (tmp == NULL)
        return false;

    *s = tmp;
    (*s)[len] = c;
    (*s)[len + 1] = '\0';
    return true;
}

bool add_arg(char *arg, char ***argv, size_t *argc) {
    (*argc)++;
    char **tmp = realloc(*argv, *argc * sizeof(char *));
    if (tmp == NULL)
        return false;

    *argv = tmp;
    (*argv)[*argc - 1] = arg;
    return true;
}