extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00404610 */
void dxball_load_sprite_bank(DxBallInt bank, DxBallInt allocation_mode, const char *file)
{
    DxBallUInt raw_size;
    DxBallInt y_adjust;
    DxBallInt source_index;
    DxBallInt destination_stride;
    DxBallSprite *shape;
    DxBallInt h;
    char char_code;
    DxBallInt x;
    DxBallByte *bitmap;
    DxBallInt shape_count;
    DxBallInt shape_number;
    DxBallInt pixel_row;
    DxBallInt old_sprite_bank;
    DxBallInt bitmap_width;

    old_sprite_bank = dxball_sprite_bank;
    dxball_select_sprite_bank(bank);
    for (shape_number = 1; shape_number < 254; shape_number = shape_number + 1)
        dxball_release_sprite(shape_number);
    dxball_board_file = fopen(file, "rb");
    if (dxball_board_file == NULL)
        exit(1);
    fread(&shape_count, 4, 1, dxball_board_file);
    for (shape_number = 1; shape_number < shape_count + 1; shape_number = shape_number + 1) {
        fread(&bitmap_width, 4, 1, dxball_board_file);
        fread(&h, 4, 1, dxball_board_file);
        fread(&char_code, 1, 1, dxball_board_file);
        fread(&y_adjust, 4, 1, dxball_board_file);
        raw_size = bitmap_width * h;
        bitmap = (DxBallByte *)dxball_runtime_malloc(raw_size + 3);
        if (bitmap == NULL)
            exit(1);
        {
            shape = (DxBallSprite *)dxball_runtime_malloc(sizeof(DxBallSprite) + 1);
            if (shape == NULL)
                exit(1);
            dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number] = shape;
        }
        fread(bitmap, 1, raw_size, dxball_board_file);
        dxball_sprite_banks[dxball_sprite_bank].count = shape_count;
        dxball_sprite_banks[dxball_sprite_bank].allocation_mode = allocation_mode;
        strcpy(dxball_sprite_banks[dxball_sprite_bank].filename, file);
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->width = bitmap_width;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->height = h;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->code = char_code;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->baseline = y_adjust;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->source_rect.top = 0;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->source_rect.left = 0;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->source_rect.bottom = h;
        dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->source_rect.right = bitmap_width;
        {
            DxBallColorKey key;
            struct {
                DxBallSurfaceDesc description;
                DxBallInt result;
                DxBallByte *pixel;
            } api;
            api.description.size = sizeof(api.description);
            api.description.flags = 0xf;
            if (dxball_sprite_banks[dxball_sprite_bank].allocation_mode == 1) {
                api.description.caps = 0x40;
            } else {
                api.description.caps = 0x840;
            }
            api.description.height = h;
            api.description.width = bitmap_width;
            api.result = dxball_direct_draw->vtable->create_surface(
                dxball_direct_draw, &api.description,
                &dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->surface, NULL);
            /* Creation failure preserves the target's partial owner and leaks;
               it does not restore the bank, close the stream or free these buffers. */
            if (api.result != 0)
                return;
            key.low = 0;
            key.high = 0;
            dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->surface->set_color_key(8, &key);
            api.description.flags = 0x7f9ee;
            do {
                api.result = dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->surface->get_desc(&api.description);
            } while (api.result != 0);
            /* GetSurfaceDesc supplies the row stride before Lock; later API writes
               to the descriptor or current record do not replace that snapshot. */
            destination_stride = api.description.pitch;
            dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->pitch = destination_stride;
            do {
                api.result = dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->surface->lock(NULL, &api.description, 0, NULL);
            } while (api.result != 0);
            source_index = 0;
            for (pixel_row = h - 1; pixel_row >= 0; --pixel_row) {
                for (x = 0; x <= bitmap_width - 1; ++x) {
                    api.pixel = pixel_row * destination_stride + x + api.description.pixels;
                    *api.pixel = bitmap[source_index];
                    source_index = source_index + 1;
                }
            }
            dxball_sprite_banks[dxball_sprite_bank].sprites[shape_number]->surface->unlock(NULL);
        }
        dxball_heap_release(bitmap);
    }
    fclose(dxball_board_file);
    dxball_select_sprite_bank(old_sprite_bank);
    return;
}

