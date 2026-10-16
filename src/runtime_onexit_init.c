#include "runtime_onexit_init.h"
#include "runtime_fatal.h"
#include "runtime_onexit.h"

/* FUNCTION: DXBALL 0x0041F880 */
void dxball_crt_initialize_onexit(void)
{
    if ((dxball_onexit_begin = (DxBallCrtCallback *)dxball_runtime_malloc(
            32 * sizeof(DxBallCrtCallback))) == NULL)
        dxball_crt_amsg_exit(24);
    *dxball_onexit_begin = NULL;
    dxball_onexit_end = dxball_onexit_begin;
}
