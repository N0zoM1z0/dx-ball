#include "runtime_environment.h"
#include <string.h>

char *dxball_crt_environment_strings(void)
{
    static int backend = 0;
    unsigned short *wide;
    unsigned short *wide_end;
    char *ansi;
    char *ansi_end;
    int count, bytes;
    if (backend == 0) {
        wide = GetEnvironmentStringsW();
        if (wide)
            backend = 1;
        else {
            ansi = GetEnvironmentStrings();
            if (ansi)
                backend = 2;
            else
                return 0;
        }
    }
    if (backend == 1) {
        if (wide == 0 && (wide = GetEnvironmentStringsW()) == 0)
            return 0;
        wide_end = wide;
        while (*wide_end) {
            if (*++wide_end == 0)
                ++wide_end;
        }
        count = (int)(wide_end - wide) + 1;
        bytes = WideCharToMultiByte(0, 0, wide, count, 0, 0, 0, 0);
        if (bytes == 0 || (ansi = (char *)dxball_runtime_malloc((DxBallUInt)bytes)) == 0) {
            FreeEnvironmentStringsW(wide);
            return 0;
        }
        if (WideCharToMultiByte(0, 0, wide, count, ansi, bytes, 0, 0) == 0) {
            dxball_heap_release(ansi);
            ansi = 0;
        }
        FreeEnvironmentStringsW(wide);
        return ansi;
    }
    if (backend == 2) {
        if (ansi == 0 && (ansi = GetEnvironmentStrings()) == 0)
            return 0;
        ansi_end = ansi;
        while (*ansi_end) {
            if (*++ansi_end == 0)
                ++ansi_end;
        }
        bytes = (int)(ansi_end - ansi) + 1;
        if ((ansi_end = (char *)dxball_runtime_malloc((DxBallUInt)bytes)) == 0) {
            FreeEnvironmentStringsA(ansi);
            return 0;
        }
        memcpy(ansi_end, ansi, (size_t)bytes);
        FreeEnvironmentStringsA(ansi);
        return ansi_end;
    }
    return 0;
}
