/* Host analysis utility, not an original DX-Ball function or display backend.
   Exercise the maintained decoder with owned, pitch-padded memory surfaces. */
#include "resources.h"
#include <stdlib.h>
#include <string.h>

typedef struct MemorySurface {
    DxBallDDSurface interface;
    DxBallInt width, height, pitch;
    DxBallByte *pixels;
} MemorySurface;

static DxBallDDSurfaceVTable surface_methods;
static DxBallDDrawVTable draw_methods;
static DxBallDDPaletteVTable palette_methods;

static DxBallUInt DXBALL_DDCALL release_surface(DxBallDDSurface *surface)
{
    MemorySurface *memory = (MemorySurface *)surface;
    free(memory->pixels);
    free(memory);
    return 0;
}

static DxBallInt DXBALL_DDCALL describe_surface(DxBallDDSurface *surface,
                                               DxBallSurfaceDesc *description)
{
    MemorySurface *memory = (MemorySurface *)surface;
    description->width = memory->width;
    description->height = memory->height;
    description->pitch = memory->pitch;
    description->pixels = memory->pixels;
    return 0;
}

static DxBallInt DXBALL_DDCALL lock_surface(DxBallDDSurface *surface,
    const DxBallRect *rect, DxBallSurfaceDesc *description, DxBallUInt flags, void *event)
{
    (void)rect; (void)flags; (void)event;
    return describe_surface(surface, description);
}

static DxBallInt DXBALL_DDCALL unlock_surface(DxBallDDSurface *surface, void *pixels)
{
    (void)surface; (void)pixels;
    return 0;
}

static DxBallInt DXBALL_DDCALL set_key(DxBallDDSurface *surface,
                                      DxBallUInt flags, const DxBallColorKey *key)
{
    (void)surface; (void)flags; (void)key;
    return 0;
}

static DxBallInt DXBALL_DDCALL set_entries(DxBallDDPalette *palette,
    DxBallUInt flags, DxBallUInt start, DxBallUInt count, const DxBallPaletteEntry *entries)
{
    (void)palette; (void)flags; (void)start; (void)count; (void)entries;
    return 0;
}

static DxBallInt DXBALL_DDCALL create_surface(DxBallDDraw *draw,
    DxBallSurfaceDesc *description, DxBallDDSurface **output, void *outer)
{
    MemorySurface *memory;
    size_t bytes;
    (void)draw; (void)outer;
    *output = NULL;
    if (description->width == 0 || description->width > 4096 ||
        description->height == 0 || description->height > 4096)
        return -1;
    memory = (MemorySurface *)malloc(sizeof(*memory));
    if (memory == NULL)
        return -1;
    memory->width = description->width;
    memory->height = description->height;
    memory->pitch = memory->width + 3;
    bytes = (size_t)memory->pitch * memory->height;
    memory->pixels = (DxBallByte *)malloc(bytes);
    if (memory->pixels == NULL) {
        free(memory);
        return -1;
    }
    memset(memory->pixels, 0xa5, bytes);
    memory->interface.vtable = &surface_methods;
    *output = &memory->interface;
    return 0;
}

static DxBallUInt fingerprint(const void *data, size_t size)
{
    const DxBallByte *bytes = (const DxBallByte *)data;
    DxBallUInt value = 2166136261U;
    size_t i;
    for (i = 0; i < size; i = i + 1)
        value = (value ^ bytes[i]) * 16777619U;
    return value;
}

static int inspect_bank(const char *path)
{
    DxBallInt i;
    DxBallSprite *sprite;
    MemorySurface *memory;
    if (strlen(path) >= sizeof(dxball_sprite_banks[0].filename)) {
        fprintf(stderr, "SBK requires a basename shorter than 20 bytes\n");
        return 2;
    }
    dxball_load_sprite_bank(0, 1, path);
    printf("{\"count\":%d,\"sprites\":[", dxball_sprite_banks[0].count);
    for (i = 1; i <= dxball_sprite_banks[0].count; i = i + 1) {
        sprite = dxball_sprite_banks[0].sprites[i];
        if (sprite == NULL || sprite->surface == NULL)
            return 3;
        memory = (MemorySurface *)sprite->surface;
        printf("%s{\"width\":%d,\"height\":%d,\"pitch\":%d,\"code\":%u,\"baseline\":%d,\"pixels\":\"%08x\"}",
            i == 1 ? "" : ",", sprite->width, sprite->height, sprite->pitch,
            (unsigned int)(DxBallByte)sprite->code, sprite->baseline,
            fingerprint(memory->pixels, (size_t)memory->pitch * memory->height));
    }
    printf("]}\n");
    for (i = 1; i <= dxball_sprite_banks[0].count; i = i + 1)
        dxball_release_sprite(i);
    return 0;
}

static int inspect_pcx(const char *path)
{
    DxBallSurfaceDesc description;
    DxBallDDSurface *surface;
    MemorySurface *memory;
    description.width = 640;
    description.height = 480;
    if (create_surface(dxball_direct_draw, &description, &surface, NULL) != 0)
        return 3;
    memset(dxball_live_palette, 0xa5, sizeof(dxball_live_palette));
    dxball_load_pcx(surface, path, 1, 0, 0);
    memory = (MemorySurface *)surface;
    printf("{\"width\":%d,\"height\":%d,\"pitch\":%d,\"pixels\":\"%08x\",\"palette\":\"%08x\"}\n",
        memory->width, memory->height, memory->pitch,
        fingerprint(memory->pixels, (size_t)memory->pitch * memory->height),
        fingerprint(dxball_live_palette, sizeof(dxball_live_palette)));
    release_surface(surface);
    return 0;
}

int main(int argc, char **argv)
{
    DxBallDDraw draw;
    DxBallDDPalette palette;
    FILE *probe;
    if (argc != 3 || (strcmp(argv[1], "--sbk") != 0 && strcmp(argv[1], "--pcx") != 0)) {
        fprintf(stderr, "Usage: dxball_resources --sbk BASENAME | --pcx FILE\n");
        return 2;
    }
    probe = fopen(argv[2], "rb");
    if (probe == NULL) {
        fprintf(stderr, "Cannot open resource\n");
        return 2;
    }
    fclose(probe);
    surface_methods.release = release_surface;
    surface_methods.get_desc = describe_surface;
    surface_methods.lock = lock_surface;
    surface_methods.unlock = unlock_surface;
    surface_methods.set_color_key = set_key;
    draw_methods.create_surface = create_surface;
    palette_methods.set_entries = set_entries;
    draw.vtable = &draw_methods;
    palette.vtable = &palette_methods;
    dxball_direct_draw = &draw;
    dxball_direct_palette = &palette;
    return strcmp(argv[1], "--sbk") == 0 ? inspect_bank(argv[2]) : inspect_pcx(argv[2]);
}
