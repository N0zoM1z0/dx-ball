#include "runtime_seh.h"

/* FUNCTION: DXBALL 0x004183CC */
DxBallSehDisposition dxball_crt_unwind_handler(DxBallSehExceptionPrefix *exception,
    void *frame, void *context, void **dispatcher)
{
    DxBallSehDisposition result = DXBALL_SEH_CONTINUE_SEARCH;
    (void)context;
    if (exception->flags & 6) {
        *dispatcher = frame;
        result = DXBALL_SEH_COLLIDED_UNWIND;
    }
    return result;
}
