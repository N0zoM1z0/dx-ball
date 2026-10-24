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

DxBallInt dxball_draw_glyph(char code, DxBallInt x, DxBallInt baseline)
{
    DxBallInt sprite;
    DxBallRect destination;
    sprite = dxball_find_glyph((signed char)code);
    if (sprite != 0) {
        destination.left = x;
        destination.top = baseline
                         - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->height
                         - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
        destination.right = dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width + x;
        destination.bottom = baseline
                            - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
        ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
            dxball_sprite_banks[dxball_font_bank].sprites[sprite]->surface,
            &dxball_sprite_banks[dxball_font_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
        return dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width;
    } else {
        return 0;
    }
}

