#include "asmstring.h"

#include <string.h>

bool resolve_escaped(char *value, size_t *new_len, size_t *start, size_t *len) {
    bool escape_next = false;
    size_t slen = strlen(value);
    char new_str[slen + 1];
    memset(new_str, 0, slen + 1);
    char num = 0;
    size_t oct_i = 0, pos = 0;

    for (size_t i = 0; i < slen; i++) {
        if (escape_next) {
            escape_next = false;
            switch (value[i]) {
                case '"':
                    new_str[pos] = '"';
                    break;
                case '\'':
                    new_str[pos] = '\'';
                    break;
                case '\\':
                    new_str[pos] = '\\';
                    break;
                case 'a':
                    new_str[pos] = '\a';
                    break;
                case 'b':
                    new_str[pos] = '\b';
                    break;
                case 'e':
                    new_str[pos] = '\e';
                    break;
                case 'f':
                    new_str[pos] = '\f';
                    break;
                case 'n':
                    new_str[pos] = '\n';
                    break;
                case 'r':
                    new_str[pos] = '\r';
                    break;
                case 't':
                    new_str[pos] = '\t';
                    break;
                case 'v':
                    new_str[pos] = '\v';
                    break;
                case 'x':   // hex byte
                    i++;
                    while (oct_i < 2 && i < slen) {
                        if ('0' <= value[i] && value[i] <= '7') {
                            num += (value[i] - '0') << (oct_i * 4);
                        } else if ('a' <= value[i] && value[i] <= 'f') {
                            num += (10 + value[i] - 'a') << ((1 - oct_i) * 4);
                        } else if ('A' <= value[i] && value[i] <= 'F') {
                            num += (10 + value[i] - 'A') << ((1 - oct_i) * 4);
                        } else {
                            *len = oct_i + 2;
                            *start = i - oct_i - 2;
                            return false;
                        }
                        oct_i++;
                        i++;
                    }
                    i--;
                    new_str[pos] = num;
                    num = 0;
                    break;

                // octal
                case'0':
                case'1':
                case'2':
                case'3':
                case'4':
                case'5':
                case'6':
                case'7':
                    while (oct_i < 3 && i < slen) {
                        if ('0' > value[i] || value[i] > '7') {
                            *len = oct_i + 2;
                            *start = i - oct_i - 1;
                            return false;
                        } else {
                            num += (value[i] - '0') << ((2 - oct_i) * 3);
                        }
                        oct_i++;
                        i++;
                    }
                    i--;
                    new_str[pos] = num;
                    num = 0;
                    break;

                default:
                    *start = i - 1;
                    *len = 2;
                    return false;

            }
            pos++;
            oct_i = 0;
        } else if (value[i] == '\\') {
            escape_next = true;
        } else {
            new_str[pos] = value[i];
            pos++;
        }
    }
    memcpy(value, new_str, pos + 1);
    *new_len = pos + 1;
    return true;
}

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
                    v[i / 2] = (prev << 8) | (value[i] & 0xff);
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