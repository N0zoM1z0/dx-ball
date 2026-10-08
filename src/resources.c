#include "allocator.h"
#include "resources.h"

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
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_active_surface, x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x10);
    return;
}

/* FUNCTION: DXBALL 0x00404040 */
void dxball_draw_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_active_surface, x, y,
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
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_active_surface, &destination,
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
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_active_surface, &destination,
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
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_active_surface, &destination,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return;
}

/* FUNCTION: DXBALL 0x00404BE0 */
void dxball_release_sprite(DxBallInt sprite)
{
    if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] != NULL) {
        if (dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface != NULL) {
            dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface->vtable->release(
                dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface);
            dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface = NULL;
        }
        dxball_heap_release(dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]);
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = NULL;
    }
    return;
}

/* FUNCTION: DXBALL 0x004042B0 */
void dxball_capture_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                           DxBallInt width, DxBallInt height)
{
    DxBallSprite *record;
    DxBallSurfaceDesc description;
    DxBallColorKey key;
    DxBallRect capture;
    DxBallInt result;
    dxball_release_sprite(sprite);
    /* The target requests 45 bytes for the 44-byte x86 record. The last byte's
       purpose is unclassified; pointer-sized host storage grows naturally. */
    record = (DxBallSprite *)dxball_malloc_bytes(sizeof(DxBallSprite) + 1);
    if (record == NULL)
        exit(1);
    dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = record;
    record->width = width;
    record->height = height;
    record->code = 0;
    record->baseline = 0;
    record->source_rect.left = 0;
    record->source_rect.top = 0;
    record->source_rect.right = width;
    record->source_rect.bottom = height;
    description.size = sizeof(description);
    description.flags = 0xf;
    description.caps = 0x840;
    description.height = height;
    description.width = width;
    result = dxball_direct_draw->vtable->create_surface(
        dxball_direct_draw, &description, &record->surface, NULL);
    if (result == 0) {
        key.low = 0;
        key.high = 0;
        record->surface->vtable->set_color_key(record->surface, 8, &key);
        description.flags = 0x7f9ee;
        do {
            result = record->surface->vtable->get_desc(record->surface, &description);
        } while (result != 0);
        record->pitch = description.pitch;
        capture.left = x;
        capture.top = y;
        capture.right = x + width;
        capture.bottom = y + height;
        record->surface->vtable->blt(record->surface, &record->source_rect,
                                    (DxBallDDSurface *)dxball_active_surface,
                                    &capture, 0x1000000, NULL);
    }
    return;
}

/* FUNCTION: DXBALL 0x00404610 */
void dxball_load_sprite_bank(DxBallInt bank, DxBallInt allocation_mode, const char *path)
{
    DxBallInt saved_bank, sprite, count, width, height, baseline;
    char code;
    DxBallUInt pixel_count;
    DxBallByte *pixels;
    DxBallSprite *record;
    DxBallSurfaceDesc description;
    DxBallColorKey key;
    DxBallInt result, row, column, cursor;
    saved_bank = dxball_sprite_bank;
    dxball_select_sprite_bank(bank);
    for (sprite = 1; sprite < 254; sprite = sprite + 1)
        dxball_release_sprite(sprite);
    dxball_board_file = fopen(path, "rb");
    if (dxball_board_file == NULL)
        exit(1);
    fread(&count, 4, 1, dxball_board_file);
    for (sprite = 1; sprite < count + 1; sprite = sprite + 1) {
        fread(&width, 4, 1, dxball_board_file);
        fread(&height, 4, 1, dxball_board_file);
        fread(&code, 1, 1, dxball_board_file);
        fread(&baseline, 4, 1, dxball_board_file);
        pixel_count = width * height;
        pixels = (DxBallByte *)dxball_malloc_bytes(pixel_count + 3);
        if (pixels == NULL)
            exit(1);
        record = (DxBallSprite *)dxball_malloc_bytes(sizeof(DxBallSprite) + 1);
        if (record == NULL)
            exit(1);
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite] = record;
        fread(pixels, 1, pixel_count, dxball_board_file);
        dxball_sprite_banks[dxball_sprite_bank].count = count;
        dxball_sprite_banks[dxball_sprite_bank].allocation_mode = allocation_mode;
        strcpy(dxball_sprite_banks[dxball_sprite_bank].filename, path);
        record->width = width;
        record->height = height;
        record->code = code;
        record->baseline = baseline;
        record->source_rect.top = 0;
        record->source_rect.left = 0;
        record->source_rect.bottom = height;
        record->source_rect.right = width;
        description.size = sizeof(description);
        description.flags = 0xf;
        description.caps = allocation_mode == 1 ? 0x40 : 0x840;
        description.height = height;
        description.width = width;
        result = dxball_direct_draw->vtable->create_surface(
            dxball_direct_draw, &description, &record->surface, NULL);
        /* Creation failure preserves the target's partial owner and leaks;
           it does not restore the bank, close the stream or free these buffers. */
        if (result != 0)
            return;
        key.low = 0;
        key.high = 0;
        record->surface->vtable->set_color_key(record->surface, 8, &key);
        description.flags = 0x7f9ee;
        do {
            result = record->surface->vtable->get_desc(record->surface, &description);
        } while (result != 0);
        record->pitch = description.pitch;
        do {
            result = record->surface->vtable->lock(record->surface, NULL, &description, 0, NULL);
        } while (result != 0);
        cursor = 0;
        row = height;
        while (--row >= 0) {
            for (column = 0; column < width; column = column + 1) {
                description.pixels[row * record->pitch + column] = pixels[cursor];
                cursor = cursor + 1;
            }
        }
        record->surface->vtable->unlock(record->surface, NULL);
        dxball_heap_release(pixels);
    }
    fclose(dxball_board_file);
    dxball_select_sprite_bank(saved_bank);
    return;
}

