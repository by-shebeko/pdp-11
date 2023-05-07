#include <stdio.h>

#include "pdp-load.h"

void load_file(const char* filename) 
{
	Adress mem_adr = 0x0000;						
	word N = 0x0000;

	byte b = 0x00; //в неё считаются 
	word i = 0x0000;
	//w_write(ostat, 0xffff);
	
	FILE* fin = fopen(filename, "r"); //открытие файла для чтения. Если файла не существует, работа программы завершиться с ошибкой.
	
	while (fscanf(fin ,"%4hx %4hx", &mem_adr, &N) > 1) 
    {
		for (i = 0x0000; i < N; i++) 
        {
			fscanf(fin ,"%2hhx", &b); //считываем значение
			b_write(mem_adr + i, b);  //записываем в массив с данными и двигаем указатель
		}
	}
	fclose(fin);
}

void mem_dump(Adress k, int n) 
{
	printf("\nMemory dumping \n");
	int i;
	for (i = k; i < k + n; i = i + 2) 
	{
		printf("%07o : %04x\n", i, w_read(i));
	}
}
