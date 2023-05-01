#include <stdio.h>
#include <stdlib.h>

#include "pdp-commands.h"
#include "pdp-register.h"

void do_mov ();
void do_add ();
void do_halt ();
void do_unknown ();
void do_sob();


Command list[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD}, // MOV : 01SSDD
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD}, // ADD : 06SSDD
    {0177000, 0077000, "sob", do_sob, HAS_NN | HAS_R},  // SOB : 077RNN
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},     // HALT : 000000
    {0000000, 0000000, "unknown", do_unknown, NO_PARAMS}, //Эта команда - ПОСЛЕДНЯЯ всегда в массиве!
};

Command parse_cmd(word w)
{
    int i = 0;
        for (i = 0; ; ++i)
        {
            Command cmd = list[i];
            if ((w & cmd.mask) == cmd.opcode)
            {
                printf ("%s ", cmd.name);

                if (cmd.params & HAS_SS)
                    ss = get_mr (w >> 6); //тк формат записи двоичного числа ... |ssssss|dddddd|

                if (cmd.params & HAS_DD)
                    dd = get_mr (w);
    
                if (cmd.params & HAS_R)
                    r = ((w>>6) & 7);     //0|...|...|...|rrr|nnn nnn| & 111 == 7 

                if (cmd.params & HAS_NN)
                    nn = ((w) & 077);       //0|...|...|...|rrr|nnn nnn| & 111111 == 077
    
                printf("\n");
                return cmd;
                exit(-12);
                break;
            }
            printf("\n");
            //return cmd;
            //exit (-1);
        }
    exit (-2);
}

void do_halt () 
{
    printf("\n---halted---\n");
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

void do_sob()
{
    reg[r]--;

    if (reg[r] != 0)
        pc = pc - 2*(nn);

}
void do_unknown ()
{}