/* FUNCTION: DXBALL 0x00404E40
   The count-th slot is intentionally excluded, and an empty bank returns 1. */
DxBallInt dxball_find_glyph(char code)
{
    DxBallInt sprite = 0;
    do {
        sprite = sprite + 1;
        if (dxball_sprite_banks[dxball_font_bank].count <= sprite)
            break;
    } while (dxball_sprite_banks[dxball_font_bank].sprites[sprite]->code != code);
    if (dxball_sprite_banks[dxball_font_bank].count == sprite)
        sprite = 0;
    return sprite;
}

/* FUNCTION: DXBALL 0x00404CF0 */
DxBallInt dxball_draw_glyph(char code, DxBallInt x, DxBallInt baseline)
{
    DxBallInt sprite;
    DxBallRect destination;
    sprite = dxball_find_glyph(code);
    if (sprite == 0)
        return 0;
    destination.left = x;
    destination.top = baseline - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->height
                     - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
    destination.right = x + dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width;
    destination.bottom = baseline - dxball_sprite_banks[dxball_font_bank].sprites[sprite]->baseline;
    ((DxBallDDSurface *)dxball_active_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_active_surface, &destination,
        dxball_sprite_banks[dxball_font_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_font_bank].sprites[sprite]->source_rect, 0x1008000, NULL);
    return dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width;
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
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, 0, 256,
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

/* FUNCTION: DXBALL 0x00409BB0
   Preserve the observed inclusive xmax*ymax limit, including truncated last
   rows and packet overshoot. This is the game decoder, not a general PCX reader. */
void dxball_load_pcx(DxBallDDSurface *surface, const char *path,
                     DxBallInt palette_mode, DxBallInt x, DxBallInt y)
{
    DxBallSurfaceDesc description;
    DxBallByte header[128], value;
    FILE *file;
    DxBallInt width, height, pitch, xmax, ymax;
    DxBallInt column, destination_x, destination_y, decoded, run, i, result;
    description.size = sizeof(description);
    description.flags = 0xe;
    surface->vtable->get_desc(surface, &description);
    width = description.width;
    height = description.height;
    pitch = description.pitch;
    destination_x = x;
    destination_y = y;
    column = 0;
    file = fopen(path, "rb");
    for (i = 0; i < 128; i = i + 1)
        header[i] = (DxBallByte)getc(file);
    xmax = (signed short)(header[8] | (header[9] << 8));
    ymax = (signed short)(header[10] | (header[11] << 8));
    do {
        result = surface->vtable->lock(surface, NULL, &description, 0, NULL);
    } while (result != 0);
    decoded = 0;
    while (decoded <= xmax * ymax) {
        value = (DxBallByte)getc(file);
        if (value < 192) {
            run = 1;
        } else {
            run = value - 192;
            value = (DxBallByte)getc(file);
        }
        decoded = decoded + run;
        for (i = 0; i < run; i = i + 1) {
            if (column > xmax) {
                column = 0;
                destination_x = x;
                destination_y = destination_y + 1;
            }
            if (destination_x < width && destination_y < height &&
                destination_x >= 0 && destination_y >= 0) {
                description.pixels[destination_x + pitch * destination_y] = value;
            }
            destination_x = destination_x + 1;
            column = column + 1;
        }
    }
    surface->vtable->unlock(surface, NULL);
    fclose(file);
    if (palette_mode == 1)
        dxball_load_live_palette(path);
    if (palette_mode == 2)
        dxball_load_saved_palette(path);
    return;
}
