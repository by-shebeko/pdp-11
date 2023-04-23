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

void test_mem()
{
    Adress a;
    byte b0, b1, bres;
    word w, wres;


    // пишем байт, читаем байт
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 0;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    // тут полезно написать отладочную печать a, b0, bres
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);
    // аналогично стоит проверить чтение и запись по нечетному адресу


    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 2;        // другой адрес
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);


    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 4;        // другой адрес
    w = 0xa1b2;
    // little-endian, младшие разряды по меньшему адресу
    b0 = 0xb2;
    b1 = 0xa1;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o b1=%02hhx b0=%02hhx wres=%04x\n", a, b1, b0, wres);
    assert(w == wres);


    //
}
