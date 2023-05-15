#include <stdio.h>
#include <stdlib.h>

#include "pdp-register.h"


Arg ss;
Arg dd;
byte nn;
byte r;
char xx;
byte B; //flag for byte operation
byte r0; //register, in which we grab

Arg get_mr(word w)
{
    Arg res;
    word reg_n = w & 7;    //First 3 bits (000rrr), REGISTER
	word mode = (w>>3) & 7; //Second 3 bits (mmm000), MODE

    switch(mode)
    {
        case 0:                         //mode 0, R1
            res.a = reg_n;
			res.val = reg[reg_n];   //value is in register
			printf("R%d ", reg_n);
		break;

        case 1:                         // мода 1, (R1)
            res.a = reg[reg_n];           // в регистре адрес
            res.val = w_read(res.a);  // по адресу - значение
            printf("(R%d) ", reg_n);
        break;

        case 2:                         // мода 2, (R1)+ или #3
            
            //puts("  qweryui    \n");
            res.a = reg[reg_n];           // в регистре адрес

            if(B && (reg_n < 6))   
            {
                res.val = b_read(res.a);  // по адресу - значение
                reg[reg_n]++;
            }                      
            
            else
            {
                res.val = w_read(res.a);  // по адресу - значение
                reg[reg_n] += 2; 
            } 

            // печать разной мнемоники для PC и других регистров
            if (reg_n == 7)
                printf("#%o ", res.val);
            else
                printf("(R%d)+ ", reg_n);
        break;

        case 3:
            res.a = w_read(reg[reg_n]); //адрес по адресу
            
            if (B) 
                res.val = b_read(res.a);
            else
                res.val = w_read(res.a); //значение из адреса по адресу

            // печать разной мнемоники для PC и других регистров
            if (reg_n == 7)
            {
                if (res.a == ostat)
                	printf("@#%o", ostat); 

                else if (res.a == odata) 
				printf("@#%o", odata);

                else
                    printf("#%o ", res.val);
            }
            else
                printf("@(R%d)+ ", reg_n);
            
			reg[reg_n] += 2;         //увеличение значения адреса по адресу
        break;

        case 4:
        //puts("  hi!!    \n");
            if (B && (reg_n < 6))
            {
                reg[reg_n]--;
                res.a = reg[reg_n];
                res.val = b_read(res.a); 
            }  

            else
            {
                reg[reg_n]-= 2;
                res.a = reg[reg_n];
                res.val = w_read(res.a);
            }
                
			printf("-(R%d) ", reg_n);
        break;

        case 5:
            reg[reg_n] -= 2;
			res.a = w_read(reg[reg_n]);

            if (B)
                res.val = b_read(res.a);
            else 
                res.val = w_read(res.a);

            printf("@-(R%d) ", reg_n);
        break;

        case 6:                         
            word x = w_read(pc);        //x = mem[pc]     // прочитали очередное слово в коде
            pc += 2;                    //pc += 2
            res.a = reg[reg_n] + x;     //adr = reg[n]    // адрес указателя
                                        //adr = adr + x   // адрес указателя со смещением
            if (B)                      //val = mem[adr]  // разыменование
                res.val = b_read(res.a);
            else 
                res.val = w_read (res.a);

            //печать моды 
            if (reg_n == 7)
                printf("%.6o ", res.a);
            else 
                printf ("%.6o(R%o) ", x, reg_n);
                                                   
        break;                               

        // мы еще не дописали другие моды
        default:
        printf("Mode %d not implemented yet!\n", mode);
        exit(1);
	}

	return res;

}

void print_reg()
{
	int i = 0;

	for (i = 0; i < 8; i++) 
    {
		printf("R%d:%o ", i, reg[i]);
	}
	printf("\n");
}
