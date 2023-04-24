#pragma once

#include "pdp-mem.h"


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    char params;    // в 1 байте кодируем наличие разных типов аргументов
} Command;

extern Command list[];
