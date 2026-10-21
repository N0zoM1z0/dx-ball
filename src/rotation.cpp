extern "C" {
#include "rotation.h"
#include "trig.h"
}

#include <stdlib.h>

static const float origin_divisor = 2.0f;

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








/* FUNCTION: DXBALL 0x004026A0 */
void dxball_render_rotated_sprite(DxBallUInt center_x, DxBallUInt center_y,
                                  DxBallInt slot, DxBallInt angle)
{
    struct DxBallRowProjection {
        DxBallUInt width;
        DxBallInt rounded, truncated;
    };
    typedef struct {
        DxBallUInt column;
    } DxBallSourceColumn;
    DxBallInt result;
    DxBallInt row;
    double column_delta_y;
    double column_delta_x;
    double row_delta_x;
    DxBallSurfaceDesc destination_desc;
    double pixelX;
    DxBallUInt width_origin;
    DxBallByte * source_pixel;
    DxBallRowProjection scanline_position;
    DxBallInt pixel_x_rounded;
    DxBallInt truncatedX;
    DxBallUInt unclassified_zero_second;
    DxBallUInt unread_zero_first;
    double row_dy;
    DxBallByte * destinationByte;
    double row_start_y;
    DxBallInt column_number;
    DxBallUInt source_height;
    double pixelY;
    DxBallSurfaceDesc read_desc;
    DxBallSourceColumn source_x;
    double rowX;
    DxBallUInt heightOrigin;

    source_x.column = 0;
    scanline_position.width = (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->width;
    source_height = (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->height;
    /* Two original frame words are zeroed here and never read afterward. */
    unread_zero_first = 0;
    unclassified_zero_second = 0;

    (void)unread_zero_first;
    (void)unclassified_zero_second;

    /* Dimensions are sampled before API calls; surface globals are read again
       at each API boundary, including lock retries and final unlocks. */
    destination_desc.size = 108;
    destination_desc.flags = 14;
    ((DxBallDDSurface *)dxball_active_surface)->get_desc(&destination_desc);
    do {
        result = ((DxBallDDSurface *)dxball_active_surface)->lock(NULL, &destination_desc, 0, NULL);
    } while (result != 0);
    read_desc.size = 108;
    read_desc.flags = 14;
    dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->get_desc(&read_desc);
    do {
        result = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->lock(NULL, &read_desc, 0, NULL);
    } while (result != 0);
    source_pixel = read_desc.pixels;
    width_origin = scanline_position.width;
    heightOrigin = source_height;

    rowX = (double)((long double)(double)(
        -((long double)width_origin * dxball_cosine(angle) / origin_divisor) +
        (long double)center_x) -
        (long double)width_origin * dxball_sine(angle) / origin_divisor);
    row_start_y = (double)((long double)(double)((long double)center_y +
        (long double)heightOrigin * dxball_sine(angle) / origin_divisor) -
        (long double)heightOrigin * dxball_cosine(angle) / 2.046);
    column_delta_x = dxball_cosine(angle);
    column_delta_y = -dxball_sine(angle);
    row_delta_x = dxball_cosine(angle + 270);
    row_dy = -dxball_sine(angle + 270);

    for (row = 0; (DxBallInt)source_height > row; ++row) {
        pixelX = rowX;
        pixelY = row_start_y;
        for (column_number = 0; (DxBallInt)scanline_position.width > column_number; ++column_number) {
            pixelX = column_delta_x + pixelX;
            pixelY = column_delta_y + pixelY;
            if (*source_pixel != 0 && pixelY > 0.0 && pixelY < (double)(destination_desc.height - 1)
                && pixelX > 0.0 && pixelX < (double)(destination_desc.width - 1)) {
                pixel_x_rounded = (DxBallInt)((long double)pixelX + 0.5);
                scanline_position.rounded = (DxBallInt)((long double)pixelY + 0.5);
                truncatedX = (DxBallInt)pixelX;
                scanline_position.truncated = (DxBallInt)pixelY;
                destinationByte = destination_desc.pixels +
                    (DxBallInt)((DxBallUInt)scanline_position.rounded * (DxBallUInt)destination_desc.pitch + (DxBallUInt)pixel_x_rounded);
                *destinationByte = *source_pixel;
                if (pixel_x_rounded != truncatedX || scanline_position.rounded != scanline_position.truncated) {
                    destinationByte = destination_desc.pixels +
                        (DxBallInt)((DxBallUInt)scanline_position.truncated * (DxBallUInt)destination_desc.pitch + (DxBallUInt)pixel_x_rounded);
                    *destinationByte = *source_pixel;
                }
            }
            ++source_x.column;
            if (source_x.column >= scanline_position.width) {
                source_x.column = 0;
                source_pixel += (DxBallInt)(read_desc.pitch - scanline_position.width + 1);
            } else {
                ++source_pixel;
            }
        }
        rowX = row_delta_x + rowX;
        row_start_y = row_dy + row_start_y;
    }
    result = ((DxBallDDSurface *)dxball_active_surface)->unlock(NULL);
    result = dxball_sprite_banks[dxball_sprite_bank].sprites[slot]->surface->unlock(NULL);
    (void)result;
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
