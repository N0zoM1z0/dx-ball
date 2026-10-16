#ifndef DXBALL_RUNTIME_LOCALE_HANDLES_H
#define DXBALL_RUNTIME_LOCALE_HANDLES_H

#include "runtime_case_conversion.h"

typedef enum DxBallCrtLocaleCategory {
    DXBALL_CRT_LC_ALL = 0,
    DXBALL_CRT_LC_COLLATE = 1,
    DXBALL_CRT_LC_CTYPE = 2,
    DXBALL_CRT_LC_MONETARY = 3,
    DXBALL_CRT_LC_NUMERIC = 4,
    DXBALL_CRT_LC_TIME = 5,
    DXBALL_CRT_LC_COUNT = 6
} DxBallCrtLocaleCategory;

#ifdef __cplusplus
extern "C" {
#endif

/* These handles are 32-bit LCID values on both Win32 and native hosts. */
extern DxBallCrtLocaleWord __lc_handle[DXBALL_CRT_LC_COUNT];
extern unsigned int __lc_codepage;

#ifdef __cplusplus
}
#endif
#endif
