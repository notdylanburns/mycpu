#include "value.h"

#include <stdlib.h>
#include <string.h>

enum VAL_TYPE get_type(char *value) {
    switch (value[0]) {
        case '*':
            return V_ADR;

        case '%':
            return V_REG;

        default:
            if (('0' <= value[0] && '9' >= value[0]) || value[0] == '$' || value[0] == '\'')
                return V_IMM;
            else
                return V_LBL;
    }
}

bool value16(char *value, uint16_t *v) {
    *v = 0;
    size_t e;
    switch (value[0]) {
        case '\'': //bin
            e = strlen(value + 1) - 1;
            for (char *c = (value + 1); *c; c++) {
                if (*c == '1' || *c == '0')
                    *v += (uint16_t)((*c == '1') << e);
                else
                    return false;
                e--;
            }
            return true;

        case '$': //hex
            e = strlen(value + 1) - 1;
            for (char *c = (value + 1); *c; c++) {
                if (*c >= '0' && *c <= '9')
                    *v += (uint16_t)((*c - '0') << (4 * e));
                else if (*c >= 'a' && *c <= 'f')
                    *v += (uint16_t)((10 + *c - 'a') << (4 * e));
                else if (*c >= 'A' && *c <= 'F')
                    *v += (uint16_t)((10 + *c - 'A') << (4 * e));
                else
                    return false;
                e--;
            }
            return true;

        default: //dec
            for (char *c = value; *c; c++)
                if ('0' > *c || *c > '9')
                    return false;
            *v = atoi(value);
            return true;
    }
}

bool value32(char *value, uint32_t *v) {
    *v = 0;
    size_t e;
    switch (value[0]) {
        case '\'': //bin
            e = strlen(value + 1) - 1;
            for (char *c = (value + 1); *c; c++) {
                if (*c == '1' || *c == '0')
                    *v += (uint32_t)((*c == '1') << e);
                else
                    return false;
                e--;
            }
            return true;

        case '$': //hex
            e = strlen(value + 1) - 1;
            for (char *c = (value + 1); *c; c++) {
                if (*c >= '0' && *c <= '9')
                    *v += (uint32_t)((*c - '0') << (4 * e));
                else if (*c >= 'a' && *c <= 'f')
                    *v += (uint32_t)((10 + *c - 'a') << (4 * e));
                else if (*c >= 'A' && *c <= 'F')
                    *v += (uint32_t)((10 + *c - 'A') << (4 * e));
                else
                    return false;
                e--;
            }
            return true;

        default: //dec
            for (char *c = value; *c; c++)
                if ('0' > *c || *c > '9')
                    return false;
            *v = atoi(value);
            return true;
    }
}

bool get_register(char n, uint8_t *r) {
    if ('0' <= n && n <= '9')
        *r = n - '0';
    else if ('a' <= n && n <= 'f')
        *r = 10 + n - 'a';
    else if ('A' <= n && n <= 'F')
        *r = 10 + n - 'A';
    else 
        return false;
    return true;
}