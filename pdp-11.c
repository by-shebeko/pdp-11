# include <stdio.h>
# include <assert.h>

#include "pdp-mem.h"
#include "pdp-load.h"


void test_mem();

int main(int argc, char * argv[])
{
    // test_mem();
    load_file(argv[1]);
    mem_dump(0x200, 0xc);
    return 0;
}
