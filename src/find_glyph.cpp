extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

DxBallInt dxball_find_glyph(char code)
{
    DxBallInt sprite = 0;
    do {
        sprite = sprite + 1;
    } while (dxball_sprite_banks[dxball_font_bank].count > sprite &&
             (signed char)dxball_sprite_banks[dxball_font_bank].sprites[sprite]->code != (signed char)code);
    if (dxball_sprite_banks[dxball_font_bank].count == sprite)
        sprite = 0;
    return sprite;
}

