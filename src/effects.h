#ifndef DXBALL_EFFECTS_H
#define DXBALL_EFFECTS_H

#include "gameplay.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DxBallBrickEffectNode {
    DxBallInt kind, sprite, x, y;
    DxBallByte tile;
    DxBallInt frames, period, ticks;
    struct DxBallBrickEffectNode *next, *previous;
} DxBallBrickEffectNode;

typedef struct DxBallBrickEffectList {
    DxBallBrickEffectNode *current, *first, *last;
} DxBallBrickEffectList;

typedef struct DxBallEffectOps {
    void (*deallocate_node)(void *node);
    void (*bonus)(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy);
    void (*keyed_sprite)(DxBallInt sprite, DxBallInt x, DxBallInt y);
    void (*reduced_sprite)(DxBallInt sprite, DxBallInt x, DxBallInt y);
    void (*region)(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom);
} DxBallEffectOps;

extern DxBallBrickEffectList dxball_brick_effects;
extern DxBallInt dxball_hit_dx, dxball_hit_dy;
extern DxBallSurface dxball_effect_surface;
extern DxBallEffectOps dxball_effect_ops;

/* Boundary to runtime deletion entry 0x416760, not a CRT reconstruction. */
void dxball_deallocate_node(void *node);
DxBallInt DXBALL_FASTCALL dxball_begin_brick_effects(DxBallBrickEffectList *list);
DxBallInt DXBALL_FASTCALL dxball_advance_brick_effect(DxBallBrickEffectList *list);
DxBallInt DXBALL_FASTCALL dxball_append_brick_effect(DxBallBrickEffectList *list);
DxBallInt DXBALL_FASTCALL dxball_remove_brick_effect(DxBallBrickEffectList *list);
DxBallInt DXBALL_FASTCALL dxball_clear_brick_effect_list(DxBallBrickEffectList *list);
/* Coordinates are tile coordinates (0..19). Kind 1 stores screen coordinates;
   kind 2 stores tile coordinates in the same x/y fields. */
void dxball_spawn_explosion_effect(DxBallInt x, DxBallInt y);
void dxball_spawn_brick_effect(DxBallInt x, DxBallInt y, DxBallByte tile, DxBallInt mode);
/* Step functions require a valid current node of their respective kind. */
void dxball_step_explosion_effect(void);
void dxball_step_brick_effect(void);
void dxball_process_brick_effects(void);
/* Extracted explosion phase of 0x40F8B0; not a reconstructed whole frame. */
void dxball_apply_explosion_requests(void);

#ifdef __cplusplus
}
#endif
#endif
