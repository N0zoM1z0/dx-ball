#include "../src/termination.h"
#include "../src/termination_process_api.h"

/* The native owner fixture already supplies this controlled returning table.
   Interpose only the genuine API boundary; never terminate the test process. */
void ExitProcess(unsigned int status)
{
    dxball_termination_ops.exit_process(status);
}
