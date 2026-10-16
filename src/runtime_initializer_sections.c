#include "runtime_initialization.h"
#include <stddef.h>

/* COFF sorts the contributions between each pair of boundary records. */
#if defined(_MSC_VER)
#define DXBALL_CRT_SECTION(name)
#else
#define DXBALL_CRT_SECTION(name) __attribute__((used, section(name)))
#endif

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XIA")
#endif
DxBallCrtCallback __xi_a[] DXBALL_CRT_SECTION(".CRT$XIA") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XIZ")
#endif
DxBallCrtCallback __xi_z[] DXBALL_CRT_SECTION(".CRT$XIZ") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XCA")
#endif
DxBallCrtCallback __xc_a[] DXBALL_CRT_SECTION(".CRT$XCA") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XCZ")
#endif
DxBallCrtCallback __xc_z[] DXBALL_CRT_SECTION(".CRT$XCZ") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XPZ")
#endif
DxBallCrtCallback __xp_z[] DXBALL_CRT_SECTION(".CRT$XPZ") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XTZ")
#endif
DxBallCrtCallback __xt_z[] DXBALL_CRT_SECTION(".CRT$XTZ") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg()
#pragma comment(linker, "/merge:.CRT=.data")
#endif
