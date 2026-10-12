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
                 dxball_sprite_banks[dxball_font_bank].sprites[sprite]->code != text[i]);
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

/* FUNCTION: DXBALL 0x00403070 */
void dxball_draw_line(DxBallDDSurface *surface, DxBallInt x1, DxBallInt y1,
    DxBallInt x2, DxBallInt y2, DxBallByte color)
{
    DxBallInt i;
    {
        DxBallInt dx, dy, error = 0;
        {
            DxBallSurfaceDesc desc;
            DxBallInt result;
            desc.size = sizeof(desc);
            desc.flags = 14;
            surface->vtable->get_desc(surface, &desc);
            do {
                result = surface->vtable->lock(
                    surface, NULL, &desc, 0, NULL);
            } while (result != 0);
            {
                DxBallByte *pixel;
                /* X advances one byte; Y advances one row of the locked plane. */
                DxBallInt step[2];
                pixel = desc.pixels;
                pixel += desc.pitch * y1 + x1;
                dx = x2 - x1; dy = y2 - y1;
                if (dx >= 0) {
                    step[0] = 1;
                } else {
                    step[0] = -1;
                    dx = -dx;
                }
                if (dy >= 0) {
                    step[1] = desc.pitch;
                } else {
                    step[1] = -desc.pitch;
                    dy = -dy;
                }
                if (dx > dy) {
                    for (i = 0; i <= dx; ++i) {
                        *pixel = color; error += dy;
                        if (error > dx) { error -= dx; pixel += step[1]; }
                        pixel += step[0];
                    }
                } else {
                    for (i = 0; i <= dy; ++i) {
                        *pixel = color; error += dx;
                        if (error > 0) { error -= dy; pixel += step[0]; }
                        pixel += step[1];
                    }
                }
            }
            surface->vtable->unlock(surface, NULL);
        }
    }
    return;
}

void dxball_fill_rect(DxBallSurface handle, DxBallInt left, DxBallInt top,
    DxBallInt right, DxBallInt bottom, DxBallUInt color)
{
    DxBallRect rect;
    {
        DxBallColorFillFx fx;
        fx.size = 100;
        fx.fill_color = color;
        rect.top = top; rect.bottom = bottom; rect.left = left; rect.right = right;
        ((DxBallDDSurface *)handle)->vtable->blt((DxBallDDSurface *)handle,
            &rect, NULL, NULL, 0x400, &fx);
    }
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

void dxball_rotate_palette_right(DxBallInt first, DxBallInt last, DxBallInt wrap)
{
    DxBallByte red, green, blue;
    if (dxball_cursor_warp_disabled == 1) return;
    if (wrap == 1) {
        red = dxball_live_palette[last].red;
        green = dxball_live_palette[last].green;
        blue = dxball_live_palette[last].blue;
    } else {
        red = 0; green = 0; blue = 0;
    }
    {
        DxBallInt i;
        for (i = last; i > first; --i) dxball_live_palette[i] = dxball_live_palette[i - 1];
    }
    dxball_live_palette[first].red = red;
    dxball_live_palette[first].green = green;
    dxball_live_palette[first].blue = blue;
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
