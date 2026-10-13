#include "runtime_access.h"

int dxball_crt_access(const char *path, int mode)
{
    DxBallCrtDword attributes = GetFileAttributesA(path);
    if (attributes == (DxBallCrtDword)-1) {
        dxball_crt_map_os_error(GetLastError());
        return -1;
    }
    if ((attributes & 1) && (mode & 2)) {
        errno = 13;
        _doserrno = 5;
        return -1;
    }
    return 0;
}
