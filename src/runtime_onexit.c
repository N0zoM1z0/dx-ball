#include "runtime_onexit.h"

/* FUNCTION: DXBALL 0x0041F7E0 */
DxBallOnExitCallback DXBALL_NEW_CALL dxball_crt_onexit(DxBallOnExitCallback callback)
{
    size_t capacity = dxball_runtime_msize(dxball_onexit_begin);
    size_t used = (size_t)dxball_onexit_end - (size_t)dxball_onexit_begin;
    if (capacity >= used + sizeof(DxBallCrtCallback)) goto append_callback;
    {
        size_t requested = dxball_runtime_msize(dxball_onexit_begin) +
                           4 * sizeof(DxBallCrtCallback);
        DxBallCrtCallback *grown = (DxBallCrtCallback *)dxball_runtime_realloc(
            dxball_onexit_begin, (DxBallUInt)requested);
        DxBallCrtCallback *finish;
        if (grown == NULL) return NULL;
        /* Re-read shared addresses after realloc and its returning callbacks. */
        finish = grown + ((size_t)dxball_onexit_end - (size_t)dxball_onexit_begin) /
                         sizeof(DxBallCrtCallback);
        dxball_onexit_begin = grown;
        dxball_onexit_end = finish;
    }
append_callback:
    *dxball_onexit_end++ = (DxBallCrtCallback)callback;
    return callback;
}

/* FUNCTION: DXBALL 0x0041F860 */
int DXBALL_NEW_CALL dxball_crt_atexit(DxBallCrtCallback callback)
{
    return dxball_crt_onexit((DxBallOnExitCallback)callback) == NULL ? -1 : 0;
}
