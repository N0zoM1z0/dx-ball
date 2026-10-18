#include "ui.h"
#include "device.h"
#include "paddle.h"

DxBallInt dxball_text_spacing = 1;

/* FUNCTION: DXBALL 0x00404FD0 */
DxBallInt dxball_measure_text(DxBallInt count, const char *text)
{
    DxBallInt i, sprite, width = 0;
    for (i = 0; count > i; ++i) {
        sprite = 0;
        do {
            sprite = sprite + 1;
        } while (dxball_sprite_banks[dxball_font_bank].count > sprite &&
                 dxball_sprite_banks[dxball_font_bank].sprites[sprite]->code != (signed char)text[i]);
        if (dxball_sprite_banks[dxball_font_bank].count == sprite)
            sprite = 0;
        if (sprite == 0)
            width += dxball_sprite_banks[dxball_font_bank].sprites[1]->width / 2;
        else
            width += dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width
                   + dxball_text_spacing;
    }
    return width;
}



void dxball_draw_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text)
{
    DxBallInt i, advance = 0;
    for (i = 0; i < count; ++i) {
        x += advance;
        advance = dxball_draw_glyph(text[i], x, baseline);
        if (advance == 0) advance = dxball_sprite_banks[dxball_font_bank].sprites[1]->width / 2;
        else advance += dxball_text_spacing;
    }
    return;
}

void dxball_draw_centered_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text)
{
    DxBallInt width;
    width = dxball_measure_text(count, text);
    dxball_draw_text(x - width / 2, baseline, count, text);
    return;
}



void dxball_set_palette_rgb(DxBallInt entry, DxBallByte red, DxBallByte green, DxBallByte blue)
{
    if (dxball_cursor_warp_disabled == 1) return;
    dxball_live_palette[entry].red = red;
    dxball_live_palette[entry].green = green;
    dxball_live_palette[entry].blue = blue;
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, entry, 1, dxball_live_palette + entry);
    return;
}

void dxball_rotate_palette_right(DxBallInt first, DxBallInt last, DxBallInt mode)
{
    DxBallByte r, g, b;
    if (dxball_cursor_warp_disabled == 1) return;
    if (mode == 1) {
        r = dxball_live_palette[last].red;
        g = dxball_live_palette[last].green;
        b = dxball_live_palette[last].blue;
    } else {
        r = 0; g = 0; b = 0;
    }
    {
        DxBallInt i;
        for (i = last; i > first; --i) dxball_live_palette[i] = dxball_live_palette[i - 1];
    }
    dxball_live_palette[first].red = r;
    dxball_live_palette[first].green = g;
    dxball_live_palette[first].blue = b;
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, first,
        last - first + 1, dxball_live_palette + first);
    return;
}

void dxball_rotate_rgb_colors(DxBallInt entry, DxBallInt count, DxBallInt *colors)
{
    struct { DxBallInt green, red, blue; } color;
    if (dxball_cursor_warp_disabled == 1) return;
    color.red = colors[0]; color.green = colors[1]; color.blue = colors[2];
    {
        DxBallInt i;
        for (i = 0; i <= count - 4; ++i) colors[i] = colors[i + 3];
    }
    colors[count - 3] = color.red; colors[count - 2] = color.green; colors[count - 1] = color.blue;
    dxball_set_palette_rgb(entry, (DxBallByte)colors[0], (DxBallByte)colors[1], (DxBallByte)colors[2]);
    return;
}

/* FUNCTION: DXBALL 0x00403290 */
const char *dxball_copy_text_word(DxBallInt skip, const char *source,
                                char *destination)
{
    struct {
        const char *text;
        DxBallInt offset, spaces;
    } cursor;
    cursor.offset = 0;
    cursor.spaces = 0;
    cursor.text = source;
    while (cursor.spaces < skip) {
        if (cursor.text[cursor.offset] == ' ') ++cursor.spaces;
        ++cursor.offset;
    }
    while (cursor.text[cursor.offset] != ' ') {
        destination[cursor.offset] = cursor.text[cursor.offset];
        ++cursor.offset;
    }
    destination[cursor.offset] = 0;
    return cursor.text + (cursor.offset + 1);
}
