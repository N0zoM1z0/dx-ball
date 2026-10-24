extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00409A30 */
void dxball_load_surface_palette(DxBallDDSurface *surface, const char *path)
{
    FILE *file;
    DxBallInt color, result;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_live_palette[color].red = (DxBallByte)getc(file);
        dxball_live_palette[color].green = (DxBallByte)getc(file);
        dxball_live_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    result = dxball_direct_draw->vtable->create_palette(dxball_direct_draw, 4,
        dxball_live_palette, &dxball_direct_palette, NULL);
    if (result != 0) {
        return;
    }
    result = surface->set_palette(dxball_direct_palette);
    return;
}

