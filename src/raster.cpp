#include "raster.h"
extern "C" {
#include "allocator.h"
}
#include <stdlib.h>
#include <string.h>

typedef struct RasterEdge {
    DxBallInt top, bottom, x;
    DxBallByte unknown[4];
    DxBallInt dx, dy, error;
} RasterEdge;
/* Both spellings denote the same signed 64-bit arithmetic type. The legacy
   compiler predates C99's long-long spelling; no layout or body is selected. */
#if defined(_MSC_VER)
typedef __int64 RasterWideInt;
#else
typedef long long RasterWideInt;
#endif
typedef char RasterWideMustBe64Bits[(sizeof(RasterWideInt) == 8) ? 1 : -1];

static DxBallInt DXBALL_RASTER_CALL portable_muldiv(DxBallInt number, DxBallInt numerator,
                                DxBallInt denominator)
{
    RasterWideInt product, divisor, magnitude, result;
    if (denominator == 0) return -1;
    product = (RasterWideInt)number * numerator;
    divisor = denominator;
    if (divisor < 0) { product = -product; divisor = -divisor; }
    magnitude = product < 0 ? -product : product;
    result = (magnitude + divisor / 2) / divisor;
    if (product < 0) result = -result;
    if (result < (-2147483647 - 1) || result > 2147483647) return -1;
    return (DxBallInt)result;
}

DxBallRasterOps dxball_raster_ops = { malloc, free, portable_muldiv };

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

/* FUNCTION: DXBALL 0x0040B550 */
void DXBALL_RASTER_CALL dxball_fill_polygon(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color)
{
    RasterEdge *storage, **pending, **active, *edge, *saved;
    DxBallRasterPoint first, second;
    DxBallInt used, live, next, gap, i, j, y, left, right;
    storage = (RasterEdge *)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*storage)));
    pending = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*pending)));
    active = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*active)));
    if (storage == NULL || pending == NULL || active == NULL) {
        if (storage != NULL) dxball_heap_release(storage);
        if (pending != NULL) dxball_heap_release(pending);
        if (active != NULL) dxball_heap_release(active);
        return;
    }
    used = 0;
    for (i = 0; i < count; ++i) {
        first = points[i];
        second = points[(i + 1) % count];
        if (first.y == second.y)
            continue;
        if (first.y > second.y) {
            first = second;
            second = points[i];
        }
        storage[used].top = first.y;
        storage[used].bottom = second.y;
        storage[used].x = first.x;
        storage[used].dx = second.x - first.x;
        storage[used].dy = second.y - first.y;
        storage[used].error = 0;
        pending[used] = &storage[used];
        ++used;
    }
    for (gap = 1; gap < used; gap = gap * 3 + 1) { }
    while ((gap /= 3) > 0) {
        for (i = gap; i < used; ++i) {
            for (j = i - gap; j >= 0 && pending[j + gap]->top < pending[j]->top; j -= gap) {
                saved = pending[j];
                pending[j] = pending[j + gap];
                pending[j + gap] = saved;
            }
        }
    }
    next = live = 0;
    /* A nonhorizontal closed contour and representable arithmetic are the
       original routine's required domain; its zero-edge read is unresolved. */
    y = pending[0]->top;
    while (next < used || live != 0) {
        while (next < used && pending[next]->top == y)
            active[live++] = pending[next++];
        i = 0;
        while (i < live) {
            if (active[i]->bottom == y) {
                --live;
                memmove(&active[i], &active[i + 1], (live - i) * sizeof(*active));
            } else {
                ++i;
            }
        }
        for (gap = 1; gap < live; gap = gap * 3 + 1) { }
        while ((gap /= 3) > 0) {
            for (i = gap; i < live; ++i) {
                for (j = i - gap; j >= 0 && active[j + gap]->x < active[j]->x; j -= gap) {
                    saved = active[j];
                    active[j] = active[j + gap];
                    active[j + gap] = saved;
                }
            }
        }
        for (i = 0; i < live; i += 2) {
            left = active[i]->x;
            right = active[i + 1]->x;
            if (active[i]->error > 0) ++left;
            if (active[i + 1]->error <= 0) --right;
            if (left <= right)
                dxball_fill_horizontal_span(pixels + y * pitch, left, right, color);
        }
        for (i = 0; i < live; ++i) {
            edge = active[i];
            edge->error += edge->dx;
            if (edge->dx < 0) {
                while (edge->dy <= -edge->error) {
                    edge->error += edge->dy;
                    --edge->x;
                }
            } else {
                while (edge->dy <= edge->error) {
                    edge->error -= edge->dy;
                    ++edge->x;
                }
            }
        }
        ++y;
    }
    dxball_heap_release(storage);
    dxball_heap_release(pending);
    dxball_heap_release(active);
    return;
}

