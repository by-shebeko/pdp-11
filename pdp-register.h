#pragma once

# include "pdp-mem.h"

typedef struct {
    word val;     // значение (что)
    Adress a;    // адрес (куда)
} Arg;

extern Arg ss;
extern Arg dd;
extern byte nn;
extern byte r;
extern byte B;

Arg get_mr(word w);
void print_reg();
