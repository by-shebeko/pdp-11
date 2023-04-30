#pragma once

typedef unsigned char byte;      // 8 bit
typedef unsigned short int word; // 16 bit
typedef word Adress;             // 16 bit

#define pc reg[7]   // к reg[7] можем обращаться как pc
extern word reg[8];

void b_write(Adress adr, byte b); // записывает в адрес переменную
byte b_read(Adress adr);          // возврат значения байта по адресу
void w_write(Adress adr, word w); // записывыет слово в адесс
word w_read(Adress adr);          // возвращает значение слова по адресу

