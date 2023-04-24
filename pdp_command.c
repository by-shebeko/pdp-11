#include <stdio.h>
#include "pdp-mem.c"
#include "registres.c"

#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2

void do_mov ();
void do_add ();
void do_nothing ();
void do_halt ();

/*typedef struct {            // struct for commands for easier if cycle
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
} Command;
*/

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    char params;    // в 1 байте кодируем наличие разных типов аргументов
} Command;

Command list[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS}
};

void do_halt () 
{
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

void do_unknown (Command res)
{}




