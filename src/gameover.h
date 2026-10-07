#ifndef DXBALL_GAMEOVER_H
#define DXBALL_GAMEOVER_H
#include "boards.h"

extern char dxball_score_name[40];
extern DxBallInt dxball_score_name_length, dxball_selected_score_index;
extern DxBallUInt dxball_score_blink_tick;
extern DxBallInt dxball_score_cursor_visible, dxball_show_high_scores;
extern DxBallInt dxball_entering_score_name;

void dxball_initialize_game_over(void);
void dxball_redraw_game_over(void);
void dxball_game_over_frame(void);
void dxball_game_over_key(char key);
void dxball_dispose_game_over(DxBallInt fade);
void dxball_draw_high_scores(void);
DxBallInt dxball_insert_high_score(const char *name, DxBallUInt score);
void dxball_edit_score_name(char key);
#endif
