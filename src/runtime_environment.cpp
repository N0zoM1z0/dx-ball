#include "runtime_environment.h"
#include <string.h>

char *dxball_crt_environment_strings(void)
{
    static int backend = 0;
    unsigned short *wide = 0;
    char *ansi = 0;
    char *result;
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
        unsigned short *end;
        int count, bytes;
        if (wide == 0 && (wide = GetEnvironmentStringsW()) == 0)
            return 0;
        end = wide;
        while (*end) {
            while (*++end)
                ;
            ++end;
        }
        count = (int)(end - wide) + 1;
        bytes = WideCharToMultiByte(0, 0, wide, count, 0, 0, 0, 0);
        if (bytes && (result = (char *)dxball_runtime_malloc((DxBallUInt)bytes)) != 0) {
            if (WideCharToMultiByte(0, 0, wide, count, result, bytes, 0, 0) == 0) {
                dxball_heap_release(result);
                result = 0;
            }
            FreeEnvironmentStringsW(wide);
            return result;
        }
        FreeEnvironmentStringsW(wide);
        return 0;
    }
    if (backend == 2) {
        char *end;
        size_t bytes;
        if (ansi == 0 && (ansi = GetEnvironmentStrings()) == 0)
            return 0;
        end = ansi;
        while (*end) {
            while (*++end)
                ;
            ++end;
        }
        bytes = (size_t)(end - ansi) + 1;
        result = (char *)dxball_runtime_malloc((DxBallUInt)bytes);
        if (result == 0) {
            FreeEnvironmentStringsA(ansi);
            return 0;
        }
        memcpy(result, ansi, bytes);
        FreeEnvironmentStringsA(ansi);
        return result;
    }
    return 0;
}
