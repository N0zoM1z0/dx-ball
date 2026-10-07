#include "device.h"
#include "paddle.h"
#include <string.h>

void dxball_palette_transition(DxBallInt frames, DxBallInt step,
                               DxBallInt first, DxBallInt last, DxBallInt direction)
{
    DxBallInt index, channel, changed;
    DxBallByte *live, *saved;
    if (dxball_cursor_warp_disabled == 1) return;
    if (direction != 0 && direction != 1) return;
    /* Callers supply a positive step and an inclusive palette range. Zero or
       negative steps can make the original repeat forever and are excluded
       from the differential termination scope. */
    do {
        changed = 0;
        for (index = first; index <= last; ++index) {
            live = (DxBallByte *)&dxball_live_palette[index];
            saved = (DxBallByte *)&dxball_saved_palette[index];
            for (channel = 0; channel < 3; ++channel) {
                if (direction == 0) {
                    if (live[channel] != 0) {
                        if ((DxBallInt)live[channel] < step) live[channel] = 0;
                        else live[channel] = (DxBallByte)(live[channel] - (DxBallByte)step);
                        changed = 1;
                    }
                } else if (live[channel] < saved[channel]) {
                    if ((DxBallInt)saved[channel] - live[channel] < step)
                        live[channel] = saved[channel];
                    else live[channel] = (DxBallByte)(live[channel] + (DxBallByte)step);
                    changed = 1;
                } else if (live[channel] > saved[channel]) {
                    if ((DxBallInt)live[channel] - saved[channel] < step)
                        live[channel] = saved[channel];
                    else live[channel] = (DxBallByte)(live[channel] - (DxBallByte)step);
                    changed = 1;
                }
            }
        }
        dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0,
            (DxBallUInt)first, (DxBallUInt)(last - first + 1), &dxball_live_palette[first]);
        dxball_wait_frames(frames);
    } while (changed);
}

void dxball_initialize_palette(void)
{
    DxBallInt index, result;
    for (index = 0; index < 256; ++index) {
        dxball_live_palette[index].red = dxball_live_palette[index].green =
            dxball_live_palette[index].blue = 0;
        dxball_saved_palette[index].red = dxball_saved_palette[index].green =
            dxball_saved_palette[index].blue = 0;
    }
    result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
        dxball_live_palette, &dxball_direct_palette, NULL);
    if (result == 0) {
        DxBallDDSurface *primary = (DxBallDDSurface *)dxball_primary_surface;
        primary->vtable->set_palette(primary, dxball_direct_palette);
    }
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
