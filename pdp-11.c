# include <stdio.h>
# include <assert.h>

#include "pdp-mem.h"
#include "pdp-load.h"
#include "pdp-commands.h"
#include "pdp_tests.h"

void run();

int main(int argc, char * argv[])
{
    //test_mem();
    //test_parse_cmd();
    //test_mode0();
    //test_mov();
    //test_mode1_toreg();
    //test_mode5();
    load_file(argv[1]);
    //mem_dump(0x200, 0xc);
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
    run();
    return 0;
}
