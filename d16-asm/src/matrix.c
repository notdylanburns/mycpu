#include "matrix.h"
const int MATRIX_LEN = 44;

const struct Opcode MATRIX[] = {
    {.N="hlt", .M={{.V=true ,.X="0000"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="int", .M={{.V=true ,.X="0001"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="rti", .M={{.V=true ,.X="0002"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="nop", .M={{.V=true ,.X="0003"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="mov", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0004"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="004R"},{.V=true ,.X="009R"},{.V=false,.X="----"},{.V=true ,.X="0005"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="005R"},{.V=true ,.X="00AR"},{.V=false,.X="----"},{.V=true ,.X="001R"},{.V=true ,.X="002R"},{.V=true ,.X="003R"},{.V=true ,.X="01XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="006R"},{.V=true ,.X="007R"},{.V=true ,.X="008R"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="phf", .M={{.V=true ,.X="0006"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="ppf", .M={{.V=true ,.X="0007"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jmp", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0008"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0009"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsr", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="000A"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="000B"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="ret", .M={{.V=true ,.X="000C"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="ppg", .M={{.V=true ,.X="000D"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="rpg", .M={{.V=true ,.X="000E"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="psh", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="000F"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="00FR"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="spg", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="00B0"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="00C0"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="00DR"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="pop", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="00ER"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsv", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0200"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0210"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsz", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0201"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0211"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsp", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0202"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0212"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jss", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0203"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0213"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsd", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0204"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0214"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsc", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0205"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0215"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsb", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0206"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0216"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jsa", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0207"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0217"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnv", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0208"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0218"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnz", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0209"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="0219"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnp", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020A"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021A"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jns", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020B"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021B"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnd", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020C"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021C"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnc", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020D"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021D"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jnb", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020E"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021E"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="jna", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="020F"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="021F"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="adc", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1150"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="112R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1160"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="114R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="110R"},{.V=true ,.X="111R"},{.V=true ,.X="113R"},{.V=true ,.X="10XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="sbc", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1350"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="133R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1360"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="134R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="130R"},{.V=true ,.X="131R"},{.V=true ,.X="133R"},{.V=true ,.X="12XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="and", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1550"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="152R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1560"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="154R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="150R"},{.V=true ,.X="151R"},{.V=true ,.X="153R"},{.V=true ,.X="14XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="orz", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1750"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="172R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1760"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="174R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="170R"},{.V=true ,.X="171R"},{.V=true ,.X="173R"},{.V=true ,.X="16XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="xor", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1950"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="192R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1960"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="194R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="190R"},{.V=true ,.X="191R"},{.V=true ,.X="193R"},{.V=true ,.X="18XY"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="lsh", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A10"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A11"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A0R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="rsh", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A30"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A31"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A2R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="rol", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A50"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A51"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A4R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="ror", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A70"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A71"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A6R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="not", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A90"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A91"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1A8R"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="inc", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AB0"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AB1"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AAR"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="dec", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AD0"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AD1"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1ACR"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
    {.N="stf", .M={{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AF0"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AF1"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=true ,.X="1AER"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},{.V=false,.X="----"},}},
};
