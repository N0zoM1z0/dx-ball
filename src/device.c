#include "device.h"
#include "paddle.h"
#include <stdlib.h>
#include <string.h>

void dxball_palette_transition(DxBallInt frames, DxBallInt step,
                               DxBallInt first, DxBallInt last, DxBallInt direction)
{
    DxBallInt index, changed;
    if (dxball_cursor_warp_disabled == 1) return;
    /* Positive steps and an inclusive valid range retain the existing
       differential termination scope. Flags bytes are not fade channels. */
    if (direction == 0) {
        do {
            changed = 0;
            for (index = first; index <= last; ++index) {
                if (dxball_live_palette[index].red > 0) {
                    if (dxball_live_palette[index].red < step) dxball_live_palette[index].red = 0;
                    else dxball_live_palette[index].red = dxball_live_palette[index].red - step;
                    changed = 1;
                }
                if (dxball_live_palette[index].green > 0) {
                    if (dxball_live_palette[index].green < step) dxball_live_palette[index].green = 0;
                    else dxball_live_palette[index].green = dxball_live_palette[index].green - step;
                    changed = 1;
                }
                if (dxball_live_palette[index].blue > 0) {
                    if (dxball_live_palette[index].blue < step) dxball_live_palette[index].blue = 0;
                    else dxball_live_palette[index].blue = dxball_live_palette[index].blue - step;
                    changed = 1;
                }
            }
            dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0,
                first, last - first + 1, &dxball_live_palette[first]);
            dxball_wait_frames(frames);
        } while (changed);
    }
    if (direction == 1) {
        do {
            changed = 0;
            for (index = first; index <= last; ++index) {
                if (dxball_live_palette[index].red < dxball_saved_palette[index].red) {
                    if (abs(dxball_live_palette[index].red - dxball_saved_palette[index].red) < step)
                        dxball_live_palette[index].red = dxball_saved_palette[index].red;
                    else dxball_live_palette[index].red = dxball_live_palette[index].red + step;
                    changed = 1;
                } else if (dxball_live_palette[index].red > dxball_saved_palette[index].red) {
                    if (abs(dxball_live_palette[index].red - dxball_saved_palette[index].red) < step)
                        dxball_live_palette[index].red = dxball_saved_palette[index].red;
                    else dxball_live_palette[index].red = dxball_live_palette[index].red - step;
                    changed = 1;
                }
                if (dxball_live_palette[index].green < dxball_saved_palette[index].green) {
                    if (abs(dxball_live_palette[index].green - dxball_saved_palette[index].green) < step)
                        dxball_live_palette[index].green = dxball_saved_palette[index].green;
                    else dxball_live_palette[index].green = dxball_live_palette[index].green + step;
                    changed = 1;
                } else if (dxball_live_palette[index].green > dxball_saved_palette[index].green) {
                    if (abs(dxball_live_palette[index].green - dxball_saved_palette[index].green) < step)
                        dxball_live_palette[index].green = dxball_saved_palette[index].green;
                    else dxball_live_palette[index].green = dxball_live_palette[index].green - step;
                    changed = 1;
                }
                if (dxball_live_palette[index].blue < dxball_saved_palette[index].blue) {
                    if (abs(dxball_live_palette[index].blue - dxball_saved_palette[index].blue) < step)
                        dxball_live_palette[index].blue = dxball_saved_palette[index].blue;
                    else dxball_live_palette[index].blue = dxball_live_palette[index].blue + step;
                    changed = 1;
                } else if (dxball_live_palette[index].blue > dxball_saved_palette[index].blue) {
                    if (abs(dxball_live_palette[index].blue - dxball_saved_palette[index].blue) < step)
                        dxball_live_palette[index].blue = dxball_saved_palette[index].blue;
                    else dxball_live_palette[index].blue = dxball_live_palette[index].blue - step;
                    changed = 1;
                }
            }
            dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0,
                first, last - first + 1, &dxball_live_palette[first]);
            dxball_wait_frames(frames);
        } while (changed);
    }
    return;
}

void dxball_initialize_palette(void)
{
    DxBallInt index, result;
    for (index = 0; index < 256; ++index) {
        dxball_live_palette[index].red = 0;
        dxball_live_palette[index].green = 0;
        dxball_live_palette[index].blue = 0;
        dxball_saved_palette[index].red = 0;
        dxball_saved_palette[index].green = 0;
        dxball_saved_palette[index].blue = 0;
    }
    result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
        dxball_live_palette, &dxball_direct_palette, NULL);
    if (result != 0) return;
    result = ((DxBallDDSurface *)dxball_primary_surface)->vtable->set_palette(
        (DxBallDDSurface *)dxball_primary_surface, dxball_direct_palette);
    if (result != 0) return;
    return;
}

void dxball_clear_surface(DxBallSurface surface, DxBallInt color)
{
    DxBallColorFillFx fill;
    DxBallRect rect = {0, 0, 640, 480};
    DxBallDDSurface *destination = (DxBallDDSurface *)surface;
    memset(&fill, 0, sizeof(fill));
    fill.size = 100;
    fill.fill_color = (DxBallUInt)color;
    destination->vtable->blt(destination, &rect, NULL, NULL, 0x400, &fill);
}

void dxball_restore_sprite_banks(void)
{
    DxBallInt bank, slot;
    DxBallSprite *sprite;
    for (bank = 0; bank < 3; ++bank) {
        if (dxball_sprite_banks[bank].allocation_mode == 1) {
            for (slot = 0; slot < 255; ++slot) {
                sprite = dxball_sprite_banks[bank].sprites[slot];
                if (sprite != NULL && sprite->surface != NULL)
                    sprite->surface->vtable->restore(sprite->surface);
            }
            dxball_runtime_ops.load_sprite_bank(bank, 1, dxball_sprite_banks[bank].filename);
        }
    }
}

void dxball_recover_surfaces(void)
{
    DxBallDDSurface *primary = (DxBallDDSurface *)dxball_primary_surface;
    DxBallDDSurface *board = (DxBallDDSurface *)dxball_board_surface;
    if (primary->vtable->restore(primary) == 0 && board->vtable->restore(board) == 0) {
        dxball_restore_sprite_banks();
        dxball_redraw_mode();
    }
}

void dxball_synchronize_surface(void)
{
    DxBallDDSurface *primary = (DxBallDDSurface *)dxball_primary_surface;
    if (dxball_cursor_warp_disabled == 0) {
        if ((DxBallUInt)primary->vtable->get_blt_status(primary, 1) == 0x887601c2UL)
            dxball_recover_surfaces();
        if (dxball_surface_restore_requested == 1) dxball_surface_restore_requested = 0;
    } else if (dxball_surface_restore_requested == 1) {
        dxball_recover_surfaces();
        dxball_surface_restore_requested = 0;
    }
}