/* FUNCTION: DXBALL 0x0040BB60 */
void DXBALL_RASTER_CALL dxball_fill_polygon_clipped(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color)
{
    RasterEdge *storage, **pending, **active, *edge, *saved;
    DxBallRasterPoint first, second;
    DxBallInt used, live, next, gap, i, j, y, left, right;
    storage = (RasterEdge *)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*storage)));
    pending = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*pending)));
    active = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*active)));
    if (storage == NULL || pending == NULL || active == NULL) {
        if (storage != NULL) dxball_heap_release(storage);
        if (pending != NULL) dxball_heap_release(pending);
        if (active != NULL) dxball_heap_release(active);
        return;
    }
    used = 0;
    for (i = 0; i < count; ++i) {
        first = points[i];
        second = points[(i + 1) % count];
        if (first.y == second.y)
            continue;
        if (first.y > second.y) {
            first = second;
            second = points[i];
        }
        storage[used].top = first.y;
        storage[used].bottom = second.y;
        storage[used].x = first.x;
        storage[used].dx = second.x - first.x;
        storage[used].dy = second.y - first.y;
        storage[used].error = 0;
        pending[used] = &storage[used];
        ++used;
    }
    for (gap = 1; gap < used; gap = gap * 3 + 1) { }
    while ((gap /= 3) > 0) {
        for (i = gap; i < used; ++i) {
            for (j = i - gap; j >= 0 && pending[j + gap]->top < pending[j]->top; j -= gap) {
                saved = pending[j];
                pending[j] = pending[j + gap];
                pending[j + gap] = saved;
            }
        }
    }
    next = live = 0;
    /* A nonhorizontal closed contour and representable arithmetic are the
       original routine's required domain; its zero-edge read is unresolved. */
    y = pending[0]->top;
    while (next < used || live != 0) {
        while (next < used && pending[next]->top == y)
            active[live++] = pending[next++];
        i = 0;
        while (i < live) {
            if (active[i]->bottom == y) {
                --live;
                memmove(&active[i], &active[i + 1], (live - i) * sizeof(*active));
            } else {
                ++i;
            }
        }
        for (gap = 1; gap < live; gap = gap * 3 + 1) { }
        while ((gap /= 3) > 0) {
            for (i = gap; i < live; ++i) {
                for (j = i - gap; j >= 0 && active[j + gap]->x < active[j]->x; j -= gap) {
                    saved = active[j];
                    active[j] = active[j + gap];
                    active[j + gap] = saved;
                }
            }
        }
        for (i = 0; i < live; i += 2) {
            left = active[i]->x;
            right = active[i + 1]->x;
            if (active[i]->error > 0) ++left;
            if (active[i + 1]->error <= 0) --right;
            if (left <= right && y >= 0 && y < 480) {
                if (right > 638) right = 639;
                if (left < 1) left = 0;
                dxball_fill_horizontal_span(pixels + y * pitch, left, right, color);
            }
        }
        for (i = 0; i < live; ++i) {
            edge = active[i];
            edge->error += edge->dx;
            if (edge->dx < 0) {
                while (edge->dy <= -edge->error) {
                    edge->error += edge->dy;
                    --edge->x;
                }
            } else {
                while (edge->dy <= edge->error) {
                    edge->error -= edge->dy;
                    ++edge->x;
                }
            }
        }
        ++y;
    }
    dxball_heap_release(storage);
    dxball_heap_release(pending);
    dxball_heap_release(active);
    return;
}

/* FUNCTION: DXBALL 0x0040AB90 */
void dxball_fill_triangle(DxBallByte *pixels, DxBallInt pitch,
    DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2,
    DxBallInt x3, DxBallInt y3, DxBallByte color)
{
    DxBallFixedPoint long_step, short_step, long_x, short_x;
    DxBallInt vertical_scale, y;
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
    long_step = DxBallFixedPoint(x3 - x1) / DxBallFixedPoint(y3 - y1);
    long_x = DxBallFixedPoint(x1);
    y = y1;
    pixels += y1 * pitch;
    if (y2 > y1) {
        short_step = DxBallFixedPoint(x2 - x1) / DxBallFixedPoint(y2 - y1);
        short_x = DxBallFixedPoint(x1);
        if (long_step < short_step) {
            while (y2 > y) {
                if (y >= 0 && y < 480) {
                    DxBallInt right, left;
                    if ((DxBallInt)short_x <= 639) right = (DxBallInt)short_x;
                    else right = 639;
                    if ((DxBallInt)long_x < 0) left = 0;
                    else left = (DxBallInt)long_x;
                    dxball_fill_horizontal_span(pixels, left, right, color);
                }
                ++y; pixels += pitch; long_x += long_step; short_x += short_step;
            }
        } else {
            while (y2 > y) {
                if (y >= 0 && y < 480) {
                    DxBallInt right, left;
                    if ((DxBallInt)long_x <= 639) right = (DxBallInt)long_x;
                    else right = 639;
                    if ((DxBallInt)short_x < 0) left = 0;
                    else left = (DxBallInt)short_x;
                    dxball_fill_horizontal_span(pixels, left, right, color);
                }
                ++y; pixels += pitch; long_x += long_step; short_x += short_step;
            }
        }
    }
    if (y3 - y2 == 0) return;
    short_step = DxBallFixedPoint(x3 - x2) / DxBallFixedPoint(y3 - y2);
    short_x = DxBallFixedPoint(x2);
    if (long_x < short_x) {
        while (y3 > y) {
            if (y >= 0 && y < 480) {
                DxBallInt right, left;
                if ((DxBallInt)short_x <= 639) right = (DxBallInt)short_x;
                else right = 639;
                if ((DxBallInt)long_x < 0) left = 0;
                else left = (DxBallInt)long_x;
                dxball_fill_horizontal_span(pixels, left, right, color);
            }
            ++y; pixels += pitch; long_x += long_step; short_x += short_step;
        }
    } else {
        while (y3 > y) {
            if (y >= 0 && y < 480) {
                DxBallInt right, left;
                if ((DxBallInt)long_x <= 639) right = (DxBallInt)long_x;
                else right = 639;
                if ((DxBallInt)short_x < 0) left = 0;
                else left = (DxBallInt)short_x;
                dxball_fill_horizontal_span(pixels, left, right, color);
            }
            ++y; pixels += pitch; long_x += long_step; short_x += short_step;
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
    return dxball_raster_ops.muldiv(number, 65536, denominator);
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

