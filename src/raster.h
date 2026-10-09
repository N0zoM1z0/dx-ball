#ifndef DXBALL_RASTER_H
#define DXBALL_RASTER_H
#include "state_types.h"

#if defined(_WIN32)
#define DXBALL_RASTER_CALL __stdcall
#else
#define DXBALL_RASTER_CALL
#endif

typedef struct DxBallRasterPoint { DxBallInt x, y; } DxBallRasterPoint;
typedef struct DxBallRasterOps {
    void *(*allocate)(size_t bytes);
    void (*deallocate)(void *memory);
    DxBallInt (DXBALL_RASTER_CALL *muldiv)(DxBallInt number, DxBallInt numerator, DxBallInt denominator);
} DxBallRasterOps;
#ifdef __cplusplus
extern "C" {
#endif
extern DxBallRasterOps dxball_raster_ops;
DxBallInt dxball_fixed_divide(DxBallInt number, DxBallInt denominator);

/* Coordinates, differences, fixed-point products, edge carries and pointer
   arithmetic must be representable. Backing must cover the visited spans.
   Polygons require a positive count and a closed contour with nonhorizontal
   edges. Unclipped polygons require in-bounds coordinates; clipped routines
   use the original fixed 640-by-480 bounds, independent of supplied pitch. */
void dxball_fill_horizontal_span(DxBallByte *row, DxBallInt left,
                                DxBallInt right, DxBallByte color);
void DXBALL_RASTER_CALL dxball_fill_polygon(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color);
void DXBALL_RASTER_CALL dxball_fill_polygon_clipped(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color);
/* This entry is cdecl, confirmed through its separate shared SEH epilogue. */
void dxball_fill_triangle(DxBallByte *pixels, DxBallInt pitch,
    DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2,
    DxBallInt x3, DxBallInt y3, DxBallByte color);
#ifdef __cplusplus
}

/* A four-byte, nonvirtual signed 16.16 value. Default construction preserves
   the scalar; the nontrivial destructor gives temporaries their real lifetime.
   Coordinate products, divisions and accumulated sums must be representable. */
class DxBallFixedPoint {
public:
    DxBallInt value;
    DxBallFixedPoint();
    ~DxBallFixedPoint();
    DxBallFixedPoint(DxBallInt integer);
    operator DxBallInt();
    DxBallFixedPoint operator/(DxBallFixedPoint denominator);
    DxBallInt operator<(DxBallFixedPoint other);
    DxBallFixedPoint &operator+=(DxBallFixedPoint increment);
};
#endif
#endif
