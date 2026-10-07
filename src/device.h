#ifndef DXBALL_DEVICE_H
#define DXBALL_DEVICE_H

#include "display.h"

/* Fixed layout of the original 100-byte DDBLTFX used for color fills.
   Only size and fill_color are specified by this caller. */
typedef struct DxBallColorFillFx {
    DxBallUInt size, reserved[19], fill_color, tail[4];
} DxBallColorFillFx;

void dxball_palette_transition(DxBallInt frames, DxBallInt step,
                               DxBallInt first, DxBallInt last, DxBallInt direction);
void dxball_initialize_palette(void);
void dxball_clear_surface(DxBallSurface surface, DxBallInt color);
void dxball_restore_sprite_banks(void);
void dxball_recover_surfaces(void);
void dxball_synchronize_surface(void);

#endif
