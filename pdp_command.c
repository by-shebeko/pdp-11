#include <stdio.h>
#include <stdlib.h>

#include "pdp-commands.h"
#include "pdp-register.h"

void do_mov ();
void do_add ();
void do_nothing ();
void do_halt ();
void do_unknown ();


Command list[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0000000, 0000000, "unknown", do_unknown, NO_PARAMS}, //Эта команда должна быть всегда последней в массиве!
};



void do_halt () 
{
    printf("\n");
    print_reg();
    printf("THE END!!!\n");
    exit(0);
}
void do_mov()
{
    // значение аргумента ss пишем по адресу аргумента dd
    w_write(dd.a, ss.val);
}
void do_add()
{
    // сумму значений аргументов ss и dd пишем по адресу аргумента dd
    w_write(dd.a, ss.val + dd.val);
}

void do_unknown ()
{
    // exit(-1);

}




