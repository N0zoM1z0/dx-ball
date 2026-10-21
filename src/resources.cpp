extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

DxBallSpriteBank dxball_sprite_banks[3];
DxBallInt dxball_sprite_bank, dxball_font_bank;
DxBallDDraw *dxball_direct_draw;
DxBallDDPalette *dxball_direct_palette;
DxBallPaletteEntry dxball_live_palette[256], dxball_saved_palette[256];

/* Only the two observed signed maxima are interpreted from the disk header. */
typedef struct DxBallPcxHeader {
    DxBallByte prefix[8];
    signed short xmax, ymax;
    DxBallByte remainder[116];
} DxBallPcxHeader;

typedef char DxBallPcxHeaderMustBe128Bytes[(sizeof(DxBallPcxHeader) == 128) ? 1 : -1];

/* Preserve the observed byte-range check and independently updated source row. */
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

/* FUNCTION: DXBALL 0x00409BB0
   Preserve the observed inclusive xmax*ymax limit, including truncated last
   rows and packet overshoot. This is the game decoder, not a general PCX reader. */
void dxball_load_pcx(DxBallDDSurface *surface, const char *path,
                     DxBallInt palette_mode, DxBallInt x, DxBallInt y)
{
    DxBallSurfaceDesc description;
    DxBallPcxHeader header;
    DxBallByte *header_bytes, *pixel;
    DxBallByte value;
    FILE *file;
    DxBallInt width, height, pitch, xmax, ymax;
    DxBallInt column, row, destination_x, destination_y, decoded, run, result;
    DxBallInt header_index, run_index;
    description.size = sizeof(description);
    description.flags = 0xe;
    surface->get_desc(&description);
    width = description.width;
    height = description.height;
    pitch = description.pitch;
    destination_x = x;
    destination_y = y;
    column = 0;
    row = 0;
    file = fopen(path, "rb");
    header_bytes = (DxBallByte *)&header;
    for (header_index = 0; header_index < 128; header_index = header_index + 1)
        header_bytes[header_index] = (DxBallByte)getc(file);
    xmax = header.xmax;
    ymax = header.ymax;
    do {
        result = surface->lock(NULL, &description, 0, NULL);
    } while (result != 0);
    pixel = description.pixels;
    decoded = 0;
    while (xmax * ymax >= decoded) {
        value = (DxBallByte)getc(file);
        if ((DxBallInt)value >= 192 && (DxBallInt)value <= 255) {
            run = value - 192;
            decoded = decoded + run;
            value = (DxBallByte)getc(file);
            run_index = 0;
            while (run_index < run) {
                if (column > xmax) {
                    column = 0;
                    destination_x = x;
                    destination_y = destination_y + 1;
                    row = row + 1;
                }
                if (destination_x < width && destination_y < height &&
                    destination_x >= 0 && destination_y >= 0) {
                    pixel = description.pixels + destination_y * pitch + destination_x;
                    *pixel = value;
                }
                destination_x = destination_x + 1;
                column = column + 1;
                run_index = run_index + 1;
            }
        } else {
            decoded = decoded + 1;
            if (column > xmax) {
                column = 0;
                destination_x = x;
                destination_y = destination_y + 1;
                row = row + 1;
            }
            if (destination_x < width && destination_y < height &&
                destination_x >= 0 && destination_y >= 0) {
                pixel = description.pixels + destination_y * pitch + destination_x;
                *pixel = value;
            }
            destination_x = destination_x + 1;
            column = column + 1;
        }
    }
    surface->unlock(NULL);
    fclose(file);
    if (palette_mode == 1)
        dxball_load_live_palette(path);
    if (palette_mode == 2)
        dxball_load_saved_palette(path);
    return;
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#include "resources_bank.h"
