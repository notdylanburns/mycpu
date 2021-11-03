#include "number.h"

enum base_t {
    BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16,
};

static enum base_t get_base(char *str) {
    char bid = str[strlen(str) - 1];
    switch (bid) {
        case 'b':
            return BIN;
        
        case 'o':
            return OCT;

        case 'd':
            return DEC;

        case 'h':
            return HEX;

        default:
            return DEC;
    }
}

number16_t value16(char *str) {
    number16_t val = { .v16 = 0, .valid = true };
    size_t str_len = strlen(str);
    enum base_t base = get_base(str);
    char valstr[str_len];
    valstr[str_len - 1] = '\0';
    strncpy(valstr, str, str_len - 1);
    for (int i = 0; i < str_len - 1; i++) {
        char c = valstr[str_len - i - 2];
        switch (base) {
            case BIN:
                if (c != '0' && c != '1')
                    goto invalid;
                else
                    val.v16 += (uint16_t)((c - '0') * pow((double)base, (double)i));
            
            case OCT:
                if (c <= '0' || c >= '7')
                    goto invalid;
                else
                    val.v16 += (uint16_t)((c - '0') * pow((double)base, (double)i));
            
            case DEC:
                if (c <= '0' || c >= '9')
                    goto invalid;
                else
                    val.v16 += (uint16_t)((c - '0') * pow((double)base, (double)i));

            case HEX:
                if (c >= '0' && c <= '9')
                    val.v16 += (uint16_t)((c - '0') * pow((double)base, (double)i));
                else if (c >= 'a' && c <= 'f')
                    val.v16 += (uint16_t)((10 + c - 'a') * pow((double)base, (double)i));
                else if (c >= 'A' && c <= 'F')
                    val.v16 += (uint16_t)((10 + c - 'A') * pow((double)base, (double)i));
                else
                    goto invalid;
        }
    }
    
    return val;

invalid:
    val.valid = false;
    return val;
}

number32_t value32(char *str) {
    number32_t val;
    size_t str_len = strlen(str);
    enum base_t base = get_base(str);
    char valstr[str_len - 1];
    strncpy(valstr, str, str_len - 1);
    for (int i = 0; i < str_len - 1; i++) {
        char c = valstr[str_len - i - 1];
        switch (base) {
            case BIN:
                if (c != '0' && c != '1')
                    goto invalid;
                else
                    val.v32 += (uint32_t)((c - '0') * pow((double)base, (double)i));
            
            case OCT:
                if (c <= '0' || c >= '7')
                    goto invalid;
                else
                    val.v32 += (uint32_t)((c - '0') * pow((double)base, (double)i));
            
            case DEC:
                if (c <= '0' || c >= '9')
                    goto invalid;
                else
                    val.v32 += (uint32_t)((c - '0') * pow((double)base, (double)i));

            case HEX:
                if (c >= '0' && c <= '9')
                    val.v32 += (uint32_t)((c - '0') * pow((double)base, (double)i));
                else if (c >= 'a' && c <= 'f')
                    val.v32 += (uint32_t)((10 + c - 'a') * pow((double)base, (double)i));
                else if (c >= 'A' && c <= 'F')
                    val.v32 += (uint32_t)((10 + c - 'A') * pow((double)base, (double)i));
                else
                    goto invalid;
        }
    }

    return val;

invalid:
    val.valid = false;
    return val;

}