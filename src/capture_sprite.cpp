extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x004042B0 */
void dxball_capture_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                           DxBallInt width, DxBallInt height)
{
    DxBallColorKey key;
    DxBallRect capture;
    dxball_release_sprite(sprite);
    {
        DxBallSprite *record;
        /* The target requests 45 bytes for the 44-byte x86 record. The last byte's
           purpose is unclassified; pointer-sized host storage grows naturally. */
        record = (DxBallSprite *)dxball_runtime_malloc(sizeof(DxBallSprite) + 1);
        if (record == NULL)
            exit(1);
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = record;
    }
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width = width;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height = height;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->code = 0;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->baseline = 0;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect.top = 0;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect.left = 0;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect.bottom = height;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect.right = width;
    {
        struct {
            DxBallSurfaceDesc description;
            DxBallInt result;
        } api;
        api.description.size = sizeof(api.description);
        api.description.flags = 0xf;
        api.description.caps = 0x840;
        api.description.height = height;
        api.description.width = width;
        api.result = dxball_direct_draw->vtable->create_surface(
            dxball_direct_draw, &api.description,
            &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface, NULL);
        if (api.result != 0) return;
        key.low = 0;
        key.high = 0;
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->set_color_key(8, &key);
        api.description.flags = 0x7f9ee;
        do {
            api.result = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->get_desc(&api.description);
        } while (api.result != 0);
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->pitch = api.description.pitch;
    }
    capture.left = x;
    capture.top = y;
    capture.right = width + x;
    capture.bottom = height + y;
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->blt(&dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        (DxBallDDSurface *)dxball_active_surface, &capture, 0x1000000, NULL);
    return;
}

