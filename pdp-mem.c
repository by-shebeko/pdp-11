# include <stdio.h>
# include <assert.h>

#include "pdp-mem.h"

# define MEMSIZE (64*1024)      //redefined! 64 -> 56


static word mem[MEMSIZE];   // 1 word = 2 bytes, mem[i] - слово по адресу i, 
                            //состоит из двух байт по адресам i и i+1. 
                            //Нечетные ячейки массива не используются
word reg[8] ;        //registers R0, R1, ... R7. R7 program counter

void b_write(Adress adr, byte b)
{
    if (adr == odata)
    {
       //printf(" %c", b);
       FILE* myfile;
       myfile = fopen("out.txt", "a");
       fprintf(myfile, "%c\n", b);
       fclose(myfile);
    }
    if(adr < 8)
	{
		if((b >> 7) == 1)        //проверка знакового бита 1000 0000
			reg[adr] = 0xFF00 | b;    //заполняем оставшееся 1111... (знак расширение)
		else
			reg[adr] = 0x0000 | b;    //заполняем ост 0000... (знак расширение)
    }

    else 
    {
        if (adr % 2 == 0)
            mem[adr] = b & 0xFF; 
    
        else 
        {    
        word w = mem[adr-1] & 0xFF; 
        mem[adr-1] = (b << 8 | w);
        }
    }
}

byte b_read(Adress adr)
{
    byte b;                     //will be returned
    
    if (adr < 8) 
            b = reg[adr] | 0xFF;  

    else
    {
        if (adr % 2 == 0)
            b = mem[adr] & 0xFF;    // mask for 1 word (16 bit)

        else                        //если адрес нечётный, а у нас что-то лежит только по чётным адресам => двигаем
        {
            word w = mem[adr-1];
            b = w >> 8 & 0xFF;
        }
    }
    return b;
}

word w_read(Adress adr)
{
    if (adr < 8) {
        return reg[adr];
    }
    
    assert(adr % 2 == 0);    
    return mem[adr];
}

void w_write(Adress adr, word w)
{
    if (adr == odata)
    {
       //printf(" %c", b);
       FILE* myfile;
       myfile = fopen("out.txt", "a");
       fprintf(myfile, "%c\n", w);
       fclose(myfile);
    }

    if (adr < 8) {
        reg[adr] = w & 0xFFFF; //registers are initialized in registres.c
        return;
    }
    else 
        assert(adr % 2 == 0);
    mem[adr] = w;
}

