#ifndef DXBALL_CORE_H
#define DXBALL_CORE_H

#include "balls.h"
#include "resources.h"

typedef struct DxBallProjectileNode {
    DxBallInt x, y, previous_x, previous_y;
    struct DxBallProjectileNode *next, *previous;
} DxBallProjectileNode;
typedef struct DxBallProjectileList {
    DxBallProjectileNode *current, *first, *last;
} DxBallProjectileList;
typedef struct DxBallFireEffectNode {
    DxBallInt x, y, ticks;
    struct DxBallFireEffectNode *next, *previous;
} DxBallFireEffectNode;
typedef struct DxBallFireEffectList {
    DxBallFireEffectNode *current, *first, *last;
} DxBallFireEffectList;

/* Every frame phase defaults to maintained owners. Their platform/COM, clock,
   sound and resource dependencies still require a configured backend. */
typedef struct DxBallFrameOps {
    DxBallUInt (*current_time)(void);
    DxBallInt (*elapsed)(DxBallUInt start, DxBallUInt interval);
    void (*animate_palette)(DxBallInt first, DxBallInt last, DxBallInt step);
    void (*update_score)(void);
    void (*wait_frames)(DxBallInt mode);
    void (*restore_regions)(void);
    void (*draw_effect_sprite)(DxBallInt sprite, DxBallInt x, DxBallInt y);
    void (*draw_paddle)(void);
    void (*last_brick)(void);
    void (*draw_last_brick)(void);
    void (*present)(void);
    void (*restart_round)(void);
} DxBallFrameOps;

extern DxBallProjectileList dxball_projectiles;
extern DxBallFireEffectList dxball_fire_effects;
extern DxBallInt dxball_projectile_count;
extern DxBallInt dxball_launch_requested, dxball_attached_ball_cue;
extern DxBallInt dxball_paused, dxball_draw_to_primary, dxball_mouse_action;
extern DxBallInt dxball_last_brick_deadline;
extern DxBallUInt dxball_palette_tick;
extern DxBallFrameOps dxball_frame_ops;

/* Valid sprite metadata, finite non-overflowing integer state, and live list
   cursors are required. Point hits clamp X; their Y window is strictly 49..350. */
DxBallInt dxball_hit_screen_point(DxBallInt x, DxBallInt y);
void dxball_retire_ball(void);
void dxball_drop_bricks(void);
void dxball_spawn_fire_effect(DxBallInt x, DxBallInt y);
void dxball_process_fire_effects(void);
void dxball_update_projectiles(void);
void dxball_fire_projectiles(void);
void dxball_update_balls(void);
void dxball_game_frame(void);
/* Typed lifecycle helpers; no independent target-entry acceptance claims. */
void dxball_clear_projectiles(void);
void dxball_clear_fire_effects(void);

#endif
