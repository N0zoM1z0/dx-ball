#ifndef DXBALL_BITMAP_H
#define DXBALL_BITMAP_H

#include "resources.h"

typedef struct DxBallBitmapInfo {
    DxBallUInt size;
    DxBallInt width, height;
    unsigned short planes, bits;
    DxBallUInt compression, image_bytes;
    DxBallInt x_pixels_per_meter, y_pixels_per_meter;
    DxBallUInt colors_used, colors_important;
} DxBallBitmapInfo;

typedef struct DxBallBitmapColor {
    DxBallByte blue, green, red, reserved;
} DxBallBitmapColor;

extern const char dxball_bitmap_fallback_prefix[];

/* The original accepts sequential 8-bit data, not the general BMP format.
   Bounded backing/geometry and fallback paths fitting MAX_PATH are required.
   Successful short reads and palette flags retain unwritten stack bytes. */
DxBallInt dxball_load_bitmap(DxBallDDSurface *surface, const char *path);

#endif
