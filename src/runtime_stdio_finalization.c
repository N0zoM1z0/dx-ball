#include "runtime_stdio_finalization.h"
#include "runtime_file_size.h"
#include "termination.h"

/* FUNCTION: DXBALL 0x0041DB60 */
void dxball_crt_end_stdio(void)
{
    dxball_crt_flushall();
    if (dxball_exit_flag)
        dxball_crt_fcloseall();
}
