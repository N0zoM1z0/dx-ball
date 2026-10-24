extern "C" {
#include "display.h"
#include "clock_api.h"
#include "device.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "particles.h"
#include "sound.h"
#include "startup.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00409610 */
void dxball_wait_frames(DxBallInt frames)
{
    DxBallUInt now;
    DxBallInt index;
    index = 0;
    if (dxball_wait_vertical_blank != 0) {
        while (index++ < frames) {
            dxball_direct_draw->vtable->wait_vertical_blank(dxball_direct_draw, 1, NULL);
        }
    } else {
        while (index++ < frames) {
            do {
                now = dxball_current_time();
                if (now < dxball_frame_wait_tick) break;
            } while (now < dxball_frame_wait_tick + 17);
            dxball_frame_wait_tick = dxball_current_time();
        }
    }
    return;
}

