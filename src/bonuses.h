#ifndef DXBALL_BONUSES_H
#define DXBALL_BONUSES_H

#include "gameplay.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DxBallBonusNode {
    DxBallInt kind, sprite, x, y, dx, dy, gravity_ticks;
    struct DxBallBonusNode *next, *previous;
} DxBallBonusNode;

typedef struct DxBallBonusList {
    DxBallBonusNode *current, *first, *last;
} DxBallBonusList;

extern DxBallBonusList dxball_bonuses;
extern DxBallInt dxball_bonus_count;
/* Kind-number names remain explicit until their gameplay consumers are recovered. */
extern DxBallInt dxball_bonus_3_active, dxball_bonus_3_ticks;
extern DxBallInt dxball_bonus_7_active, dxball_bonus_8_active, dxball_bonus_9_active;
extern DxBallInt dxball_bonus_12_active, dxball_bonus_14_active;
extern DxBallInt dxball_bonus_17_active, dxball_bonus_18_active;

DxBallInt DXBALL_FASTCALL dxball_append_bonus(DxBallBonusList *list);
DxBallInt DXBALL_FASTCALL dxball_begin_bonuses(DxBallBonusList *list);
DxBallInt DXBALL_FASTCALL dxball_advance_bonus(DxBallBonusList *list);
DxBallInt DXBALL_FASTCALL dxball_remove_bonus(DxBallBonusList *list);
/* Tile x/y in 0..19; controlled RNG returns values in 0..limit-1. */
void dxball_generate_bonus(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy);
/* Original decrements count even if the current node is absent. */
void dxball_retire_bonus(void);
void dxball_draw_bonuses(void);
void dxball_update_bonuses(void);

#ifdef __cplusplus
}
#endif

#endif
