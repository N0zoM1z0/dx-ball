extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00404280 */
void dxball_draw_rotated_sprite(DxBallInt slot, DxBallUInt center_x,
                               DxBallUInt center_y, DxBallInt angle)
{
    dxball_render_rotated_sprite(center_x, center_y, slot, angle);
    return;
}

