#include "rotation.h"
#include "trig.h"

#include <stdlib.h>

/* FUNCTION: DXBALL 0x004026A0 */
void dxball_render_rotated_sprite(DxBallUInt center_x, DxBallUInt center_y,
                                  DxBallInt slot, DxBallInt angle)
{
    DxBallSprite *sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[slot];
    DxBallDDSurface *destination = (DxBallDDSurface *)dxball_active_surface;
    DxBallDDSurface *source;
    DxBallSurfaceDesc destination_desc, source_desc;
    DxBallUInt width = (DxBallUInt)sprite->width;
    DxBallUInt height = (DxBallUInt)sprite->height;
    DxBallByte *pixel;
    DxBallInt column, row, rounded_x, rounded_y, truncated_x, truncated_y, result;
    double row_x, row_y, x, y, column_dx, column_dy, row_dx, row_dy;
    double first_x_term, first_y_term;
    const double rounding_bias = 0.5;

    /* Dimensions are sampled before API calls; surface globals are read again
       at each API boundary, including lock retries and final unlocks. */
    destination_desc.size = 108;
    destination_desc.flags = 14;
    destination->vtable->get_desc(destination, &destination_desc);
    do {
        destination = (DxBallDDSurface *)dxball_active_surface;
        result = destination->vtable->lock(destination, NULL, &destination_desc, 0, NULL);
    } while (result != 0);
    source_desc.size = 108;
    source_desc.flags = 14;
    source = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface;
    source->vtable->get_desc(source, &source_desc);
    do {
        source = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface;
        result = source->vtable->lock(source, NULL, &source_desc, 0, NULL);
    } while (result != 0);
    pixel = source_desc.pixels;

    first_x_term = (double)((long double)center_x -
        (long double)width * dxball_cosine(angle) / 2.0);
    row_x = (double)((long double)first_x_term -
        (long double)width * dxball_sine(angle) / 2.0);
    first_y_term = (double)((long double)center_y +
        (long double)height * dxball_sine(angle) / 2.0);
    row_y = (double)((long double)first_y_term -
        (long double)height * dxball_cosine(angle) / 2.046);
    column_dx = dxball_cosine(angle);
    column_dy = -dxball_sine(angle);
    row_dx = dxball_cosine(angle + 270);
    row_dy = -dxball_sine(angle + 270);

    for (row = 0; row < (DxBallInt)height; ++row) {
        x = row_x;
        y = row_y;
        for (column = 0; column < (DxBallInt)width; ++column) {
            x += column_dx;
            y += column_dy;
            if (*pixel != 0 && y > 0.0 && y < (double)(destination_desc.height - 1)
                && x > 0.0 && x < (double)(destination_desc.width - 1)) {
                rounded_x = (DxBallInt)((long double)x + rounding_bias);
                rounded_y = (DxBallInt)((long double)y + rounding_bias);
                truncated_x = (DxBallInt)x;
                truncated_y = (DxBallInt)y;
                destination_desc.pixels[rounded_y * destination_desc.pitch + rounded_x] = *pixel;
                if (rounded_x != truncated_x || rounded_y != truncated_y)
                    destination_desc.pixels[truncated_y * destination_desc.pitch + rounded_x] = *pixel;
            }
            ++pixel;
        }
        /* The original uses the executed column count for zero-width rows. */
        pixel += source_desc.pitch - column;
        row_x += row_dx;
        row_y += row_dy;
    }
    destination = (DxBallDDSurface *)dxball_active_surface;
    destination->vtable->unlock(destination, NULL);
    source = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface;
    source->vtable->unlock(source, NULL);
    return;
}

/* FUNCTION: DXBALL 0x00402CD0 */
DxBallInt dxball_rotated_sprite_offset(DxBallInt slot, DxBallInt angle)
{
    DxBallInt first, second;
    /* Keep division extended until conversion; 13/1.3 truncates to nine. */
    first = abs((DxBallInt)((long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width *
        dxball_cosine(angle + 45) / 1.3));
    second = abs((DxBallInt)((long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width *
        dxball_cosine(angle + 135) / 1.3));
    return -(first > second ? first : second);
}

/* FUNCTION: DXBALL 0x00404280 */
void dxball_draw_rotated_sprite(DxBallInt slot, DxBallUInt center_x,
                               DxBallUInt center_y, DxBallInt angle)
{
    dxball_render_rotated_sprite(center_x, center_y, slot, angle);
    return;
}
