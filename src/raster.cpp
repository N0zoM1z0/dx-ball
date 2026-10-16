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

#if defined(_WIN32)
extern "C" DxBallInt DXBALL_RASTER_CALL MulDiv(
    DxBallInt number, DxBallInt numerator, DxBallInt denominator);
DxBallRasterOps dxball_raster_ops = { malloc, free, MulDiv };
#else
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
#endif

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

/* Pending and active edges share one scan/sort workspace. Every field has
   an actual producer and consumer; the two sort exchanges remain distinct. */
struct RasterPolygonWorkspace {
    RasterEdge *edge;
    DxBallByte *row;
    RasterEdge *active_exchange, *pending_exchange;
    DxBallInt j;
    RasterEdge **pending, **active;
    DxBallInt i, y;
    RasterEdge *storage;
    DxBallInt gap, used, live;
    DxBallInt left, next;
    DxBallInt right;
};

/* FUNCTION: DXBALL 0x0040B550 */
void DXBALL_RASTER_CALL dxball_fill_polygon(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color)
{
    RasterPolygonWorkspace work;
    DxBallRasterPoint first, second;
    work.storage = (RasterEdge *)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.storage)));
    work.pending = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.pending)));
    work.active = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.active)));
    if (work.storage == NULL || work.pending == NULL || work.active == NULL) {
        if (work.storage != NULL) dxball_heap_release(work.storage);
        if (work.pending != NULL) dxball_heap_release(work.pending);
        if (work.active != NULL) dxball_heap_release(work.active);
        return;
    }
    work.i = 0;
    work.used = 0;
    for (; work.i < count; ++work.i) {
        first = points[work.i];
        second = points[(work.i + 1) % count];
        if (first.y == second.y)
            continue;
        if (first.y > second.y) {
            first = second;
            second = points[work.i];
        }
        work.storage[work.used].top = first.y;
        work.storage[work.used].bottom = second.y;
        work.storage[work.used].x = first.x;
        work.storage[work.used].dx = second.x - first.x;
        work.storage[work.used].dy = second.y - first.y;
        work.storage[work.used].error = 0;
        work.pending[work.used] = &work.storage[work.used];
        ++work.used;
    }
    for (work.gap = 1; work.gap < work.used; work.gap = work.gap * 3 + 1) { }
    for (work.gap /= 3; work.gap > 0; work.gap /= 3) {
        for (work.i = work.gap; work.i < work.used; ++work.i) {
            for (work.j = work.i - work.gap; work.j >= 0; work.j -= work.gap) {
                if (work.pending[work.j + work.gap]->top >= work.pending[work.j]->top)
                    break;
                work.pending_exchange = work.pending[work.j];
                work.pending[work.j] = work.pending[work.j + work.gap];
                work.pending[work.j + work.gap] = work.pending_exchange;
            }
        }
    }
    work.live = 0;
    work.next = 0;
    /* A nonhorizontal closed contour and representable arithmetic are the
       original routine's required domain; its zero-work.edge read is unresolved. */
    work.y = work.pending[work.next]->top;
    while (work.next < work.used || work.live != 0) {
        while (work.next < work.used && work.pending[work.next]->top == work.y)
            work.active[work.live++] = work.pending[work.next++];
        work.i = 0;
        while (work.i < work.live) {
            if (work.active[work.i]->bottom == work.y) {
                --work.live;
                memmove(&work.active[work.i], &work.active[work.i + 1], (work.live - work.i) * sizeof(*work.active));
            } else {
                ++work.i;
            }
        }
        for (work.gap = 1; work.gap < work.live; work.gap = work.gap * 3 + 1) { }
        for (work.gap /= 3; work.gap > 0; work.gap /= 3) {
            for (work.i = work.gap; work.i < work.live; ++work.i) {
                for (work.j = work.i - work.gap; work.j >= 0; work.j -= work.gap) {
                    if (work.active[work.j + work.gap]->x >= work.active[work.j]->x)
                        break;
                    work.active_exchange = work.active[work.j];
                    work.active[work.j] = work.active[work.j + work.gap];
                    work.active[work.j + work.gap] = work.active_exchange;
                }
            }
        }
        for (work.i = 0; work.i < work.live; work.i += 2) {
            work.left = work.active[work.i]->x;
            work.right = work.active[work.i + 1]->x;
            if (work.active[work.i]->error > 0) ++work.left;
            if (work.active[work.i + 1]->error <= 0) --work.right;
            if (work.left <= work.right) {
                work.row = pixels + work.y * pitch;
                dxball_fill_horizontal_span(work.row, work.left, work.right, color);
            }
        }
        for (work.i = 0; work.i < work.live; ++work.i) {
            work.edge = work.active[work.i];
            work.edge->error += work.edge->dx;
            if (work.edge->dx < 0) {
                while (work.edge->dy <= -work.edge->error) {
                    work.edge->error += work.edge->dy;
                    --work.edge->x;
                }
            } else {
                while (work.edge->dy <= work.edge->error) {
                    work.edge->error -= work.edge->dy;
                    ++work.edge->x;
                }
            }
        }
        ++work.y;
    }
    dxball_heap_release(work.storage);
    dxball_heap_release(work.pending);
    dxball_heap_release(work.active);
    return;
}

