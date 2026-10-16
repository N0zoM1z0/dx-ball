#include "runtime_fatal.h"
#include "runtime_stdio_initialization.h"
#include "runtime_resize.h"

/* FUNCTION: DXBALL 0x0041DA90 */
void dxball_crt_initialize_stdio(void)
{
    int index;

    if (dxball_crt_stream_limit == 0)
        dxball_crt_stream_limit = 512;
    else if (dxball_crt_stream_limit < 20)
        dxball_crt_stream_limit = 20;

    if ((dxball_crt_streams = (DxBallCrtStream **)dxball_runtime_calloc(
            dxball_crt_stream_limit, sizeof(*dxball_crt_streams))) == NULL) {
        dxball_crt_stream_limit = 20;
        if ((dxball_crt_streams = (DxBallCrtStream **)dxball_runtime_calloc(
                dxball_crt_stream_limit, sizeof(*dxball_crt_streams))) == NULL)
            dxball_crt_amsg_exit(26);
    }

    for (index = 0; index < 20; ++index)
        dxball_crt_streams[index] = &dxball_crt_standard_streams[index];

    for (index = 0; index < 3; ++index) {
        if (__pioinfo[index >> 5][index & 31].handle == (void *)-1 ||
            __pioinfo[index >> 5][index & 31].handle == NULL)
            dxball_crt_standard_streams[index].descriptor = -1;
    }
}
