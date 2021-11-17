#include "asminclude.h"

#include <string.h>

struct IncludedBy *new_include(char *filepath, size_t n, size_t num_lines) {
    struct IncludedBy *by = malloc(sizeof(struct IncludedBy));
    if (by == NULL)
        return NULL;

    by->fp = strdup(filepath);
    if (by->fp == NULL) {
        free(by);
        return NULL;
    }

    by->line = 0;
    by->n = n;
    by->remaining = num_lines;

    by->parent = NULL;

    return by;
}

void destroy_include(struct IncludedBy *by) {
    struct IncludedBy *next = NULL;
    while (by != NULL) {
        next = by->parent;
        free(by->fp);
        free(by);
        by = next;
    }
}

size_t get_lineno(struct IncludedBy *by) {
    struct IncludedBy *parent = 0;
    size_t total = 0;
    while (by != NULL) {
        parent = by->parent;
        total += by->line;
        by = parent;
    }

    return total;
}