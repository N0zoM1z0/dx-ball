#ifndef DXBALL_INTRO_H
#define DXBALL_INTRO_H
#include "boards.h"

typedef struct DxBallIntroPoint { DxBallInt x, y, angle, kind; } DxBallIntroPoint;
typedef struct DxBallIntroOffset { DxBallInt x, y; } DxBallIntroOffset;
extern DxBallIntroPoint dxball_intro_points[287];
extern DxBallIntroOffset dxball_intro_offsets[360];
extern DxBallUInt dxball_intro_tick;
extern DxBallInt dxball_intro_cursor_x, dxball_intro_cursor_y;
extern DxBallInt dxball_scroller_length, dxball_scroller_shift, dxball_scroller_index;
extern DxBallInt dxball_scroller_reserved, dxball_scroller_advance;
extern DxBallInt dxball_credit_angle, dxball_credit_first_y, dxball_credit_second_y;
extern DxBallInt dxball_splash_span, dxball_splash_phase, dxball_splash_offset;
extern DxBallInt dxball_splash_colors[66];
extern const char dxball_welcome_text[];
DxBallInt dxball_raw_sine(DxBallInt angle);
DxBallInt dxball_raw_cosine(DxBallInt angle);
DxBallInt dxball_wave_x(DxBallInt origin, DxBallInt angle, DxBallInt amplitude);
DxBallInt dxball_wave_y(DxBallInt origin, DxBallInt angle, DxBallInt amplitude);
void dxball_initialize_intro_points(void);
void dxball_update_intro_points(void);
void dxball_initialize_intro(void);
void dxball_redraw_intro(void);
void dxball_intro_frame(void);
void dxball_intro_key(char key);
void dxball_dispose_intro(DxBallInt fade);
void dxball_initialize_splash(void);
void dxball_redraw_splash(void);
void dxball_splash_frame(void);
void dxball_splash_key(char key);
void dxball_dispose_splash(DxBallInt fade);
void dxball_draw_scroller_wave(void);
void dxball_update_scroller(void);
void dxball_draw_waving_credits(void);
void dxball_pulse_splash_palette(void);
#endif
