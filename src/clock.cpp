extern "C" {
#include "runtime.h"
#include "clock_api.h"
}

DxBallUInt dxball_current_time(void)
{
    DxBallInt result;
    DxBallCounter value;
    if (dxball_high_resolution_clock != 0) {
        if (dxball_clock_divisor == 0) {
            result = dxball_query_performance_frequency(&value);
            if (result == 0) {
                return timeGetTime();
                /* The original full span retains this unreachable store. */
                dxball_clock_divisor = 0;
            } else {
                dxball_clock_divisor = value.low / 1000;
            }
        }
        dxball_query_performance_counter(&value);
        return value.low / dxball_clock_divisor;
    } else {
        return timeGetTime();
    }
}

DxBallInt dxball_elapsed(DxBallUInt start, DxBallUInt interval)
{
    DxBallUInt now;
    now = dxball_current_time();
    if (start > now) return 1;
    if (interval + start > now) {
        return 0;
    } else {
        return 1;
    }
}

