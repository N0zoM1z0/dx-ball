#include "runtime_lowio_read.h"

/* FUNCTION: DXBALL 0x00419ED0 */
int dxball_crt_close(int descriptor)
{
    DxBallCrtDword error;
    if ((unsigned int)descriptor >= (unsigned int)_nhandle ||
        (__pioinfo[descriptor >> 5][descriptor & 31].flags & 1) == 0) {
        errno = 9;
        _doserrno = 0;
        return -1;
    }
    if (descriptor == 1 || descriptor == 2) {
        DxBallCrtOsHandle first_handle = dxball_crt_get_osfhandle(1);
        DxBallCrtOsHandle second_handle = dxball_crt_get_osfhandle(2);
        if (first_handle == second_handle)
            goto close_skipped;
    }
    if (!CloseHandle((void *)dxball_crt_get_osfhandle(descriptor))) {
        error = GetLastError();
        goto retire_handle;
    }
close_skipped:
    error = 0;
retire_handle:
    dxball_crt_free_osfhandle(descriptor);
    if (error != 0) {
        dxball_crt_map_os_error(error);
        return -1;
    }
    __pioinfo[descriptor >> 5][descriptor & 31].flags = 0;
    return 0;
}
