extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x004041F0 */
void dxball_stretch_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                                DxBallInt width, DxBallInt height)
{
    DxBallRect destination;
    destination.left = x;
    destination.top = y;
    destination.right = x + width;
    destination.bottom = y + height;
    ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return;
}

