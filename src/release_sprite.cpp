extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00404BE0 */
void dxball_release_sprite(DxBallInt sprite)
{
    if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] == NULL) return;
    if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface != NULL) {
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->release();
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface = NULL;
    }
    dxball_heap_release(dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]);
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = NULL;
    return;
}

