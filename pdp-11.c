# include <stdio.h>
# include <assert.h>

#include "pdp-mem.h"
#include "pdp-load.h"
#include "pdp-commands.h"

void run();

void test_mem();

int main(int argc, char * argv[])
{
    // test_mem();
    load_file(argv[1]);
    //mem_dump(0x200, 0xc);
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
    run();
    return 0;
}
