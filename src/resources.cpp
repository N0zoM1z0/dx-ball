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

/* FUNCTION: DXBALL 0x00403E70 */
void dxball_select_sprite_bank(DxBallInt bank)
{
    dxball_sprite_bank = bank;
    return;
}

/* FUNCTION: DXBALL 0x00403E90 */
void dxball_select_font_bank(DxBallInt bank)
{
    dxball_font_bank = bank;
    return;
}



/* FUNCTION: DXBALL 0x00404180 */
void dxball_draw_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    ((DxBallDDSurface *)dxball_active_surface)->blt_fast(x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x10);
    return;
}

/* FUNCTION: DXBALL 0x00404040 */
void dxball_draw_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    ((DxBallDDSurface *)dxball_active_surface)->blt_fast(x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x11);
    return;
}

/* FUNCTION: DXBALL 0x00403F70 */
void dxball_blt_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect destination;
    destination.left = x;
    destination.top = y;
    destination.right = x + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width;
    destination.bottom = y + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height;
    ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return;
}

/* FUNCTION: DXBALL 0x004040B0 */
void dxball_blt_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect destination;
    destination.left = x;
    destination.top = y;
    destination.right = x + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width;
    destination.bottom = y + dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height;
    ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1000000, NULL);
    return;
}

/* FUNCTION: DXBALL 0x004041F0 */
void dxball_stretch_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                                DxBallInt width, DxBallInt height)
{
    DxBallRect destination;
    destination.left = x;
    destination.top = y;
    destination.right = x + width;
    destination.bottom = y + height;
    ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return;
}

/* FUNCTION: DXBALL 0x00404280 */
void dxball_draw_rotated_sprite(DxBallInt slot, DxBallUInt center_x,
                               DxBallUInt center_y, DxBallInt angle)
{
    dxball_render_rotated_sprite(center_x, center_y, slot, angle);
    return;
}

/* FUNCTION: DXBALL 0x00404BE0 */
void dxball_release_sprite(DxBallInt sprite)
{
    if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] == NULL) return;
    if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface != NULL) {
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->release();
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface = NULL;
    }
    dxball_heap_release(dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]);
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = NULL;
    return;
}

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

/* FUNCTION: DXBALL 0x00404610 */
void dxball_load_sprite_bank(DxBallInt bank, DxBallInt allocation_mode, const char *file)
{
    DxBallInt saved_bank, i, count;
    DxBallInt row, column, cursor, pitch;
    saved_bank = dxball_sprite_bank;
    dxball_select_sprite_bank(bank);
    for (i = 1; i < 254; i = i + 1)
        dxball_release_sprite(i);
    dxball_board_file = fopen(file, "rb");
    if (dxball_board_file == NULL)
        exit(1);
    fread(&count, 4, 1, dxball_board_file);
    for (i = 1; i < (DxBallInt)((DxBallUInt)count + 1); i = i + 1) {
        DxBallInt width, height, yoffset;
        signed char letter;
        DxBallUInt nbytes;
        DxBallByte *bitmap;
        fread(&width, 4, 1, dxball_board_file);
        fread(&height, 4, 1, dxball_board_file);
        fread(&letter, 1, 1, dxball_board_file);
        fread(&yoffset, 4, 1, dxball_board_file);
        nbytes = (DxBallUInt)width * height;
        bitmap = (DxBallByte *)dxball_runtime_malloc(nbytes + 3);
        if (bitmap == NULL)
            exit(1);
        {
            DxBallSprite *new_shape;
            new_shape = (DxBallSprite *)dxball_runtime_malloc(sizeof(DxBallSprite) + 1);
            if (new_shape == NULL)
                exit(1);
            dxball_sprite_banks[dxball_sprite_bank].sprites[i] = new_shape;
        }
        fread(bitmap, 1, nbytes, dxball_board_file);
        dxball_sprite_banks[dxball_sprite_bank].count = count;
        dxball_sprite_banks[dxball_sprite_bank].allocation_mode = allocation_mode;
        strcpy(dxball_sprite_banks[dxball_sprite_bank].filename, file);
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->width = width;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->height = height;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->code = letter;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->baseline = yoffset;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->source_rect.top = 0;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->source_rect.left = 0;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->source_rect.bottom = height;
        dxball_sprite_banks[dxball_sprite_bank].sprites[i]->source_rect.right = width;
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
            api.description.height = height;
            api.description.width = width;
            api.result = dxball_direct_draw->vtable->create_surface(
                dxball_direct_draw, &api.description,
                &dxball_sprite_banks[dxball_sprite_bank].sprites[i]->surface, NULL);
            /* Creation failure preserves the target's partial owner and leaks;
               it does not restore the bank, close the stream or free these buffers. */
            if (api.result != 0)
                return;
            key.low = 0;
            key.high = 0;
            dxball_sprite_banks[dxball_sprite_bank].sprites[i]->surface->set_color_key(8, &key);
            api.description.flags = 0x7f9ee;
            do {
                api.result = dxball_sprite_banks[dxball_sprite_bank].sprites[i]->surface->get_desc(&api.description);
            } while (api.result != 0);
            /* GetSurfaceDesc supplies the row stride before Lock; later API writes
               to the descriptor or current record do not replace that snapshot. */
            pitch = api.description.pitch;
            dxball_sprite_banks[dxball_sprite_bank].sprites[i]->pitch = pitch;
            do {
                api.result = dxball_sprite_banks[dxball_sprite_bank].sprites[i]->surface->lock(NULL, &api.description, 0, NULL);
            } while (api.result != 0);
            cursor = 0;
            for (row = height - 1; row >= 0; --row) {
                for (column = 0; column <= width - 1; ++column) {
                    api.pixel = row * pitch + column + api.description.pixels;
                    *api.pixel = bitmap[cursor];
                    cursor = cursor + 1;
                }
            }
            dxball_sprite_banks[dxball_sprite_bank].sprites[i]->surface->unlock(NULL);
        }
        dxball_heap_release(bitmap);
    }
    fclose(dxball_board_file);
    dxball_select_sprite_bank(saved_bank);
    return;
}

