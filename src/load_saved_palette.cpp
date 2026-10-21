extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x004098F0 */
void dxball_load_saved_palette(const char *path)
{
    FILE *file;
    DxBallInt color;
    file = fopen(path, "rb");
    fseek(file, -768, SEEK_END);
    for (color = 0; color < 256; color = color + 1) {
        dxball_saved_palette[color].red = (DxBallByte)getc(file);
        dxball_saved_palette[color].green = (DxBallByte)getc(file);
        dxball_saved_palette[color].blue = (DxBallByte)getc(file);
    }
    fclose(file);
    return;
}

