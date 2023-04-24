# include "pdp-11.c"

word reg[8];        //6 - sp, 7 - pc

typedef struct {
    word val;     // значение (что)
    Adress a;    // адрес (куда)
} Arg;

Arg ss;
Arg dd;


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
            printf("R%d ", reg_n);
        break;

        case 2:                          // мода 2, (R1)+ или #3
            res.a = reg[reg_n];           // в регистре адрес
            res.val = w_read(res.a);  // по адресу - значение
            reg[reg_n] += 2;  

            // печать разной мнемоники для PC и других регистров
            if (reg_n == 7)
            printf("#%o ", res.val);
            else
            printf("(R%d)+ ", reg_n);
        break;

        // мы еще не дописали другие моды

        default:
        printf("Mode %d not implemented yet!\n", mode);
        exit(1);
	}

	return res;

}

void print_reg()  //понимаю, что через число команд плохо, как по-другому - не поняла :(
{
	int i = 0;
	printf("\nRegisters are: \n");

	for (i = 0; i < 3; i++) 
    {
		printf("R%d : %.7o ", i, reg[i]);
	}
	printf("\n");
}
