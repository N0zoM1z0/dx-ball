#ifndef DXBALL_RESOURCES_H
#define DXBALL_RESOURCES_H

#include "boards.h"

/* This attribute follows the platform ABI, never an exact/normal source profile.
   The original i386 DirectDraw interfaces use stdcall; the native analysis host
   uses its native C ABI with the same owner declarations. */
#if defined(_WIN32)
#define DXBALL_DDCALL __stdcall
#else
#define DXBALL_DDCALL
#endif

typedef struct DxBallDDSurface DxBallDDSurface;
typedef struct DxBallDDraw DxBallDDraw;
typedef struct DxBallDDPalette DxBallDDPalette;
typedef struct DxBallPaletteEntry DxBallPaletteEntry;
typedef void (DXBALL_DDCALL *DxBallUnknownDDMethod)(void);

typedef struct DxBallSurfaceDesc {
    DxBallUInt size, flags, height, width;
    DxBallInt pitch;
    DxBallUInt ancillary[4];
    DxBallByte *pixels;
    DxBallUInt color_keys[8];
    DxBallUInt pixel_format[8];
    DxBallUInt caps;
} DxBallSurfaceDesc;

typedef struct DxBallColorKey {
    DxBallUInt low, high;
} DxBallColorKey;

/* Unknown slots are opaque and never invoked by this owner. Known slot indices
   come from target calls, corroborated by the original DirectDraw interface. */
typedef struct DxBallDDSurfaceVTable {
    DxBallUnknownDDMethod query_interface, add_ref;
    DxBallUInt (DXBALL_DDCALL *release)(DxBallDDSurface *);
    DxBallUnknownDDMethod add_attached_surface, add_overlay_dirty_rect;
    DxBallInt (DXBALL_DDCALL *blt)(DxBallDDSurface *, const DxBallRect *,
                                 DxBallDDSurface *, const DxBallRect *, DxBallUInt, void *);
    DxBallUnknownDDMethod blt_batch;
    DxBallInt (DXBALL_DDCALL *blt_fast)(DxBallDDSurface *, DxBallUInt, DxBallUInt,
                                      DxBallDDSurface *, const DxBallRect *, DxBallUInt);
    DxBallUnknownDDMethod slots_8_to_10[3];
    DxBallInt (DXBALL_DDCALL *flip)(DxBallDDSurface *, DxBallDDSurface *, DxBallUInt);
    DxBallUnknownDDMethod slot_12;
    DxBallInt (DXBALL_DDCALL *get_blt_status)(DxBallDDSurface *, DxBallUInt);
    DxBallUnknownDDMethod slots_14_to_21[8];
    DxBallInt (DXBALL_DDCALL *get_desc)(DxBallDDSurface *, DxBallSurfaceDesc *);
    DxBallUnknownDDMethod initialize, is_lost;
    DxBallInt (DXBALL_DDCALL *lock)(DxBallDDSurface *, const DxBallRect *,
                                  DxBallSurfaceDesc *, DxBallUInt, void *);
    DxBallUnknownDDMethod release_dc;
    DxBallInt (DXBALL_DDCALL *restore)(DxBallDDSurface *);
    DxBallUnknownDDMethod set_clipper;
    DxBallInt (DXBALL_DDCALL *set_color_key)(DxBallDDSurface *, DxBallUInt,
                                            const DxBallColorKey *);
    DxBallUnknownDDMethod set_overlay_position;
    DxBallInt (DXBALL_DDCALL *set_palette)(DxBallDDSurface *, DxBallDDPalette *);
    DxBallInt (DXBALL_DDCALL *unlock)(DxBallDDSurface *, void *);
} DxBallDDSurfaceVTable;

struct DxBallDDSurface { const DxBallDDSurfaceVTable *vtable; };

typedef struct DxBallDDrawVTable {
    DxBallUnknownDDMethod slots_0_to_4[5];
    DxBallInt (DXBALL_DDCALL *create_palette)(DxBallDDraw *, DxBallUInt,
        DxBallPaletteEntry *, DxBallDDPalette **, void *);
    DxBallInt (DXBALL_DDCALL *create_surface)(DxBallDDraw *, DxBallSurfaceDesc *,
                                             DxBallDDSurface **, void *);
    DxBallUnknownDDMethod slots_7_to_21[15];
    DxBallInt (DXBALL_DDCALL *wait_vertical_blank)(DxBallDDraw *, DxBallUInt, void *);
} DxBallDDrawVTable;
struct DxBallDDraw { const DxBallDDrawVTable *vtable; };

struct DxBallPaletteEntry { DxBallByte red, green, blue, flags; };
typedef struct DxBallDDPaletteVTable {
    DxBallUnknownDDMethod slots_0_to_5[6];
    DxBallInt (DXBALL_DDCALL *set_entries)(DxBallDDPalette *, DxBallUInt, DxBallUInt,
                                          DxBallUInt, const DxBallPaletteEntry *);
} DxBallDDPaletteVTable;
struct DxBallDDPalette { const DxBallDDPaletteVTable *vtable; };

typedef struct DxBallSprite {
    DxBallDDSurface *surface;
    DxBallInt opaque;
    DxBallInt width, height, pitch;
    DxBallRect source_rect;
    char code;
    DxBallInt baseline;
} DxBallSprite;

typedef struct DxBallSpriteBank {
    DxBallSprite *sprites[255];
    DxBallInt count, allocation_mode;
    char filename[20];
} DxBallSpriteBank;

extern DxBallSpriteBank dxball_sprite_banks[3];
extern DxBallInt dxball_sprite_bank, dxball_font_bank;
extern DxBallDDraw *dxball_direct_draw;
extern DxBallDDPalette *dxball_direct_palette;
extern DxBallPaletteEntry dxball_live_palette[256], dxball_saved_palette[256];

/* Valid bank indices are 0..2; sprite indices are caller-owned 1..254. */
void dxball_select_sprite_bank(DxBallInt bank);
void dxball_select_font_bank(DxBallInt bank);
void dxball_draw_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_draw_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_blt_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_blt_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_stretch_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                                DxBallInt width, DxBallInt height);
void dxball_release_sprite(DxBallInt sprite);
void dxball_capture_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                           DxBallInt width, DxBallInt height);
void dxball_load_sprite_bank(DxBallInt bank, DxBallInt allocation_mode, const char *path);
DxBallInt dxball_find_glyph(char code);
DxBallInt dxball_draw_glyph(char code, DxBallInt x, DxBallInt baseline);
void dxball_load_live_palette(const char *path);
void dxball_load_saved_palette(const char *path);
/* Read the live RGB tail, create a palette and attach it after successful creation. */
void dxball_load_surface_palette(DxBallDDSurface *, const char *);
void dxball_load_pcx(DxBallDDSurface *surface, const char *path,
                     DxBallInt palette_mode, DxBallInt x, DxBallInt y);

#endif
