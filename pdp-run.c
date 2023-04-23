#include <stdio.h>
#include "pdp-mem.c"
#include "pdp_command.c"

word reg[8] ;        //registers R0, R1, ... R7. R7 program counter
#define pc reg[7]   // к rep[7] можем обращаться как pc

void run()
{
    pc = 01000;         //восьмеричное начало адреса

    while(1)
    {
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        pc += 2;                        // move on 2, cause only odd numbs as adresses



        if (w == 0)
        {
            printf("halt ");
            do_halt();
        }

        for ()

        if ((w & mask) == opcode);

        else if
        {

        }
        
    }
}