/* FUNCTION: DXBALL 0x0040BB60 */
void DXBALL_RASTER_CALL dxball_fill_polygon_clipped(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color)
{
    RasterPolygonWorkspace work;
    DxBallRasterPoint first, second;
    work.storage = (RasterEdge *)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.storage)));
    work.pending = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.pending)));
    work.active = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*work.active)));
    if (work.storage == NULL || work.pending == NULL || work.active == NULL) {
        if (work.storage != NULL) dxball_heap_release(work.storage);
        if (work.pending != NULL) dxball_heap_release(work.pending);
        if (work.active != NULL) dxball_heap_release(work.active);
        return;
    }
    work.i = 0;
    work.used = 0;
    for (; work.i < count; ++work.i) {
        first = points[work.i];
        second = points[(work.i + 1) % count];
        if (first.y == second.y)
            continue;
        if (first.y > second.y) {
            first = second;
            second = points[work.i];
        }
        work.storage[work.used].top = first.y;
        work.storage[work.used].bottom = second.y;
        work.storage[work.used].x = first.x;
        work.storage[work.used].dx = second.x - first.x;
        work.storage[work.used].dy = second.y - first.y;
        work.storage[work.used].error = 0;
        work.pending[work.used] = &work.storage[work.used];
        ++work.used;
    }
    for (work.gap = 1; work.gap < work.used; work.gap = work.gap * 3 + 1) { }
    for (work.gap /= 3; work.gap > 0; work.gap /= 3) {
        for (work.i = work.gap; work.i < work.used; ++work.i) {
            for (work.j = work.i - work.gap; work.j >= 0; work.j -= work.gap) {
                if (work.pending[work.j + work.gap]->top >= work.pending[work.j]->top)
                    break;
                work.pending_exchange = work.pending[work.j];
                work.pending[work.j] = work.pending[work.j + work.gap];
                work.pending[work.j + work.gap] = work.pending_exchange;
            }
        }
    }
    work.live = 0;
    work.next = 0;
    /* A nonhorizontal closed contour and representable arithmetic are the
       original routine's required domain; its zero-work.edge read is unresolved. */
    work.y = work.pending[work.next]->top;
    while (work.next < work.used || work.live != 0) {
        while (work.next < work.used && work.pending[work.next]->top == work.y)
            work.active[work.live++] = work.pending[work.next++];
        work.i = 0;
        while (work.i < work.live) {
            if (work.active[work.i]->bottom == work.y) {
                --work.live;
                memmove(&work.active[work.i], &work.active[work.i + 1], (work.live - work.i) * sizeof(*work.active));
            } else {
                ++work.i;
            }
        }
        for (work.gap = 1; work.gap < work.live; work.gap = work.gap * 3 + 1) { }
        for (work.gap /= 3; work.gap > 0; work.gap /= 3) {
            for (work.i = work.gap; work.i < work.live; ++work.i) {
                for (work.j = work.i - work.gap; work.j >= 0; work.j -= work.gap) {
                    if (work.active[work.j + work.gap]->x >= work.active[work.j]->x)
                        break;
                    work.active_exchange = work.active[work.j];
                    work.active[work.j] = work.active[work.j + work.gap];
                    work.active[work.j + work.gap] = work.active_exchange;
                }
            }
        }
        for (work.i = 0; work.i < work.live; work.i += 2) {
            work.left = work.active[work.i]->x;
            work.right = work.active[work.i + 1]->x;
            if (work.active[work.i]->error > 0) ++work.left;
            if (work.active[work.i + 1]->error <= 0) --work.right;
            if (work.left <= work.right && work.y >= 0 && work.y < 480) {
                work.row = pixels + work.y * pitch;
                dxball_fill_horizontal_span(work.row, work.left > 0 ? work.left : 0,
                    work.right < 639 ? work.right : 639, color);
            }
        }
        for (work.i = 0; work.i < work.live; ++work.i) {
            work.edge = work.active[work.i];
            work.edge->error += work.edge->dx;
            if (work.edge->dx < 0) {
                while (work.edge->dy <= -work.edge->error) {
                    work.edge->error += work.edge->dy;
                    --work.edge->x;
                }
            } else {
                while (work.edge->dy <= work.edge->error) {
                    work.edge->error -= work.edge->dy;
                    ++work.edge->x;
                }
            }
        }
        ++work.y;
    }
    dxball_heap_release(work.storage);
    dxball_heap_release(work.pending);
    dxball_heap_release(work.active);
    return;
}

/* FUNCTION: DXBALL 0x0040AB90 */
void dxball_fill_triangle(DxBallByte *pixels, DxBallInt pitch,
    DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2,
    DxBallInt x3, DxBallInt y3, DxBallByte color)
{
    DxBallFixedPoint long_step, short_step, long_x, short_x;
    DxBallInt vertical_scale;
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
    {
        DxBallInt y;
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

