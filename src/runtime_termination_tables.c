#include "termination.h"
#include "runtime_stdio_finalization.h"
#include <stddef.h>

/* Keep the consumer's two pretermination slots in their existing typed array. */
#if defined(_MSC_VER)
#define DXBALL_CRT_SECTION(name)
#else
#define DXBALL_CRT_SECTION(name) __attribute__((used, section(name)))
#endif

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XPA")
#endif
DxBallCrtCallback dxball_preterminators[2] DXBALL_CRT_SECTION(".CRT$XPA") = {
    NULL, dxball_crt_end_stdio
};

#if defined(_MSC_VER)
#pragma data_seg(".CRT$XTA")
#endif
DxBallCrtCallback dxball_terminators[1] DXBALL_CRT_SECTION(".CRT$XTA") = { NULL };

#if defined(_MSC_VER)
#pragma data_seg()
#endif
