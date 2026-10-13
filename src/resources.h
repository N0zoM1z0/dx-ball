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

#ifdef __cplusplus
#if defined(_WIN32)
#include <windows.h>
#include <wtypes.h>
typedef HRESULT DxBallDDResult;
typedef DWORD DxBallDDWord;
typedef ULONG DxBallDDRefCount;
typedef LONG DxBallDDLong;
typedef HDC DxBallDDDC;
typedef HANDLE DxBallDDHandle;
#else
typedef DxBallInt DxBallDDResult;
typedef DxBallUInt DxBallDDWord, DxBallDDRefCount;
typedef DxBallInt DxBallDDLong;
typedef void *DxBallDDDC, *DxBallDDHandle;
#endif
#define DX_DD_RESULT DxBallDDResult
#define DX_DD_WORD DxBallDDWord
#define DX_DD_LONG DxBallDDLong
#define DX_DD_REFCOUNT DxBallDDRefCount
#else
#define DX_DD_RESULT DxBallInt
#define DX_DD_WORD DxBallUInt
#define DX_DD_LONG DxBallInt
#define DX_DD_REFCOUNT DxBallUInt
#endif

typedef struct DxBallDDSurface DxBallDDSurface;
typedef struct DxBallDDraw DxBallDDraw;
typedef struct DxBallDDPalette DxBallDDPalette;
typedef struct DxBallPaletteEntry DxBallPaletteEntry;
typedef void (DXBALL_DDCALL *DxBallUnknownDDMethod)(void);

typedef struct DxBallSurfaceDesc {
    DX_DD_WORD size, flags, height, width;
    DX_DD_LONG pitch;
    DX_DD_WORD ancillary[4];
    DxBallByte *pixels;
    DX_DD_WORD color_keys[8];
    DX_DD_WORD pixel_format[8];
    DX_DD_WORD caps;
} DxBallSurfaceDesc;

typedef struct DxBallColorKey {
    DX_DD_WORD low, high;
} DxBallColorKey;

/* Unknown slots are opaque and never invoked by this owner. Known slot indices
   come from target calls, corroborated by the original DirectDraw interface. */
typedef struct DxBallDDSurfaceVTable {
    DxBallUnknownDDMethod query_interface, add_ref;
    DX_DD_REFCOUNT (DXBALL_DDCALL *release)(DxBallDDSurface *);
    DxBallUnknownDDMethod add_attached_surface, add_overlay_dirty_rect;
    DX_DD_RESULT (DXBALL_DDCALL *blt)(DxBallDDSurface *, DxBallRect *,
                                 DxBallDDSurface *, DxBallRect *, DX_DD_WORD, void *);
    DxBallUnknownDDMethod blt_batch;
    DX_DD_RESULT (DXBALL_DDCALL *blt_fast)(DxBallDDSurface *, DX_DD_WORD, DX_DD_WORD,
                                      DxBallDDSurface *, DxBallRect *, DX_DD_WORD);
    DxBallUnknownDDMethod slots_8_to_10[3];
    DX_DD_RESULT (DXBALL_DDCALL *flip)(DxBallDDSurface *, DxBallDDSurface *, DX_DD_WORD);
    DxBallUnknownDDMethod slot_12;
    DX_DD_RESULT (DXBALL_DDCALL *get_blt_status)(DxBallDDSurface *, DX_DD_WORD);
    DxBallUnknownDDMethod slots_14_to_21[8];
    DX_DD_RESULT (DXBALL_DDCALL *get_desc)(DxBallDDSurface *, DxBallSurfaceDesc *);
    DxBallUnknownDDMethod initialize, is_lost;
    DX_DD_RESULT (DXBALL_DDCALL *lock)(DxBallDDSurface *, DxBallRect *,
                                  DxBallSurfaceDesc *, DX_DD_WORD, void *);
    DxBallUnknownDDMethod release_dc;
    DX_DD_RESULT (DXBALL_DDCALL *restore)(DxBallDDSurface *);
    DxBallUnknownDDMethod set_clipper;
    DX_DD_RESULT (DXBALL_DDCALL *set_color_key)(DxBallDDSurface *, DX_DD_WORD,
                                            DxBallColorKey *);
    DxBallUnknownDDMethod set_overlay_position;
    DX_DD_RESULT (DXBALL_DDCALL *set_palette)(DxBallDDSurface *, DxBallDDPalette *);
    DX_DD_RESULT (DXBALL_DDCALL *unlock)(DxBallDDSurface *, void *);
} DxBallDDSurfaceVTable;

