// flags N, Z, C are also here
#include <stdio.h>
#include <stdlib.h>

#include "pdp-commands.h"
#include "pdp-register.h"

byte N;      // N = is negative (старший бит)
byte Z;      // Z = is zero
byte C;

void set_NZ(word w);          // flags!
void set_C(word a, word b);
void print_NZC();

void do_mov ();
void do_add ();     //!!!замена С!!!
void do_halt ();
void do_unknown ();
void do_sob();
void do_clr();      //!!!замена флагов!!!

void do_br();       //ветка без условия
void do_beq();      //ветка с условием Z = 1
void do_bpl();
void do_tst();      //test
void do_jmp();      //переход на указанный адрес

Command list[] = {
    {0070000, 0010000, "mov", do_mov, HAS_SS | HAS_DD | HAS_B}, // MOV : B1SSDD
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD}, // ADD : 06SSDD
    {0177000, 0077000, "sob", do_sob, HAS_NN | HAS_R},  // SOB : 077RNN
    {0077700, 0005000, "clr", do_clr, HAS_DD | HAS_B},  // CLR : B050DD 1/0 000|101 000|dddddd|
    
    {0177400, 0000400, 	"br", do_br, HAS_XX},           // BR : 0004XX -> 77!4! может меняться на 7!!! при отрицательном перемещении!
    {0177400, 0001400, "beq", do_beq, HAS_XX},          // BEQ : 0014XX Branch if Equal	If Z=1
	{0177400, 0100000, "bpl", do_bpl, HAS_XX},          // BPL : 1000XX Branch if Plus	If N=0
    {0077700, 0005700, "tst", do_tst, HAS_DD | HAS_B},  // TST : B057DD test d 
	{0177700, 0000100, "jmp", do_jmp, HAS_DD},          // JMP : 0001DD	Jump PC=d
    
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},     // HALT : 000000   
    {0000000, 0000000, "unknown", do_unknown, NO_PARAMS}, //Эта команда - ПОСЛЕДНЯЯ всегда в массиве!
};

Command parse_cmd(word w)
{
    int i = 0;
        for (i = 0; ; i++)
        {
            Command cmd = list[i];
            if ((w & cmd.mask) == cmd.opcode)
            {
                printf ("%s", cmd.name);

                if (cmd.params & HAS_B)
                {
                    B = (w >> 15) & 7;       //0|...|111|...|ssssss|dddddd| & 111 == 7
                    if(B)
                        printf("b ");  
                    else 
                        printf(" ");     
                }

                else 
                    printf("  ");
                
                    

                if (cmd.params & HAS_SS)
                    ss = get_mr (w >> 6); //тк формат записи двоичного числа ... |ssssss|dddddd|

                if (cmd.params & HAS_DD)
                    dd = get_mr (w);
    
                if (cmd.params & HAS_R)
                    r = ((w>>6) & 7);     //0|...|...|...|rrr|nnn nnn| & 111 == 7 

                if (cmd.params & HAS_NN)
                    nn = ((w) & 077);     //0|...|...|...|rrr|nnn nnn| & 111111 == 077
    
                if (cmd.params & HAS_XX)  //0|...|...|...|1xx|xxx xxx| & 11111111 == ff
                    xx = (w & 0xff);

                printf("\n");
                return cmd;
                exit(-12);
                break;
            }            
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
    if(B)
		b_write(dd.a, (byte)ss.val); 
	else
		w_write(dd.a, ss.val);
    set_NZ (ss.val);

}
void do_add()
{
    // сумму значений аргументов ss и dd пишем по адресу аргумента dd
    w_write(dd.a, ss.val + dd.val);
    set_NZ(dd.val + ss.val);
    C = ((ss.val + dd.val) >> 16) & 1; //смотрим за значением в бите, который за старшим
}

void do_sob()
{
    reg[r]--;

    if (reg[r] != 0)
        pc = pc - 2*(nn);

}
void do_unknown ()
{}

void do_clr()
{
    dd.val = 0;
    N = 0;
	Z = 1;
	C = 0;
	B = 0;      
}

void do_br () 
{
	pc = pc + 2*(xx);
}

void do_beq() 
{
    if(Z)
        do_br();
}

void do_bpl() 
{
    if(N == 0)
        do_br();
}

void do_tst()
{
	set_NZ(dd.val);
	C = 0;
}

void do_jmp() 
{
	pc = dd.a; 
}

//funcs for flags
void set_NZ(word w)
{
    if (w == 0)
    {
        Z = 1;
        N = 0;
    }

    else
    {
        Z = 0;
        if (B)     //если байтовая операция, то берём по старшему биту из 8м
            N = (w >> 7) & 1; 
        else
	        N = (w >> 15) & 1; 
    }
}

void print_NZC()
{
	printf("\n N=%d Z=%d C=%d \n",N ,Z ,C);
}