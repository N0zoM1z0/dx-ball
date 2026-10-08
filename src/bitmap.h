#ifndef DXBALL_BITMAP_H
#define DXBALL_BITMAP_H

#include "resources.h"

/* Opaque file handles grow with the native host; Win32 uses four bytes. */
typedef struct DxBallBitmapApi {
    size_t (DXBALL_DDCALL *create_file)(const char *, DxBallUInt, DxBallUInt,
        void *, DxBallUInt, DxBallUInt, size_t);
    DxBallInt (DXBALL_DDCALL *read_file)(size_t, void *, DxBallUInt,
                                       DxBallUInt *, void *);
    void *(DXBALL_DDCALL *local_alloc)(DxBallUInt, size_t);
    void *(DXBALL_DDCALL *local_free)(void *);
    DxBallInt (DXBALL_DDCALL *close_file)(size_t);
} DxBallBitmapApi;

extern DxBallBitmapApi dxball_bitmap_api;

/* The original accepts sequential 8-bit data, not the general BMP format.
   Bounded backing/geometry and fallback paths fitting MAX_PATH are required.
   Successful short reads and palette flags retain unwritten stack bytes. */
DxBallInt dxball_load_bitmap(DxBallDDSurface *surface, const char *path);

#endif
