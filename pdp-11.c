# include <stdio.h>
# include <assert.h>

#include "pdp-mem.h"
#include "pdp-load.h"
#include "pdp-commands.h"
#include "pdp_tests.h"

void run();

int main(int argc, char * argv[])
{
    test_mem();
    printf("\n\n%d\n\n", sizeof(word));
    //test_parse_cmd();
    test_NZC();
    //test_mov();
    //test_mode1_toreg();
    //test_mode5();
    //load_file(argv[1]);
    //mem_dump(0x40, 0x5);
    //mem_dump(0x200, 0x12);
    //fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
    //run();
    return 0;
}
