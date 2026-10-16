#include "runtime_locale_handles.h"

/* Original C-locale category defaults and CP_ACP selector. */
DxBallCrtLocaleWord __lc_handle[DXBALL_CRT_LC_COUNT] = { 0, 0, 0, 0, 0, 0 };
unsigned int __lc_codepage = 0;
