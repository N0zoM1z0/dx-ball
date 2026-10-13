#include "runtime_file_modes.h"

/* FUNCTION: DXBALL 0x0041FCC0 */
int _setmode(int descriptor, int mode)
{
    unsigned char *flags;
    unsigned int previous;
    if ((unsigned int)descriptor < (unsigned int)_nhandle) {
        flags = &__pioinfo[descriptor >> 5][descriptor & 31].bytes[4];
        if (*flags & 1) {
            previous = *flags & 0x80;
            if (mode == 0x8000) {
                *flags &= 0x7f;
            } else if (mode == 0x4000) {
                *flags |= 0x80;
            } else {
                errno = 22;
                return -1;
            }
            return previous ? 0x4000 : 0x8000;
        }
    }
    errno = 9;
    return -1;
}
