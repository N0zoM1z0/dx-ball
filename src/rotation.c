#include "rotation.h"
#include "trig.h"

#include <stdlib.h>

static const float origin_divisor = 2.0f;

/* FUNCTION: DXBALL 0x004026A0 */
void dxball_render_rotated_sprite(DxBallUInt center_x, DxBallUInt center_y,
                                  DxBallInt slot, DxBallInt angle)
{
    DxBallUInt source_column = 0;
    DxBallUInt width = (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width;
    DxBallUInt height = (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height;
    /* Two original frame words are zeroed here and never read afterward. */
    DxBallUInt unclassified_zero_first = 0, unclassified_zero_second = 0;
    DxBallSurfaceDesc destination_desc, source_desc;
    DxBallUInt origin_width, origin_height;
    DxBallByte *pixel;
    DxBallInt column, row, result;
    double row_x, row_y, x, y, column_dx, column_dy, row_dx, row_dy;
    double first_x_term, first_y_term;

    (void)unclassified_zero_first;
    (void)unclassified_zero_second;

    /* Dimensions are sampled before API calls; surface globals are read again
       at each API boundary, including lock retries and final unlocks. */
    destination_desc.size = 108;
    destination_desc.flags = 14;
    ((DxBallDDSurface *)dxball_active_surface)->vtable->get_desc(
        (DxBallDDSurface *)dxball_active_surface, &destination_desc);
    do {
        result = ((DxBallDDSurface *)dxball_active_surface)->vtable->lock(
            (DxBallDDSurface *)dxball_active_surface, NULL, &destination_desc, 0, NULL);
    } while (result != 0);
    source_desc.size = 108;
    source_desc.flags = 14;
    dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->vtable->get_desc(
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface, &source_desc);
    do {
        result = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->vtable->lock(
            dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface,
            NULL, &source_desc, 0, NULL);
    } while (result != 0);
    pixel = source_desc.pixels;
    origin_width = width;
    origin_height = height;

    first_x_term = (double)(-((long double)origin_width * dxball_cosine(angle) / origin_divisor) +
        (long double)center_x);
    row_x = (double)((long double)first_x_term -
        (long double)origin_width * dxball_sine(angle) / origin_divisor);
    first_y_term = (double)((long double)center_y +
        (long double)origin_height * dxball_sine(angle) / origin_divisor);
    row_y = (double)((long double)first_y_term -
        (long double)origin_height * dxball_cosine(angle) / 2.046);
    column_dx = dxball_cosine(angle);
    column_dy = -dxball_sine(angle);
    row_dx = dxball_cosine(angle + 270);
    row_dy = -dxball_sine(angle + 270);

    for (row = 0; (DxBallInt)height > row; ++row) {
        x = row_x;
        y = row_y;
        for (column = 0; (DxBallInt)width > column; ++column) {
            x = column_dx + x;
            y = column_dy + y;
            if (*pixel != 0 && y > 0.0 && y < (double)(destination_desc.height - 1)
                && x > 0.0 && x < (double)(destination_desc.width - 1)) {
                DxBallInt rounded_x, rounded_y, truncated_x, truncated_y;
                DxBallByte *destination_pixel;
                rounded_x = (DxBallInt)((long double)x + 0.5);
                rounded_y = (DxBallInt)((long double)y + 0.5);
                truncated_x = (DxBallInt)x;
                truncated_y = (DxBallInt)y;
                destination_pixel = destination_desc.pixels + (rounded_y * destination_desc.pitch + rounded_x);
                *destination_pixel = *pixel;
                if (rounded_x != truncated_x || rounded_y != truncated_y) {
                    destination_pixel = destination_desc.pixels + (truncated_y * destination_desc.pitch + rounded_x);
                    *destination_pixel = *pixel;
                }
            }
            ++source_column;
            if (source_column >= width) {
                source_column = 0;
                pixel += source_desc.pitch - width + 1;
            } else {
                ++pixel;
            }
        }
        row_x = row_dx + row_x;
        row_y = row_dy + row_y;
    }
    result = ((DxBallDDSurface *)dxball_active_surface)->vtable->unlock(
        (DxBallDDSurface *)dxball_active_surface, NULL);
    result = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->vtable->unlock(
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface, NULL);
    (void)result;
    return;
}

/* FUNCTION: DXBALL 0x00402CD0 */
DxBallInt dxball_rotated_sprite_offset(DxBallInt slot, DxBallInt angle)
{
    DxBallInt projections[2];
    /* Keep division extended until conversion; 13/1.3 truncates to nine. */
    projections[0] = abs((DxBallInt)(dxball_cosine(angle + 45) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width / 1.3));
    projections[1] = abs((DxBallInt)(dxball_cosine(angle + 135) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width / 1.3));
    if (projections[1] < projections[0]) {
        return -projections[0];
    } else {
        return -projections[1];
    }
}







/* FUNCTION: DXBALL 0x00404280 */
void dxball_draw_rotated_sprite(DxBallInt slot, DxBallUInt center_x,
                               DxBallUInt center_y, DxBallInt angle)
{
    dxball_render_rotated_sprite(center_x, center_y, slot, angle);
    return;
}

/* FUNCTION: DXBALL 0x00402DE0 */
DxBallInt dxball_rotated_sprite_y_offset(DxBallInt slot, DxBallInt angle)
{
    DxBallInt projections[2];
    projections[0] = abs((DxBallInt)(dxball_sine(angle + 45) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height));
    projections[1] = abs((DxBallInt)(dxball_sine(angle + 135) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height));
    if (projections[1] < projections[0]) {
        return -projections[0];
    } else {
        return -projections[1];
    }
}

/* FUNCTION: DXBALL 0x00402EA0 */
DxBallInt dxball_rotated_sprite_width(DxBallInt slot, DxBallInt angle)
{
    DxBallInt projections[2];
    projections[0] = abs((DxBallInt)(dxball_cosine(angle + 45) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width / 1.3));
    projections[1] = abs((DxBallInt)(dxball_cosine(angle + 135) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width / 1.3));
    if (projections[1] < projections[0]) {
        return projections[0] * 2;
    } else {
        return projections[1] * 2;
    }
}

/* FUNCTION: DXBALL 0x00402FB0 */
DxBallInt dxball_rotated_sprite_height(DxBallInt slot, DxBallInt angle)
{
    DxBallInt projections[2];
    projections[0] = abs((DxBallInt)(dxball_sine(angle + 45) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height));
    projections[1] = abs((DxBallInt)(dxball_sine(angle + 135) * (long double)
        dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height));
    if (projections[1] < projections[0]) {
        return projections[0] * 2;
    } else {
        return projections[1] * 2;
    }
}
