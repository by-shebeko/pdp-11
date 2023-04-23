#include <stdio.h>
#include "pdp-mem.c"

void do_mov () {}
void do_add () {}
void do_nothing () {}
void do_halt () {
    printf("THE END!!!\n");
    exit(0);
}

typedef struct {            // struct for commands for easier if cycle
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
} Command;

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177777, 0000000, "halt", do_halt}
};
