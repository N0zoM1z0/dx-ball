extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00409790 */
void dxball_load_live_palette(const char *path)
{
    FILE *file;
    DxBallInt color;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_live_palette[color].red = (DxBallByte)getc(file);
        dxball_live_palette[color].green = (DxBallByte)getc(file);
        dxball_live_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    dxball_direct_palette->set_entries(0, 0, 256,
                                              dxball_live_palette);
    return;
}

