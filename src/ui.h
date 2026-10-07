#ifndef DXBALL_UI_H
#define DXBALL_UI_H
#include "boards.h"

extern DxBallInt dxball_text_spacing;
void dxball_draw_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text);
void dxball_draw_centered_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text);
DxBallInt dxball_measure_text(DxBallInt count, const char *text);
void dxball_draw_line(DxBallSurface surface, DxBallInt x1, DxBallInt y1,
    DxBallInt x2, DxBallInt y2, DxBallByte color);
void dxball_fill_rect(DxBallSurface surface, DxBallInt left, DxBallInt top,
    DxBallInt right, DxBallInt bottom, DxBallUInt color);
void dxball_rotate_palette_right(DxBallInt first, DxBallInt last, DxBallInt wrap);
void dxball_rotate_rgb_colors(DxBallInt entry, DxBallInt count, DxBallInt *colors);
void dxball_set_palette_rgb(DxBallInt entry, DxBallByte red, DxBallByte green, DxBallByte blue);
#endif
