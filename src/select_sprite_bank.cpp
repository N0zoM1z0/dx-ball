extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00403E70 */
void dxball_select_sprite_bank(DxBallInt bank)
{
    dxball_sprite_bank = bank;
    return;
}

