# include <stdio.h>
# include <assert.h>

typedef unsigned char byte;      // 8 bit
typedef unsigned short int word; // 16 bit
typedef word Adress;             // 16 bit

# define MEMSIZE (64*1024)

word mem[MEMSIZE];  // 1 word = 2 bytes, mem[i] - слово по адресу i, 
                    //состоит из двух байт по адресам i и i+1. 
                    //Нечетные ячейки массива не используются

void b_write(Adress adr, byte b); // записывает в адрес переменную
byte b_read(Adress adr);          // возврат значения байта по адресу
void w_write(Adress adr, word w); // записывыет слово в адесс
word w_read(Adress adr);          // возвращает значение слова по адресу

void test_mem();

int main()
{
    test_mem();
    return 0;
}

void b_write(Adress adr, byte b)
{
    if (adr % 2 == 0)
        mem[adr] = b & 0xFF; 
    
    else 
    {    
       word w = mem[adr-1] & 0xFF; 
       mem[adr-1] = (b << 8 | w);
    }
}

byte b_read(Adress adr)
{
    byte b;                     //will be returned
    if (adr % 2 == 0)
        b = mem[adr] & 0xFF;    // mask for 1 word (16 bit)

    else                        //если адрес нечётный, а у нас что-то лежит только по чётным адресам => двигаем
    {
        word w = mem[adr-1];
        b = w >> 8 & 0xFF;
    }

    return b;
}

word w_read(Adress adr)
{
    assert(adr % 2 == 0);
    return mem[adr];
}

void w_write(Adress adr, word w)
{
    assert(adr % 2 == 0);
    mem[adr] = w;
}
