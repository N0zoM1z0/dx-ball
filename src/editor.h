#ifndef DXBALL_EDITOR_H
#define DXBALL_EDITOR_H
#include "boards.h"

enum { DXBALL_HIT_REGION_CAPACITY = 100 };
typedef struct DxBallHitRegion {
    DxBallInt left, top, right, bottom, active;
} DxBallHitRegion;
extern DxBallHitRegion dxball_hit_regions[DXBALL_HIT_REGION_CAPACITY];
extern DxBallInt dxball_hit_region_count, dxball_editor_selected_tile;

/* Initialization clears through count+1 inclusive; valid storage needs
   -2 <= count <= 98. Set-region indices require 0..99. Lookup count <= 100. */
void dxball_initialize_hit_regions(DxBallInt count);
void dxball_set_hit_region(DxBallInt index, DxBallInt left, DxBallInt top,
                          DxBallInt right, DxBallInt bottom);
/* Single-region helpers require an index in 0..99. Resetting the count
   leaves every region record unchanged. */
void dxball_clear_hit_region(DxBallInt index);
DxBallInt dxball_hit_region_contains(DxBallInt index, DxBallInt x, DxBallInt y);
void dxball_reset_hit_region_count(void);
DxBallInt dxball_find_hit_region(DxBallInt x, DxBallInt y);
void dxball_initialize_editor(void);
void dxball_redraw_editor(void);
void dxball_editor_frame(void);
void dxball_editor_key(char key);
void dxball_dispose_editor(DxBallInt fade);
void dxball_draw_editor_choices(void);
void dxball_draw_editor_status(void);
/* Zero-argument interface for the observed no-effect operation.
   The original prototype and ownership remain unknown. */
void dxball_unclassified_noop_40cc20(void);
#endif
