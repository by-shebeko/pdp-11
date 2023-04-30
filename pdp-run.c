#include <stdio.h>
#include "pdp-mem.h"
#include "pdp-commands.h"
#include "pdp-register.h"


void run()
{
    printf("\n---Running---\n");
    int i = 0;
    pc = 01000;         //восьмеричное начало адреса

    while(1)
    {
        word w = w_read(pc);
        printf("%06o: ", pc);
        pc += 2;                        // move on 2, cause only even numbs as adresses
        
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
    
                cmd.do_command();
                printf("\n");    
                break;
            }
            //printf("\n");
        }
        
    }
}


