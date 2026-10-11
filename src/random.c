#include "random.h"

DxBallUInt dxball_random_state = 1;

/* FUNCTION: DXBALL 0x004179F0 */
void dxball_crt_srand(DxBallUInt seed)
{
    dxball_random_state = seed;
}

/* FUNCTION: DXBALL 0x00417A00 */
DxBallInt dxball_crt_rand(void)
{
    /* Unsigned arithmetic retains the original low-word wrapping on every host. */
    dxball_random_state = dxball_random_state * 214013U + 2531011U;
    return (DxBallInt)((dxball_random_state & 0x7fff0000U) >> 16);
}
