extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00404040 */
void dxball_draw_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    ((DxBallDDSurface *)dxball_active_surface)->blt_fast(x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x11);
    return;
}

