#include "asmstring.h"

#include <string.h>

bool word_len(char *value, size_t *len) {
    if (value[strlen(value) - 1] != '"') // is last character "
        return false; 

    switch (value[0]) {
        case 'w':
            if (value[1] != '"')
                return false;
            value++;

        case '"':   // wide string default
            value++;
            *len = strlen(value);
            break;

        case 'b':
            if (value[1] != '"')
                return false;

            value += 2;
            size_t l = strlen(value);
            *len = (l & 1) ? (l / 2) + 1 : (l / 2);
            break;

        default:
            return false;
    }

    return true;
}

bool strval(char *value, uint16_t *v) {
    if (value[strlen(value) - 1] != '"') // is last character "
        return false; 

    size_t i;
    switch (value[0]) {
        case 'w':
            value++;
            if (value[0] != '"')
                return false;
        case '"':   // wide string default
            value++;

            for (i = 0; i < strlen(value) - 1; i++) {
                v[i] = 0x0000 | (uint8_t)value[i];
            }

            v[i] = 0x0000;

            return true;

        case 'b':
            if (value[1] != '"')
                return false;

            value += 2;

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