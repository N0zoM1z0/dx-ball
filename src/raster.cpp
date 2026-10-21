#include "raster.h"
#include "raster_imports.h"
extern "C" {
#include "allocator.h"
}
#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x0040B4C0 */
void dxball_fill_horizontal_span(DxBallByte *row, DxBallInt left,
                                DxBallInt right, DxBallByte color)
{
    DxBallInt length, alignment = 0;
    length = right - left + 1;
    row += left;
    if (length > 4 && (alignment = (DxBallInt)((size_t)row & 3)) != 0) {
        while (alignment++ < 4) {
            *row++ = color;
            --length;
        }
    }
    while (length-- > 0) *row++ = color;
    return;
}

/* FUNCTION: DXBALL 0x0040AB90 */
void dxball_fill_triangle(DxBallByte *pixels, DxBallInt pitch,
    DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2,
    DxBallInt x3, DxBallInt y3, DxBallByte color)
{
    DxBallFixedPoint long_increment, short_step, long_fixed_x, short_x;
    DxBallInt vertical_scale, scanline_index;
    if (y2 < y1) {
        y1 ^= y2; y2 ^= y1; y1 ^= y2;
        x1 ^= x2; x2 ^= x1; x1 ^= x2;
    }
    if (y3 < y2) {
        y2 ^= y3; y3 ^= y2; y2 ^= y3;
        x2 ^= x3; x3 ^= x2; x2 ^= x3;
    }
    if (y2 < y1) {
        y1 ^= y2; y2 ^= y1; y1 ^= y2;
        x1 ^= x2; x2 ^= x1; x1 ^= x2;
    }
    if (y3 - y1 == 0) return;
    /* Original instructions store this ratio but never read it. Its role
       is unresolved; retain the observed calculation, not a gradient claim. */
    vertical_scale = 0xf0000 / (y3 - y1);
    (void)vertical_scale;
    long_increment = DxBallFixedPoint(x3 - x1) / DxBallFixedPoint(y3 - y1);
    long_fixed_x = DxBallFixedPoint(x1);
    {
        scanline_index = y1;
        pixels += y1 * pitch;
        if (y2 > y1) {
            short_step = DxBallFixedPoint(x2 - x1) / DxBallFixedPoint(y2 - y1);
            short_x = DxBallFixedPoint(x1);
            if (long_increment < short_step) {
                while (y2 > scanline_index) {
                    if (scanline_index >= 0 && scanline_index < 480) {
                        DxBallInt right, left;
                        if ((DxBallInt)short_x <= 639) right = (DxBallInt)short_x;
                        else right = 639;
                        if ((DxBallInt)long_fixed_x < 0) left = 0;
                        else left = (DxBallInt)long_fixed_x;
                        dxball_fill_horizontal_span(pixels, left, right, color);
                    }
                    ++scanline_index; pixels += pitch; long_fixed_x += long_increment; short_x += short_step;
                }
            } else {
                while (y2 > scanline_index) {
                    if (scanline_index >= 0 && scanline_index < 480) {
                        DxBallInt right, left;
                        if ((DxBallInt)long_fixed_x <= 639) right = (DxBallInt)long_fixed_x;
                        else right = 639;
                        if ((DxBallInt)short_x < 0) left = 0;
                        else left = (DxBallInt)short_x;
                        dxball_fill_horizontal_span(pixels, left, right, color);
                    }
                    ++scanline_index; pixels += pitch; long_fixed_x += long_increment; short_x += short_step;
                }
            }
        }
        if (y3 - y2 == 0) return;
        short_step = DxBallFixedPoint(x3 - x2) / DxBallFixedPoint(y3 - y2);
        short_x = DxBallFixedPoint(x2);
        if (long_fixed_x < short_x) {
            while (y3 > scanline_index) {
                if (scanline_index >= 0 && scanline_index < 480) {
                    DxBallInt right, left;
                    if ((DxBallInt)short_x <= 639) right = (DxBallInt)short_x;
                    else right = 639;
                    if ((DxBallInt)long_fixed_x < 0) left = 0;
                    else left = (DxBallInt)long_fixed_x;
                    dxball_fill_horizontal_span(pixels, left, right, color);
                }
                ++scanline_index; pixels += pitch; long_fixed_x += long_increment; short_x += short_step;
            }
        } else {
            while (y3 > scanline_index) {
                if (scanline_index >= 0 && scanline_index < 480) {
                    DxBallInt right, left;
                    if ((DxBallInt)long_fixed_x <= 639) right = (DxBallInt)long_fixed_x;
                    else right = 639;
                    if ((DxBallInt)short_x < 0) left = 0;
                    else left = (DxBallInt)short_x;
                    dxball_fill_horizontal_span(pixels, left, right, color);
                }
                ++scanline_index; pixels += pitch; long_fixed_x += long_increment; short_x += short_step;
            }
        }
    }
}

/* FUNCTION: DXBALL 0x0040B240 */
DxBallFixedPoint::DxBallFixedPoint() { return; }
/* FUNCTION: DXBALL 0x0040B260 */
DxBallFixedPoint::~DxBallFixedPoint() { return; }
/* FUNCTION: DXBALL 0x0040B280 */
DxBallFixedPoint::DxBallFixedPoint(DxBallInt integer) {
    value = (DxBallInt)((DxBallUInt)integer << 16);
    return;
}
/* FUNCTION: DXBALL 0x0040B2B0 */
DxBallFixedPoint::operator DxBallInt() { return value >> 16; }
/* FUNCTION: DXBALL 0x0040B2D0 */
DxBallFixedPoint DxBallFixedPoint::operator/(DxBallFixedPoint denominator) {
    DxBallFixedPoint result;
    result.value = dxball_fixed_divide(value, denominator.value);
    return result;
}
/* FUNCTION: DXBALL 0x0040B390 */
DxBallInt dxball_fixed_divide(DxBallInt number, DxBallInt denominator) {
    return MulDiv(number, 65536, denominator);
}
/* FUNCTION: DXBALL 0x0040B3C0 */
DxBallInt DxBallFixedPoint::operator<(DxBallFixedPoint other) {
    return value < other.value;
}
/* FUNCTION: DXBALL 0x0040B450 */
DxBallFixedPoint &DxBallFixedPoint::operator+=(DxBallFixedPoint increment) {
    value += increment.value;
    return *this;
}
