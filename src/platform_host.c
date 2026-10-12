/* Shared SDK transports. Windows binds its adapters; native callers retain
   live callbacks with the same argument/result contracts. */
#include "platform.h"
#include "clock_api.h"
#include <stdlib.h>

DxBallDrawFactory dxball_draw_factory_backend;

static DxBallUInt DXBALL_DDCALL clock_time(void)
{
    return dxball_clock_ops.time_ms();
}

static DxBallInt DXBALL_DDCALL clock_frequency(DxBallCounter *value)
{
    return dxball_clock_ops.frequency(value);
}

static DxBallInt DXBALL_DDCALL clock_counter(DxBallCounter *value)
{
    return dxball_clock_ops.counter(value);
}

DxBallUInt (DXBALL_DDCALL *dxball_time_get_time)(void) = clock_time;
#if !defined(_WIN32)
DxBallUInt DXBALL_DDCALL timeGetTime(void)
{
    return dxball_time_get_time();
}
#endif

DxBallInt (DXBALL_DDCALL *dxball_query_performance_frequency)(DxBallCounter *) = clock_frequency;
DxBallInt (DXBALL_DDCALL *dxball_query_performance_counter)(DxBallCounter *) = clock_counter;

DxBallInt DXBALL_DDCALL dxball_direct_draw_create(void *guid,
    DxBallDDraw **device, void *outer)
{
    if (dxball_draw_factory_backend == NULL) return (DxBallInt)0x80004005UL;
    return dxball_draw_factory_backend(guid, device, outer);
}

void (*dxball_process_exit_backend)(DxBallInt);

void dxball_process_exit(DxBallInt status)
{
    if (dxball_process_exit_backend != NULL)
        dxball_process_exit_backend(status);
    exit(status);
}
