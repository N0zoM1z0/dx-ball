#include "runtime_lowio_read.h"

/* FUNCTION: DXBALL 0x0041D890 */
int dxball_crt_set_osfhandle(int descriptor, DxBallCrtOsHandle handle)
{
    if ((unsigned int)descriptor < (unsigned int)_nhandle &&
        __pioinfo[descriptor >> 5][descriptor & 31].handle == (void *)(size_t)-1) {
        if (dxball_crt_application_type == 1) {
            switch (descriptor) {
            case 0: SetStdHandle((DxBallCrtDword)-10, (void *)handle); break;
            case 1: SetStdHandle((DxBallCrtDword)-11, (void *)handle); break;
            case 2: SetStdHandle((DxBallCrtDword)-12, (void *)handle); break;
            }
        }
        __pioinfo[descriptor >> 5][descriptor & 31].handle = (void *)handle;
        return 0;
    } else {
        errno = 9;
        _doserrno = 0;
        return -1;
    }
}

/* FUNCTION: DXBALL 0x0041D940 */
int dxball_crt_free_osfhandle(int descriptor)
{
    if ((unsigned int)descriptor < (unsigned int)_nhandle &&
        (__pioinfo[descriptor >> 5][descriptor & 31].flags & 1) &&
        __pioinfo[descriptor >> 5][descriptor & 31].handle != (void *)(size_t)-1) {
        if (dxball_crt_application_type == 1) {
            switch (descriptor) {
            case 0: SetStdHandle((DxBallCrtDword)-10, NULL); break;
            case 1: SetStdHandle((DxBallCrtDword)-11, NULL); break;
            case 2: SetStdHandle((DxBallCrtDword)-12, NULL); break;
            }
        }
        __pioinfo[descriptor >> 5][descriptor & 31].handle = (void *)(size_t)-1;
        return 0;
    } else {
        errno = 9;
        _doserrno = 0;
        return -1;
    }
}
