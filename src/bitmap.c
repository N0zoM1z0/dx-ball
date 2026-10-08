#include "bitmap.h"
#include <string.h>

DxBallBitmapApi dxball_bitmap_api;

static DxBallUInt read_u32(const DxBallByte *p)
{
    return (DxBallUInt)p[0] | ((DxBallUInt)p[1] << 8) |
           ((DxBallUInt)p[2] << 16) | ((DxBallUInt)p[3] << 24);
}

/* FUNCTION: DXBALL 0x00409F70 */
DxBallInt dxball_load_bitmap(DxBallDDSurface *surface, const char *path)
{
    char fallback[260];
    DxBallByte header[14], info[40], colors[1024];
    DxBallPaletteEntry entries[256];
    DxBallDDPalette *palette;
    DxBallSurfaceDesc desc;
    DxBallUInt transferred, size;
    DxBallInt width, height, count, y, i;
    DxBallByte *pixels;
    size_t source, destination, file;

    file = dxball_bitmap_api.create_file(path, 0x80000000, 1, NULL, 3, 0x80, 0);
    if (file == (size_t)-1) {
        strcpy(fallback, "..\\");
        strcat(fallback, path);
        file = dxball_bitmap_api.create_file(fallback, 0x80000000, 1, NULL, 3, 0x80, 0);
        if (file == (size_t)-1) return 0;
    }
    /* ReadFile success is tested; transferred counts are deliberately ignored.
       Untouched local suffixes are not assigned deterministic values. */
    if (!dxball_bitmap_api.read_file(file, header, 14, &transferred, NULL)) return 0;
    if (!dxball_bitmap_api.read_file(file, info, 40, &transferred, NULL)) return 0;
    if (((DxBallUInt)info[14] | ((DxBallUInt)info[15] << 8)) != 8) return 0;
    if (!dxball_bitmap_api.read_file(file, colors, 1024, &transferred, NULL)) return 0;

    width = (DxBallInt)read_u32(info + 4);
    height = (DxBallInt)read_u32(info + 8);
    size = (DxBallUInt)width * (DxBallUInt)height;
    pixels = (DxBallByte *)dxball_bitmap_api.local_alloc(0x40, size);
    if (pixels == NULL) return 0;
    if (!dxball_bitmap_api.read_file(file, pixels, size, &transferred, NULL)) {
        dxball_bitmap_api.local_free(pixels);
        return 0;
    }
    memset(&desc, 0, sizeof(desc));
    desc.size = sizeof(desc);
    if (surface->vtable->lock(surface, NULL, &desc, 0, NULL) != 0) {
        dxball_bitmap_api.local_free(pixels);
        return 0;
    }
    count = desc.pitch < width ? desc.pitch : width;
    /* Use integer addresses: the final source retreat can pass the allocation
       start without another dereference, as in the original x86 loop. */
    source = (size_t)pixels + (size_t)(height - 1) * (DxBallUInt)width;
    destination = (size_t)desc.pixels;
    for (y = 0; y < height; ++y) {
        memcpy((void *)destination, (const void *)source, (size_t)count);
        destination += desc.pitch;
        source -= count;
    }
    surface->vtable->unlock(surface, NULL);
    dxball_bitmap_api.local_free(pixels);
    dxball_bitmap_api.close_file(file);
    for (i = 0; i < 256; ++i) {
        entries[i].red = colors[i * 4 + 2];
        entries[i].green = colors[i * 4 + 1];
        entries[i].blue = colors[i * 4];
        /* flags is unwritten in the original, not a reconstructed constant. */
    }
    if (dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
                                                  entries, &palette, NULL) != 0)
        return 0;
    surface->vtable->set_palette(surface, palette);
    return 1;
}
