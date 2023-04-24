#include <stdio.h>
#include "pdp-mem.h"
#include "pdp-commands.h"
#include "pdp-register.h"


void run()
{
    printf("\nRunning \n");
    int i = 0;
    pc = 01000;         //восьмеричное начало адреса

    while(1)
    {
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        pc += 2;                        // move on 2, cause only odd numbs as adresses
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

        for (i = 0; ; i++)
        {
            Command cmd = list[i];
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

            if ((w & cmd.mask) == cmd.opcode)
            {
                printf ("%s ", cmd.name);

                if (cmd.params & HAS_SS)
                    ss = get_mr (w >> 6); //тк формат записи двоичного числа ... |ssssss|dddddd|

                if (cmd.params & HAS_DD)
                    dd = get_mr (w);
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

                cmd.do_command();
                printf("\n");
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
                break;

            }
            printf("\n");
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        }
        
    }
}


