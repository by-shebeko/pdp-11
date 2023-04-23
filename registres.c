# include "pdp-11.c"


typedef struct {
    word val;     // значение (что)
    Adress a;    // адрес (куда)
} Arg;

Arg ss;
Arg dd;


Arg get_mr(word w)
{
    Arg res;
    word nn = w & 7;    //First 3 bits (000rrr), REGISTER
	word mode = (w>>3) & 7; //Second 3 bits (mmm000), MODE

    switch(mode)
    {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        default:
            printf("smth's not cool :< ");

	}

	return res;



    }



