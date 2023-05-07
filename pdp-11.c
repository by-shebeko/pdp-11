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
    //test_NZC();
    //test_mov();
    //test_mode1_toreg();
    //test_mode5();
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

    load_file(argv[1]);
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

    mem_dump(0x40, 0x5);
    mem_dump(0x200, 0x10);
    fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
    run();
    return 0;
}
