#include "asmstring.h"

#include <string.h>

bool word_len(char *value, size_t *len, enum STR_TYPE t) {
    if (value[0] != '"' || value[strlen(value) - 1] != '"') // is surrounded by ""
        return false; 

    switch (t) {
        case STR_WIDE:
            value++;
            *len = strlen(value);
            break;

        case STR_BYTE:
            value++;
            size_t l = strlen(value);
            *len = (l & 1) ? (l / 2) + 1 : (l / 2);
            break;

        default:
            return false;
    }

    return true;
}

bool strval(char *value, uint16_t *v, enum STR_TYPE t) {
    if (value[0] != '"' || value[strlen(value) - 1] != '"') // is surrounded by ""
        return false; 

    value++;
    size_t i;
    switch (t) {
        case STR_WIDE:
            for (i = 0; i < strlen(value) - 1; i++) {
                v[i] = 0x0000 | (uint8_t)value[i];
            }

            v[i] = 0x0000;

            return true;

        case STR_BYTE:
            bool parity = false;
            uint8_t prev = 0;
            for (i = 0; i < strlen(value) - 1; i++) {
                if (parity) {
                    v[i / 2] = (prev << 8) | value[i];
                } else {
                    prev = value[i];
                }
                parity = !parity;
            }

            if (parity)
                v[i / 2] = (prev << 8);
            else
                v[i / 2] = 0x0000; 

            return true;

        default:
            return false;
    }
}

bool strraw(char *value, char **v) {
    size_t final = strlen(value) - 1;
    if (value[0] != '"' || value[final] != '"')
        return false; 

    *v = value + 1;
    value[final] = '\0';

    return true;
}