#ifndef DXBALL_CLOCK_API_H
#define DXBALL_CLOCK_API_H

#include "runtime.h"
/* Independent WinMM/kernel import boundaries, not a contiguous original table.
   Host defaults forward the live clock callbacks; Windows binds its SDK adapters. */
typedef char DxBallCounterLayout[(sizeof(DxBallCounter) == 8) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
#if defined(_WIN32)
__declspec(dllimport) unsigned long DXBALL_DDCALL timeGetTime(void);
#else
DxBallUInt DXBALL_DDCALL timeGetTime(void);
#endif
extern DxBallUInt (DXBALL_DDCALL *dxball_time_get_time)(void);
extern DxBallInt (DXBALL_DDCALL *dxball_query_performance_frequency)(DxBallCounter *);
extern DxBallInt (DXBALL_DDCALL *dxball_query_performance_counter)(DxBallCounter *);
#ifdef __cplusplus
}
#endif

#endif
