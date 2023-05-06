#pragma once

#include "pdp-mem.h"


#define NO_PARAMS 0
#define HAS_DD 1        //001 в двоич
#define HAS_SS 2        //010 в двоич
#define HAS_NN 4        //100 в двоич
#define HAS_R  8        //001000 в двоич
#define HAS_B  16       //010000 в двоич
#define HAS_XX 32       //100000 в двоич

extern byte N;      // N = is negative (старший бит)
extern byte Z;      // Z = is zero
extern byte C;      // C = carry (после старшего бита если переполнилось)

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    char params;    // в 1 байте кодируем наличие разных типов аргументов
} Command;

extern Command list[];
Command parse_cmd(word w);
void set_NZ(word w);
void print_NZC();