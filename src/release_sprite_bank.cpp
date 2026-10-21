extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

extern "C" {
#include "resources_bank.h"
}

/* FUNCTION: DXBALL 0x00403EB0 */
void dxball_release_sprite_bank(DxBallInt bank)
{
    DxBallInt sprite, saved_bank;
    saved_bank = dxball_sprite_bank;
    dxball_select_sprite_bank(bank);
    sprite = 0;
    while (sprite <= 254) {
        dxball_release_sprite(sprite);
        ++sprite;
    }
    dxball_sprite_banks[bank].count = 0;
    dxball_sprite_banks[bank].allocation_mode = 0;
    strcpy(dxball_sprite_banks[bank].filename, " ");
    dxball_select_sprite_bank(saved_bank);
    return;
}

