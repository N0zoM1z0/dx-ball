#include "round.h"
#include "paddle.h"

DxBallInt dxball_lives, dxball_life_score_limit;
DxBallInt dxball_restart_requested, dxball_level_changed;
DxBallInt dxball_end_requested, dxball_return_to_menu;
DxBallRoundOps dxball_round_ops = { dxball_initialize_board, dxball_count_destructible_bricks };

void dxball_advance_level(void)
{
    dxball_restart_requested = 1;
    dxball_level_changed = 1;
    ++dxball_board_index;
    if (dxball_board_index > 49) {
        dxball_end_requested = 1;
        dxball_return_to_menu = 0;
    }
    dxball_round_ops.initialize_board();
    if (dxball_round_ops.count_bricks() < 1) {
        dxball_lives = 0;
        dxball_end_requested = 1;
        dxball_return_to_menu = 0;
    }
    return;
}

void dxball_lose_life(void)
{
    --dxball_lives;
    dxball_life_score_limit = 999999999;
    dxball_gameplay_ops.stop_sound(14);
    dxball_gameplay_ops.play_sound(14, 0, dxball_screen_pan(dxball_paddle_x), 0);
    dxball_restart_requested = 1;
    return;
}
