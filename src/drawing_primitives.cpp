extern "C" {
#include "ui.h"
#include "device.h"
}

// Adjacent original surface drawing primitives; fixed entry sequence.

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
            surface->get_desc(&desc);
            do {
                result = surface->lock(
                    NULL, &desc, 0, NULL);
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
            surface->unlock(NULL);
        }
    }
    return;
}

/* FUNCTION: DXBALL 0x00403230 */
void dxball_fill_rect(DxBallSurface handle, DxBallInt left, DxBallInt top,
    DxBallInt right, DxBallInt bottom, DxBallUInt color)
{
    DxBallRect rect;
    {
        DxBallColorFillFx fx;
        fx.size = 100;
        fx.fill_color = color;
        rect.top = top; rect.bottom = bottom; rect.left = left; rect.right = right;
        ((DxBallDDSurface *)handle)->blt(
            &rect, NULL, NULL, 0x400, (DxBallDDBltFx *)&fx);
    }
    return;
}
