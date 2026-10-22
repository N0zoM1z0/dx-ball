extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

DxBallSpriteBank dxball_sprite_banks[3];
DxBallInt dxball_sprite_bank, dxball_font_bank;
DxBallDDraw *dxball_direct_draw;
DxBallDDPalette *dxball_direct_palette;
DxBallPaletteEntry dxball_live_palette[256], dxball_saved_palette[256];

/* Only the two observed signed maxima are interpreted from the disk header. */
typedef struct DxBallPcxFilePrefix {
    char manufacturer, version, encoding, bits_per_pixel;
    unsigned short xmin, ymin, xmax, ymax;
    unsigned short hres, vres;
    unsigned char palette[48];
    char reserved, color_planes;
    unsigned short bytes_per_line, palette_type;
    char filler[58];
    unsigned data;
} DxBallPcxFilePrefix;

typedef char DxBallPcxHeaderPrefixMustBe128Bytes[
    (offsetof(DxBallPcxFilePrefix, data) == 128) ? 1 : -1];

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
    DxBallInt max_y;
    DxBallByte *headerBytes;
    DxBallInt x_max;
    DxBallInt surface_height;
    DxBallInt header_index;
    DxBallInt run;
    DxBallByte *pixel_address;
    DxBallInt destinationY;
    DxBallInt row;
    DxBallInt run_position;
    FILE *pcx_input;
    DxBallInt rowPitch;
    DxBallInt draw_x;
    DxBallInt image_column;
    DxBallPcxFilePrefix header;
    DxBallByte value;
    DxBallSurfaceDesc pcx_description;
    DxBallInt width;
    DxBallInt lockStatus;
    DxBallInt decoded_pixels;
    pcx_description.size = sizeof(pcx_description);
    pcx_description.flags = 0xe;
    surface->get_desc(&pcx_description);
    width = pcx_description.width;
    surface_height = pcx_description.height;
    rowPitch = pcx_description.pitch;
    draw_x = x;
    destinationY = y;
    image_column = 0;
    row = 0;
    pcx_input = fopen(path, "rb");
    headerBytes = (DxBallByte *)&header;
    for (header_index = 0; header_index < (DxBallInt)offsetof(DxBallPcxFilePrefix, data); header_index = header_index + 1)
        headerBytes[header_index] = (DxBallByte)getc(pcx_input);
    x_max = (signed short)header.xmax;
    max_y = (signed short)header.ymax;
    do {
        lockStatus = surface->lock(NULL, &pcx_description, 0, NULL);
    } while (lockStatus != 0);
    pixel_address = pcx_description.pixels;
    decoded_pixels = 0;
    while (x_max * max_y >= decoded_pixels) {
        value = (DxBallByte)getc(pcx_input);
        if ((DxBallInt)value >= 192 && (DxBallInt)value <= 255) {
            run = value - 192;
            decoded_pixels = decoded_pixels + run;
            value = (DxBallByte)getc(pcx_input);
            run_position = 0;
            while (run_position < run) {
                if (image_column > x_max) {
                    image_column = 0;
                    draw_x = x;
                    destinationY = destinationY + 1;
                    row = row + 1;
                }
                if (draw_x < width && destinationY < surface_height &&
                    draw_x >= 0 && destinationY >= 0) {
                    pixel_address = pcx_description.pixels + destinationY * rowPitch + draw_x;
                    *pixel_address = value;
                }
                draw_x = draw_x + 1;
                image_column = image_column + 1;
                run_position = run_position + 1;
            }
        } else {
            decoded_pixels = decoded_pixels + 1;
            if (image_column > x_max) {
                image_column = 0;
                draw_x = x;
                destinationY = destinationY + 1;
                row = row + 1;
            }
            if (draw_x < width && destinationY < surface_height &&
                draw_x >= 0 && destinationY >= 0) {
                pixel_address = pcx_description.pixels + destinationY * rowPitch + draw_x;
                *pixel_address = value;
            }
            draw_x = draw_x + 1;
            image_column = image_column + 1;
        }
    }
    surface->unlock(NULL);
    fclose(pcx_input);
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
