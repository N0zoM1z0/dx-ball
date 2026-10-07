#ifndef DXBALL_BALLS_H
#define DXBALL_BALLS_H
#include "gameplay.h"

typedef struct DxBallBallNode {
    DxBallInt x, y, previous_x, previous_y, dx, dy, sprite, angle, speed;
    DxBallInt bounce_count, attached, attach_offset, wall_bounces;
    struct DxBallBallNode *next, *previous;
} DxBallBallNode;
typedef struct DxBallBallList {
    DxBallBallNode *current, *first, *last;
} DxBallBallList;

extern DxBallBallList dxball_balls, dxball_duplicate_balls;
extern DxBallInt dxball_ball_count;
DxBallInt DXBALL_FASTCALL dxball_append_ball(DxBallBallList *list);
DxBallInt DXBALL_FASTCALL dxball_begin_balls(DxBallBallList *list);
DxBallInt DXBALL_FASTCALL dxball_advance_ball(DxBallBallList *list);
DxBallInt DXBALL_FASTCALL dxball_remove_ball(DxBallBallList *list);
DxBallInt DXBALL_FASTCALL dxball_clear_ball_list(DxBallBallList *list);
void dxball_spawn_ball(void);
void dxball_clone_balls(void);
void dxball_bounce_ball_from_paddle(void);
void dxball_release_attached_balls(void);
#endif
