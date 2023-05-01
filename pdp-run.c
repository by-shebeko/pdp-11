#include <stdio.h>
#include "pdp-mem.h"
#include "pdp-commands.h"
#include "pdp-register.h"


void run()
{
    printf("\n---Running---\n");
    //int i = 0;
    pc = 01000;         //восьмеричное начало адреса

    while(1)
    {
        word w = w_read(pc);
                               // move on 2, cause only even numbs as adresses
        printf("%06o %06o: ", pc, w);
        pc += 2; 
        Command cmnd = parse_cmd(w);
        cmnd.do_command();  
        //print_reg();
        //printf("\n");         
    }
}


