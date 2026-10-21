extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00403F70 */
void dxball_blt_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect destination;
    destination.left = x;
    destination.top = y;
    destination.right = x
                        + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width;
    destination.bottom = y
                         + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height;
    ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return;
}

