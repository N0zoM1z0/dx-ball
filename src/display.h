#ifndef DXBALL_DISPLAY_H
#define DXBALL_DISPLAY_H

#include "runtime.h"

#define DXBALL_DIRTY_CAPACITY 1000
#define DXBALL_PRESENT_CAPACITY 2000

/* Two interleaved rectangle pages, with separate counts. */
extern DxBallRect dxball_dirty_regions[DXBALL_DIRTY_CAPACITY][2];
extern DxBallInt dxball_dirty_counts[2], dxball_dirty_page;
extern DxBallRect dxball_present_regions[DXBALL_PRESENT_CAPACITY];
extern DxBallInt dxball_present_keys[DXBALL_PRESENT_CAPACITY], dxball_present_count;
extern DxBallInt dxball_clip_regions, dxball_wait_vertical_blank;
extern DxBallUInt dxball_frame_wait_tick;
extern DxBallSurface dxball_restore_surface;
extern DxBallRect dxball_lightning_rect;

typedef struct DxBallDisplayOps {
    void (*update_sound)(DxBallInt slot, DxBallInt frequency, DxBallInt pan, DxBallInt volume);
    void (*recover_surfaces)(void);
} DxBallDisplayOps;
extern DxBallDisplayOps dxball_display_ops;

void dxball_reset_regions(void);
void dxball_queue_region(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom);
void dxball_invalidate_region(DxBallRect rect);
void dxball_restore_effect_region(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom);
void dxball_bind_board_surface(DxBallSurface surface);
void dxball_bind_display_surface(DxBallSurface surface);
void dxball_draw_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_draw_reduced_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
void dxball_blt_effect_sprite(DxBallInt, DxBallInt, DxBallInt);
void dxball_blt_reduced_sprite(DxBallInt, DxBallInt, DxBallInt);
void dxball_stretch_effect_sprite(DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt);
void dxball_queue_sprite_region(DxBallInt, DxBallInt, DxBallInt);
void dxball_restore_regions(void);
void dxball_sort_present_regions(DxBallInt first, DxBallInt last);
void dxball_present_regions_now(void);
void dxball_present(void);
void dxball_wait_frames(DxBallInt frames);
void dxball_animate_palette(DxBallInt first, DxBallInt last, DxBallInt rotate);
void dxball_last_brick(void);
void dxball_draw_last_brick(void);

/* Portable rendering bridge; no independent original-entry claim. */
void dxball_restore_board_region(DxBallSurface destination, DxBallInt x, DxBallInt y,
                                DxBallSurface source, const DxBallRect *rect, DxBallUInt flags);

#endif
