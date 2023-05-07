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
extern char xx; //оно знаковое!!!!!!!

#define ostat = 177564  ; регистр состояния дисплея дисплея
#define odata = 177566  ; регистр данных дисплея

Arg get_mr(word w);
void print_reg();
