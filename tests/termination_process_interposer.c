#include "../src/termination.h"
#include "../src/termination_process_api.h"
#include <stdlib.h>

/* The native owner fixture already supplies this controlled returning table.
   Interpose only the genuine API boundary; never terminate the test process. */
void ExitProcess(unsigned int status)
{
    dxball_termination_ops.exit_process(status);
}

/* Controlled tables replace the production preterminators before every case.
   These real dependency boundaries must remain unused in that fixture. */
int dxball_crt_flushall(void) { abort(); }
int dxball_crt_fcloseall(void) { abort(); }
