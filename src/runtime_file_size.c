#include "runtime_file_size.h"
#include <string.h>

/* FUNCTION: DXBALL 0x0041F670 */
int dxball_crt_chsize(int descriptor, DxBallCrtLong size)
{
    int status = 0;
    DxBallCrtLong position, end, remaining;
    if ((unsigned int)descriptor >= (unsigned int)_nhandle ||
        (__pioinfo[descriptor >> 5][descriptor & 31].flags & 1) == 0) {
        errno = 9;
        return -1;
    }
    position = dxball_crt_seek(descriptor, 0, 1);
    if (position == -1 || (end = dxball_crt_seek(descriptor, 0, 2)) == -1) return -1;
    remaining = size - end;
    if (remaining > 0) {
        char zeros[4096];
        int mode;
        memset(zeros, 0, sizeof(zeros));
        mode = _setmode(descriptor, 0x8000);
        do {
            unsigned int chunk = 4096;
            int written;
            if (remaining < 4096) chunk = (unsigned int)remaining;
            written = dxball_crt_write(descriptor, zeros, chunk);
            if (written == -1) {
                if (_doserrno == 5) errno = 13;
                status = written;
                break;
            }
            remaining -= written;
        } while (remaining > 0);
        _setmode(descriptor, mode);
    } else if (remaining < 0) {
        dxball_crt_seek(descriptor, size, 0);
        status = SetEndOfFile((void *)dxball_crt_get_osfhandle(descriptor)) ? 0 : -1;
        if (status == -1) {
            errno = 13;
            _doserrno = GetLastError();
        }
    }
    dxball_crt_seek(descriptor, position, 0);
    return status;
}
