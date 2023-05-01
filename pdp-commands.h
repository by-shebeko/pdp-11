#pragma once

#include "pdp-mem.h"


#define NO_PARAMS 0
#define HAS_DD 1        //001 в двоич
#define HAS_SS 2        //010 в двоич
#define HAS_NN 4        //100 в двоич
#define HAS_R  8        //001000 в двоич

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    char params;    // в 1 байте кодируем наличие разных типов аргументов
} Command;

extern Command list[];
Command parse_cmd(word w);