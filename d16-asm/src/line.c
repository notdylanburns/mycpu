#include "line.h"

struct line_t **get_lines(char *src, size_t len) {
    struct line_t **lines = NULL;
    struct line_t *current = malloc(sizeof(struct line_t));
    if (current == NULL)
        return NULL;

    for (char *c = src; *c && (c - src < len); c++) {
        current
    }
}
