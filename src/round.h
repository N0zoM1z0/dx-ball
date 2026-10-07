#ifndef DXBALL_ROUND_H
#define DXBALL_ROUND_H

#include "gameplay.h"

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallInt dxball_lives, dxball_life_score_limit;
extern DxBallInt dxball_restart_requested, dxball_level_changed;
extern DxBallInt dxball_end_requested, dxball_return_to_menu;
typedef struct DxBallRoundOps {
    void (*initialize_board)(void);
    DxBallInt (*count_bricks)(void);
} DxBallRoundOps;
extern DxBallRoundOps dxball_round_ops;
/* Default board initialization requires the resulting index in 0..49.
   Terminal/invalid-slot initialization remains a controlled dependency. */
void dxball_advance_level(void);
void dxball_lose_life(void);

#ifdef __cplusplus
}
#endif
#endif
