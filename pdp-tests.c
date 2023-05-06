//#ifdef AAA

#include "pdp-mem.h"
#include "pdp-commands.h"
#include "pdp-register.h"
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include "pdp_tests.h"
#include <stdio.h>


void test_mem()
{
    Adress a;
    byte b0, b1, bres;
    word w, wres;


    // пишем байт, читаем байт
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 20;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    //отладочная печать a, b0, bres
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);
    // аналогично стоит проверить чтение и запись по нечетному адресу


    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 12;        // другой адрес
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);


    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 14;        // другой адрес
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

// тест, что мы правильно определяем команды mov, add, halt
void test_parse_cmd()
{
    printf ("test parse mov\n");  

    Command cmd = parse_cmd(0011111);
    assert(0 == strcmp(cmd.name, "mov"));
    printf(" ... OK1\n");

    printf ("test parse halt\n");    
    cmd = parse_cmd(0000000);
    assert(0 == strcmp(cmd.name, "halt"));
    printf(" ... OK2\n");

    printf ("test parse add\n");    
    cmd = parse_cmd(0061111);
    assert(0 == strcmp(cmd.name, "add"));
    printf(" ... OK3\n");
}

// тест, что мы разобрали правильно аргументы ss и dd в mov R5, R3
void test_mode0()
{
    printf ("test mode 0\n");    
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503); 
    assert(ss.val == 34);
    assert(ss.a == 5);
    assert(dd.val == 12);
    assert(dd.a == 3);
    printf(" ... OK\n");
}

// тест, что mov и мода 0 работают верно в mov R5, R3
 void test_mov()
{
    printf ("test mov\n");    
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    cmd.do_command();
    assert(reg[3] == 34);
    assert(reg[5] == 34);
    printf(" ... OKe\n");
}

void test_mode1_toreg()
{
    printf ("test mode 1\n");    
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

    assert(reg[3] == 34);
    // проверяем, что значение регистра не изменилось
    assert(reg[5] == 0200);

    printf(" ... OK!!!\n");
}

void test_mode2_toreg()
{
    printf ("test mode 2\n");  

    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 34);

    Command cmd = parse_cmd(0012503);
    assert(ss.val == 34);
    assert(ss.a == 0200);
    assert(dd.val == 12);
    assert(dd.a == 3);

    cmd.do_command();

    assert(reg[3] == 34);
    // проверяем, что значение регистра увеличилось на 2
    assert(reg[5] == 0202);

    printf(" ... OK :)))\n");
}

void test_mode3_toreg()
{
    printf ("test mode 3\n"); 


    w_write(0776, 5);           //в адрес кладём значение, которое хотим получить в к
    printf("%d\n",w_read(0776));  //0776 = 510

    reg[1] = 12;    // dd
    reg[3] = 01010;  // ss
    w_write(01010, 0776); //записали адрес в адрес
    
    Command cmd = parse_cmd(0013301); //mov @(R3)+ R1
    assert(ss.a == 0776);
    assert(ss.val == 5);
    assert(dd.val == 12);
    assert(dd.a == 1);

    cmd.do_command();

    // проверяем, что значение регистра увеличилось на 2
    assert(reg[3] == 01012);    
    assert(reg[1] == 5);
    

    printf(" ... OK ;;)\n");
}

void test_mode4()
{
    printf ("test mode 4\n"); 

    reg[3] = 12;    // dd
    reg[5] = 0202;  // ss
    w_write(0200, 34);

    Command cmd = parse_cmd(0014503);

    assert(ss.val == 34);
    assert(ss.a == 0200);
    assert(dd.val == 12);
    assert(dd.a == 3);

    cmd.do_command();

    assert(reg[3] == 34);
    // проверяем, что значение регистра уменьшилось на 2
    assert(reg[5] == 0200);
    printf(" ... OKeee\n");
}

void test_mode5()
{
    printf ("test mode 5\n"); 

    w_write(0776, 5);           //в адрес кладём значение, которое хотим получить
    printf("%d\n",w_read(0776));  //0776 = 510

    reg[1] = 12;    // dd
    reg[3] = 01012;  // ss
    w_write(01010, 0776); //записали адрес в адрес
    
    Command cmd = parse_cmd(0015301); //mov @-(R3) R1
    assert(ss.a == 0776);
    assert(ss.val == 5);
    assert(dd.val == 12);
    assert(dd.a == 1);

    cmd.do_command();

    // проверяем, что значение регистра уменьшилось на 2
    assert(reg[3] == 01010);    
    assert(reg[1] == 5);
    

    printf(" ... OK :()\n");
}

void test_NZC()
{
    printf ("test flags N Z C\n");

    printf ("test -1 + (-1)\n");
    
    reg[3] = -1;
    reg[5] = -1;

    Command cmd = parse_cmd(0060305); //складываем значения из 3го и 5го регистров и записываем в 3
    cmd.do_command();

    word res = reg[5];   //1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| = -2
    
    set_NZ (res);
    print_NZC();

    assert (N == 1);
    assert (Z == 0);
    assert (C == 1);

    printf ("test -1 + 1\n");
    reg[3] = -1;
    reg[5] = 1;

    cmd = parse_cmd(0060305); //складываем значения из 3го и 5го регистров и записываем в 3
    cmd.do_command();

    res = reg[5];   //1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| = -2
    set_NZ (res);
    print_NZC();

    assert (N == 0);
    assert (Z == 1);
    assert (C == 1);

    printf ("test 16384 + 16384 (sign overflow)\n");
    reg[3] = 16384; // 1 0..0
    reg[5] = 16384;

    cmd = parse_cmd(0060305); //складываем значения из 3го и 5го регистров и записываем в 3
    cmd.do_command();

    res = reg[5];   //1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| = -2
    printf("%x", res);
    set_NZ (res);
    print_NZC();

    assert (N == 1);
    assert (Z == 0);
    assert (C == 0);

    printf("don't worry be happy!");



    


}
//#endif