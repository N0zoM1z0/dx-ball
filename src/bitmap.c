#include "bitmap.h"
#include "file.h"
#include "memory.h"
#include <string.h>

const char dxball_bitmap_fallback_prefix[] = "..\\";

/* FUNCTION: DXBALL 0x00409F70 */
DxBallInt dxball_load_bitmap(DxBallDDSurface *surface, const char *path)
{
    char fallback[260];
    DxBallByte header[14];
    DxBallBitmapInfo info;
    DxBallBitmapColor colors[256];
    DxBallPaletteEntry entries[256];
    DxBallDDPalette *palette;
    DxBallSurfaceDesc desc;
    DxBallUInt transferred;
    DxBallInt result, count, i;
    DxBallByte *pixels;
    size_t source, destination;
    DxBallHandle file;

    file = dxball_file_create(path, 0x80000000, 1, NULL, 3, 0x80, 0);
    if (file == (DxBallHandle)-1) {
        strcpy(fallback, dxball_bitmap_fallback_prefix);
        strcat(fallback, path);
        file = dxball_file_create(fallback, 0x80000000, 1, NULL, 3, 0x80, 0);
        if (file == (DxBallHandle)-1) return 0;
    }
    /* ReadFile success is tested; transferred counts are deliberately ignored.
       Untouched local suffixes are not assigned deterministic values. */
    if (!dxball_file_read(file, header, 14, &transferred, NULL)) return 0;
    if (!dxball_file_read(file, &info, 40, &transferred, NULL)) return 0;
    if (info.bits != 8) return 0;
    if (!dxball_file_read(file, colors, 1024, &transferred, NULL)) return 0;

    pixels = (DxBallByte *)dxball_local_alloc(0x40,
        (DxBallUInt)info.width * (DxBallUInt)info.height);
    if (pixels == NULL) return 0;
    if (!dxball_file_read(file, pixels,
        (DxBallUInt)info.width * (DxBallUInt)info.height, &transferred, NULL)) {
        dxball_local_free(pixels);
        return 0;
    }
    memset(&desc, 0, sizeof(desc));
    desc.size = sizeof(desc);
    result = surface->vtable->lock(surface, NULL, &desc, 0, NULL);
    if (result != 0) {
        dxball_local_free(pixels);
        return 0;
    }
    destination = (size_t)desc.pixels;
    /* Use integer addresses: the final source retreat can pass the allocation
       start without another dereference, as in the original x86 loop. */
    source = (size_t)pixels + (DxBallUInt)(info.height - 1) * (DxBallUInt)info.width;
    if (info.width > desc.pitch) count = desc.pitch;
    else count = info.width;
    for (i = 0; i < info.height; ++i) {
        memcpy((void *)destination, (const void *)source, (size_t)count);
        destination += desc.pitch;
        source -= count;
    }
    surface->vtable->unlock(surface, NULL);
    dxball_local_free(pixels);
    dxball_file_close(file);
    for (i = 0; i < 256; ++i) {
        entries[i].red = colors[i].red;
        entries[i].green = colors[i].green;
        entries[i].blue = colors[i].blue;
        /* flags is unwritten in the original, not a reconstructed constant. */
    }
    result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
                                                      entries, &palette, NULL);
    if (result != 0) return 0;
    surface->vtable->set_palette(surface, palette);
    return 1;
}
