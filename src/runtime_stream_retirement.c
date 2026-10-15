#include "runtime_file_size.h"

/* FUNCTION: DXBALL 0x0041F5F0 */
int dxball_crt_fcloseall(void)
{
    int closed = 0;
    int index;
    for (index = 3; index < dxball_crt_stream_limit; ++index) {
        if (dxball_crt_streams[index] != NULL) {
            if ((dxball_crt_streams[index]->flags & 0x83) &&
                dxball_crt_fclose(dxball_crt_streams[index]) != -1) ++closed;
            if (index >= 20) {
                dxball_heap_release(dxball_crt_streams[index]);
                dxball_crt_streams[index] = NULL;
            }
        }
    }
    return closed;
}