/* FUNCTION: DXBALL 0x00404E40
   The count-th slot is intentionally excluded, and an empty bank returns 1. */
DxBallInt dxball_find_glyph(signed char code)
{
    DxBallInt sprite = 0;
    do {
        sprite = sprite + 1;
    } while (dxball_sprite_banks[dxball_font_bank].count > sprite &&
             dxball_sprite_banks[dxball_font_bank].sprites[sprite]->code != code);
    if (dxball_sprite_banks[dxball_font_bank].count == sprite)
        sprite = 0;
    return sprite;
}

/* FUNCTION: DXBALL 0x00404CF0 */
DxBallInt dxball_draw_glyph(signed char code, DxBallInt x, DxBallInt baseline)
{
    DxBallInt sprite;
    DxBallRect destination;
    sprite = dxball_find_glyph(code);
    if (sprite != 0) {
        destination.left = x;
        destination.top = baseline - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->height
                         - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
        destination.right = dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width + x;
        destination.bottom = baseline - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
        ((DxBallDDSurface *)dxball_active_surface)->blt(&destination,
            dxball_sprite_banks[dxball_font_bank].sprites[sprite]->surface,
            &dxball_sprite_banks[dxball_font_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
        return dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x00409790 */
void dxball_load_live_palette(const char *path)
{
    FILE *file;
    DxBallInt color;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_live_palette[color].red = (DxBallByte)getc(file);
        dxball_live_palette[color].green = (DxBallByte)getc(file);
        dxball_live_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    dxball_direct_palette->set_entries(0, 0, 256,
                                              dxball_live_palette);
    return;
}

/* FUNCTION: DXBALL 0x004098F0 */
void dxball_load_saved_palette(const char *path)
{
    FILE *file;
    DxBallInt color;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_saved_palette[color].red = (DxBallByte)getc(file);
        dxball_saved_palette[color].green = (DxBallByte)getc(file);
        dxball_saved_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    return;
}

/* FUNCTION: DXBALL 0x00409A30 */
void dxball_load_surface_palette(DxBallDDSurface *surface, const char *path)
{
    FILE *file;
    DxBallInt color, result;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_live_palette[color].red = (DxBallByte)getc(file);
        dxball_live_palette[color].green = (DxBallByte)getc(file);
        dxball_live_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
        dxball_live_palette, &dxball_direct_palette, NULL);
    if (result != 0) {
        return;
    }
    result = surface->set_palette(dxball_direct_palette);
    return;
}

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

/* FUNCTION: DXBALL 0x00403EB0 */
void dxball_release_sprite_bank(DxBallInt bank)
{
    DxBallInt sprite, saved_bank;
    saved_bank = dxball_sprite_bank;
    dxball_select_sprite_bank(bank);
    sprite = 0;
    while (sprite <= 254) {
        dxball_release_sprite(sprite);
        ++sprite;
    }
    dxball_sprite_banks[bank].count = 0;
    dxball_sprite_banks[bank].allocation_mode = 0;
    strcpy(dxball_sprite_banks[bank].filename, " ");
    dxball_select_sprite_bank(saved_bank);
    return;
}
