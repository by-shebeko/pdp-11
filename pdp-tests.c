#include "pdp-11.c"
#include <stdarg.h>
#include "pdp_command.c"
# include <assert.h>

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


    // еще тесты

    
}

//#define DEBUG 1
//#define MORE_DEBUG 2

//int debug_level = DEBUG;

/*void trace(int dbg_lvl, char * format, ...) 
{//1/2 x3
	if (dbg_lvl != debug_level)
		return;
	va_list argptr;
	va_start (argptr, format);
	vprintf(format, argptr);
	va_end(argptr);	
}
*/


// тест, что мы правильно определяем команды mov, add, halt
void test_parse_mov()
{
            //trace(TRACE, __FUNCTION__);
    Command cmd = parse_cmd(0017654);
    assert(strcmp(cmd.name, "mov"));
            //trace(TRACE, " ... OK\n");
    printf(" ... OK\n");
}

// тест, что мы разобрали правильно аргументы ss и dd в mov R5, R3
void test_mode0()
{
            //trace(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503); //????
    assert(ss.val == 34);
    assert(ss.a == 5);
    assert(dd.val == 12);
    assert(dd.a == 3);
            //trace(TRACE, " ... OK\n");
    printf(" ... OK\n");
}
// тест, что mov и мода 0 работают верно в mov R5, R3
 void test_mov()
{
            //trace(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    cmd.do_command();
    assert(reg[3] = 34);
    assert(reg[5] = 34);
            //trace(TRACE, " ... OK\n");
    printf(" ... OK\n");
}

void test_mode1_toreg()
{
            //trace(TRACE, __FUNCTION__)
    // setup
    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 34);


    Command cmd = parse_cmd(0011503);


    assert(ss.val == 34);
    assert(ss.a == 0200);
    assert(dd.val == 12);
    assert(dd.a == 3);


    cmd.do_command();

    assert(reg[3] = 34);
    // проверяем, что значение регистра не изменилось
    assert(reg[5] = 0200);

            //trace(TRACE, " ... OK\n");
    printf(" ... OK\n");
}

void test_mode2_toreg()
{
    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 34);


    Command cmd = parse_cmd(0011503);


    assert(ss.val == 34);
    assert(ss.a == 0200);
    assert(dd.val == 12);
    assert(dd.a == 3);

    cmd.do_command();

    assert(reg[3] = 34);

    // проверяем, что значение регистра увеличилось на 2
    assert(reg[5] = 0202);

            //trace(TRACE, " ... OK\n");
    printf(" ... OK\n");
}
