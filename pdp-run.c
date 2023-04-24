#include <stdio.h>
#include "pdp-mem.c"
#include "pdp_command.c"

word reg[8] ;        //registers R0, R1, ... R7. R7 program counter
#define pc reg[7]   // к rep[7] можем обращаться как pc

void run()
{
    printf("\nRunning \n");
    int i = 0;
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

        for (i = 0; ; i++)
        {
            Command cmd = list[i];

            if ((w & cmd.mask) == cmd.opcode)
            {
                printf ("%s ", cmd.name);

                if (cmd.params & HAS_SS)
                    ss = get_mr (w >> 6); //тк формат записи двоичного числа ... |ssssss|dddddd|

                if (cmd.params & HAS_DD)
                    dd = get_mr (w);

            }

        }
        
    }
}


