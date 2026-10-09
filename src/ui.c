#include "ui.h"
#include "device.h"
#include "paddle.h"
#include <string.h>

DxBallInt dxball_text_spacing = 1;

DxBallInt dxball_measure_text(DxBallInt count, const char *text)
{
    DxBallInt i, sprite, width = 0;
    for (i = 0; i < count; ++i) {
        sprite = dxball_find_glyph(text[i]);
        width += sprite == 0 ? dxball_sprite_banks[dxball_font_bank].sprites[1]->width / 2
            : dxball_sprite_banks[dxball_font_bank].sprites[sprite]->width + dxball_text_spacing;
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
}

void dxball_draw_centered_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text)
{
    x -= dxball_measure_text(count, text) / 2;
    dxball_draw_text(x, baseline, count, text);
}

void dxball_draw_line(DxBallSurface handle, DxBallInt x1, DxBallInt y1,
    DxBallInt x2, DxBallInt y2, DxBallByte color)
{
    DxBallDDSurface *surface = (DxBallDDSurface *)handle;
    DxBallSurfaceDesc desc;
    DxBallByte *pixel;
    DxBallInt dx, dy, step_x, step_y, error = 0, i;
    memset(&desc, 0, sizeof(desc)); desc.size = 108; desc.flags = 14;
    surface->vtable->get_desc(surface, &desc);
    while (surface->vtable->lock(surface, NULL, &desc, 0, NULL) != 0) {}
    pixel = desc.pixels + desc.pitch * y1 + x1;
    dx = x2 - x1; dy = y2 - y1;
    step_x = dx < 0 ? -1 : 1;
    step_y = dy < 0 ? -desc.pitch : desc.pitch;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    if (dy < dx) {
        for (i = 0; i <= dx; ++i) {
            *pixel = color; error += dy;
            if (error > dx) { error -= dx; pixel += step_y; }
            pixel += step_x;
        }
    } else {
        for (i = 0; i <= dy; ++i) {
            *pixel = color; error += dx;
            if (error > 0) { error -= dy; pixel += step_x; }
            pixel += step_y;
        }
    }
    surface->vtable->unlock(surface, NULL);
}

void dxball_fill_rect(DxBallSurface handle, DxBallInt left, DxBallInt top,
    DxBallInt right, DxBallInt bottom, DxBallUInt color)
{
    DxBallDDSurface *surface = (DxBallDDSurface *)handle;
    DxBallRect rect;
    DxBallUInt fx[25];
    memset(fx, 0, sizeof(fx));
    fx[0] = 100;
    fx[20] = color;
    rect.left = left; rect.top = top; rect.right = right; rect.bottom = bottom;
    surface->vtable->blt(surface, &rect, NULL, NULL, 0x400, fx);
}

void dxball_set_palette_rgb(DxBallInt entry, DxBallByte red, DxBallByte green, DxBallByte blue)
{
    if (dxball_cursor_warp_disabled != 1) {
        dxball_live_palette[entry].red = red;
        dxball_live_palette[entry].green = green;
        dxball_live_palette[entry].blue = blue;
        dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, entry, 1, dxball_live_palette + entry);
    }
}

void dxball_rotate_palette_right(DxBallInt first, DxBallInt last, DxBallInt wrap)
{
    DxBallPaletteEntry color;
    DxBallInt i;
    if (dxball_cursor_warp_disabled == 1) return;
    color.red = wrap == 1 ? dxball_live_palette[last].red : 0;
    color.green = wrap == 1 ? dxball_live_palette[last].green : 0;
    color.blue = wrap == 1 ? dxball_live_palette[last].blue : 0;
    for (i = last; i > first; --i) dxball_live_palette[i] = dxball_live_palette[i - 1];
    dxball_live_palette[first].red = color.red;
    dxball_live_palette[first].green = color.green;
    dxball_live_palette[first].blue = color.blue;
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, first,
        last - first + 1, dxball_live_palette + first);
}

void dxball_rotate_rgb_colors(DxBallInt entry, DxBallInt count, DxBallInt *colors)
{
    DxBallInt red, green, blue, i;
    if (dxball_cursor_warp_disabled == 1) return;
    red = colors[0]; green = colors[1]; blue = colors[2];
    for (i = 0; i <= count - 4; ++i) colors[i] = colors[i + 3];
    colors[count - 3] = red; colors[count - 2] = green; colors[count - 1] = blue;
    dxball_set_palette_rgb(entry, (DxBallByte)colors[0], (DxBallByte)colors[1], (DxBallByte)colors[2]);
}

/* FUNCTION: DXBALL 0x00403290 */
const char *dxball_copy_text_word(DxBallInt skip, const char *source,
                                char *destination)
{
    DxBallInt spaces, offset;
    const char *text;
    offset = 0;
    spaces = 0;
    text = source;
    while (spaces < skip) {
        if (text[offset] == ' ') ++spaces;
        ++offset;
    }
    while (text[offset] != ' ') {
        destination[offset] = text[offset];
        ++offset;
    }
    destination[offset] = 0;
    return text + (offset + 1);
}
