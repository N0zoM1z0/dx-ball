#ifndef DXBALL_GAMEPLAY_H
#define DXBALL_GAMEPLAY_H

#include "boards.h"

#ifdef _WIN32
#define DXBALL_FASTCALL __fastcall
#else
#define DXBALL_FASTCALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The target has three 32-bit payload fields, followed by two pointers. */
typedef struct DxBallExplosionNode {
    DxBallInt kind, x, y;
    struct DxBallExplosionNode *next, *previous;
} DxBallExplosionNode;

typedef struct DxBallExplosionList {
    DxBallExplosionNode *current, *first, *last;
} DxBallExplosionList;

/* Explicit boundaries, not implementations of the missing game backends. */
typedef struct DxBallGameplayOps {
    void *(*allocate_node)(size_t size);
    void (*brick_effect)(DxBallInt x, DxBallInt y, DxBallByte tile, DxBallInt mode);
    void (*stop_sound)(DxBallInt sound);
    void (*play_sound)(DxBallInt sound, DxBallInt repeat, DxBallInt pan, DxBallInt volume);
    DxBallInt (*random_range)(DxBallInt limit);
    void (*particle)(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy,
                     DxBallInt color, DxBallInt mode);
} DxBallGameplayOps;

extern DxBallInt dxball_remaining_bricks;
extern DxBallInt dxball_destroy_hard_tiles;
extern DxBallInt dxball_reduced_particles;
extern DxBallInt dxball_explosion_pending;
extern DxBallInt dxball_score;
extern double dxball_pan_scale;
extern DxBallExplosionList dxball_explosions;
extern DxBallGameplayOps dxball_gameplay_ops;

/* Host bridge for the target allocation entry at 0x416770. CRT new-handler
   behavior is outside this owner's acceptance scope. */
void *dxball_allocate_node(size_t size);
DxBallInt DXBALL_FASTCALL dxball_append_explosion(DxBallExplosionList *list);
DxBallInt dxball_screen_pan(DxBallInt x);
/* x/y precondition: 0..19. Full return is an int, not just AL. */
DxBallInt dxball_hit_board_tile(DxBallInt x, DxBallInt y);
void dxball_scan_explosive_tiles(void);
DxBallInt DXBALL_FASTCALL dxball_begin_explosions(DxBallExplosionList *list);
DxBallInt DXBALL_FASTCALL dxball_advance_explosion(DxBallExplosionList *list);
DxBallInt DXBALL_FASTCALL dxball_remove_explosion(DxBallExplosionList *list);
void dxball_queue_explosion_at(DxBallInt x, DxBallInt y);

#ifdef __cplusplus
}
#endif
#endif
