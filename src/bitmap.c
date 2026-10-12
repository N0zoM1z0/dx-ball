#include "bitmap.h"
#include "file.h"
#include "memory.h"
#include <string.h>

const char dxball_bitmap_fallback_prefix[] = "..\\";

/* FUNCTION: DXBALL 0x00409F70 */
DxBallInt dxball_load_bitmap(DxBallDDSurface *surface, const char *path)
{
    struct {
        DxBallHandle file;
        DxBallDDPalette *palette;
        DxBallSurfaceDesc desc;
        DxBallByte *pixels;
        DxBallInt result, count;
        size_t destination;
        char fallback[260];
        DxBallInt index;
        DxBallByte header[14];
        DxBallBitmapInfo info;
        DxBallPaletteEntry entries[256];
        size_t source;
        DxBallUInt transferred;
        DxBallBitmapColor colors[256];
    } load;

    load.file = dxball_file_create(path, 0x80000000, 1, NULL, 3, 0x80, 0);
    if (load.file == (DxBallHandle)-1) {
        strcpy(load.fallback, dxball_bitmap_fallback_prefix);
        strcat(load.fallback, path);
        load.file = dxball_file_create(load.fallback, 0x80000000, 1, NULL, 3, 0x80, 0);
        if (load.file == (DxBallHandle)-1) return 0;
    }
    /* ReadFile success is tested; load.transferred counts are deliberately ignored.
       Untouched local suffixes are not assigned deterministic values. */
    if (!dxball_file_read(load.file, load.header, 14, &load.transferred, NULL)) return 0;
    if (!dxball_file_read(load.file, &load.info, 40, &load.transferred, NULL)) return 0;
    if (load.info.bits != 8) return 0;
    if (!dxball_file_read(load.file, load.colors, 1024, &load.transferred, NULL)) return 0;

    load.pixels = (DxBallByte *)dxball_local_alloc(0x40,
        (DxBallUInt)load.info.width * (DxBallUInt)load.info.height);
    if (load.pixels == NULL) return 0;
    if (!dxball_file_read(load.file, load.pixels,
        (DxBallUInt)load.info.width * (DxBallUInt)load.info.height, &load.transferred, NULL)) {
        dxball_local_free(load.pixels);
        return 0;
    }
    memset(&load.desc, 0, sizeof(load.desc));
    load.desc.size = sizeof(load.desc);
    load.result = surface->vtable->lock(surface, NULL, &load.desc, 0, NULL);
    if (load.result != 0) {
        dxball_local_free(load.pixels);
        return 0;
    }
    load.destination = (size_t)load.desc.pixels;
    /* Use integer addresses: the final load.source retreat can pass the allocation
       start without another dereference, as in the original x86 loop. */
    load.source = (size_t)load.pixels + (DxBallUInt)(load.info.height - 1) * (DxBallUInt)load.info.width;
    if (load.info.width > load.desc.pitch) load.count = load.desc.pitch;
    else load.count = load.info.width;
    for (load.index = 0; load.index < load.info.height; ++load.index) {
        memcpy((void *)load.destination, (const void *)load.source, (size_t)load.count);
        load.destination += load.desc.pitch;
        load.source -= load.count;
    }
    surface->vtable->unlock(surface, NULL);
    dxball_local_free(load.pixels);
    dxball_file_close(load.file);
    for (load.index = 0; load.index < 256; ++load.index) {
        load.entries[load.index].red = load.colors[load.index].red;
        load.entries[load.index].green = load.colors[load.index].green;
        load.entries[load.index].blue = load.colors[load.index].blue;
        /* flags is unwritten in the original, not a reconstructed constant. */
    }
    load.result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
                                                      load.entries, &load.palette, NULL);
    if (load.result != 0) return 0;
    surface->vtable->set_palette(surface, load.palette);
    return 1;
}