#ifdef __cplusplus
/* C++ projection of the original IDirectDrawSurface interface. Widths use
   the same fixed-width ABI types as the public C view. No virtual destructor. */
struct DxBallDDGuid { DX_DD_WORD a; unsigned short b, c; DxBallByte d[8]; };
struct DxBallDDBltFx;
struct DxBallDDBltBatch;
struct DxBallDDCaps;
struct DxBallDDClipper;
struct DxBallDDPixelFormat;
struct DxBallDDOverlayFx;
typedef DX_DD_RESULT (DXBALL_DDCALL *DxBallDDEnumSurface)(
    DxBallDDSurface *, DxBallSurfaceDesc *, void *);
struct DxBallDDUnknown {
    virtual DX_DD_RESULT DXBALL_DDCALL query_interface(const DxBallDDGuid &, void **) = 0;
    virtual DX_DD_REFCOUNT DXBALL_DDCALL add_ref() = 0;
    virtual DX_DD_REFCOUNT DXBALL_DDCALL release() = 0;
};
struct DxBallDDSurface : public DxBallDDUnknown {
    virtual DX_DD_RESULT DXBALL_DDCALL add_attached_surface(DxBallDDSurface *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL add_overlay_dirty_rect(DxBallRect *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL blt(DxBallRect *, DxBallDDSurface *, DxBallRect *, DX_DD_WORD, DxBallDDBltFx *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL blt_batch(DxBallDDBltBatch *, DX_DD_WORD, DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL blt_fast(DX_DD_WORD, DX_DD_WORD, DxBallDDSurface *, DxBallRect *, DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL delete_attached_surface(DX_DD_WORD, DxBallDDSurface *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL enum_attached_surfaces(void *, DxBallDDEnumSurface) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL enum_overlay_z_orders(DX_DD_WORD, void *, DxBallDDEnumSurface) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL flip(DxBallDDSurface *, DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_attached_surface(DxBallDDCaps *, DxBallDDSurface **) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_blt_status(DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_caps(DxBallDDCaps *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_clipper(DxBallDDClipper **) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_color_key(DX_DD_WORD, DxBallColorKey *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_dc(DxBallDDDC *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_flip_status(DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_overlay_position(DX_DD_LONG *, DX_DD_LONG *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_palette(DxBallDDPalette **) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_pixel_format(DxBallDDPixelFormat *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_desc(DxBallSurfaceDesc *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL initialize(DxBallDDraw *, DxBallSurfaceDesc *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL is_lost() = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL lock(DxBallRect *, DxBallSurfaceDesc *, DX_DD_WORD, DxBallDDHandle) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL release_dc(DxBallDDDC) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL restore() = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL set_clipper(DxBallDDClipper *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL set_color_key(DX_DD_WORD, DxBallColorKey *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL set_overlay_position(DX_DD_LONG, DX_DD_LONG) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL set_palette(DxBallDDPalette *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL unlock(void *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL update_overlay(DxBallRect *, DxBallDDSurface *, DxBallRect *, DX_DD_WORD, DxBallDDOverlayFx *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL update_overlay_display(DX_DD_WORD) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL update_overlay_z_order(DX_DD_WORD, DxBallDDSurface *) = 0;
};
#else
struct DxBallDDSurface { const DxBallDDSurfaceVTable *vtable; };
#endif

typedef struct DxBallDDrawVTable {
    DxBallUnknownDDMethod slots_0_to_4[5];
    DX_DD_RESULT (DXBALL_DDCALL *create_palette)(DxBallDDraw *, DX_DD_WORD,
        DxBallPaletteEntry *, DxBallDDPalette **, void *);
    DX_DD_RESULT (DXBALL_DDCALL *create_surface)(DxBallDDraw *, DxBallSurfaceDesc *,
                                             DxBallDDSurface **, void *);
    DxBallUnknownDDMethod slots_7_to_21[15];
    DX_DD_RESULT (DXBALL_DDCALL *wait_vertical_blank)(DxBallDDraw *, DX_DD_WORD, void *);
} DxBallDDrawVTable;
struct DxBallDDraw { const DxBallDDrawVTable *vtable; };

struct DxBallPaletteEntry { DxBallByte red, green, blue, flags; };
typedef struct DxBallDDPaletteVTable {
    DxBallUnknownDDMethod slots_0_to_5[6];
    DX_DD_RESULT (DXBALL_DDCALL *set_entries)(DxBallDDPalette *, DX_DD_WORD, DX_DD_WORD,
                                          DX_DD_WORD, DxBallPaletteEntry *);
} DxBallDDPaletteVTable;
#ifdef __cplusplus
/* Seven original IDirectDrawPalette slots, inherited IUnknown first. */
struct DxBallDDPalette : public DxBallDDUnknown {
    virtual DX_DD_RESULT DXBALL_DDCALL get_caps(DX_DD_WORD *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL get_entries(DX_DD_WORD, DX_DD_WORD, DX_DD_WORD, DxBallPaletteEntry *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL initialize(DxBallDDraw *, DX_DD_WORD, DxBallPaletteEntry *) = 0;
    virtual DX_DD_RESULT DXBALL_DDCALL set_entries(DX_DD_WORD, DX_DD_WORD, DX_DD_WORD, DxBallPaletteEntry *) = 0;
};
#else
struct DxBallDDPalette { const DxBallDDPaletteVTable *vtable; };
#endif

typedef struct DxBallSprite {
    DxBallDDSurface *surface;
    DxBallInt opaque;
    DxBallInt width, height, pitch;
    DxBallRect source_rect;
    signed char code;
    DxBallInt baseline;
} DxBallSprite;

typedef struct DxBallSpriteBank {
    DxBallSprite *sprites[255];
    DxBallInt count, allocation_mode;
    char filename[20];
} DxBallSpriteBank;

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallSpriteBank dxball_sprite_banks[3];
extern DxBallInt dxball_sprite_bank, dxball_font_bank;
extern DxBallDDraw *dxball_direct_draw;
extern DxBallDDPalette *dxball_direct_palette;
extern DxBallPaletteEntry dxball_live_palette[256], dxball_saved_palette[256];

/* Valid bank indices are 0..2; drawing/capture slots are caller-owned 1..254.
   Single-sprite release also accepts slot zero, as required by bank release. */
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
DxBallInt dxball_find_glyph(signed char code);
DxBallInt dxball_draw_glyph(signed char code, DxBallInt x, DxBallInt baseline);
void dxball_load_live_palette(const char *path);
void dxball_load_saved_palette(const char *path);
/* Read the live RGB tail, create a palette and attach it after successful creation. */
void dxball_load_surface_palette(DxBallDDSurface *, const char *);
void dxball_load_pcx(DxBallDDSurface *surface, const char *path,
                     DxBallInt palette_mode, DxBallInt x, DxBallInt y);

#ifdef __cplusplus
}
#endif

#undef DX_DD_RESULT
#undef DX_DD_WORD
#undef DX_DD_LONG
#undef DX_DD_REFCOUNT

#endif
