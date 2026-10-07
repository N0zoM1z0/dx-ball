#ifndef DXBALL_PADDLE_H
#define DXBALL_PADDLE_H

#include "resources.h"

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallInt dxball_paddle_x, dxball_paddle_y, dxball_paddle_width;
extern DxBallInt dxball_paddle_sprite;
extern DxBallInt dxball_paddle_previous_x, dxball_paddle_previous_y;
extern DxBallInt dxball_mouse_x, dxball_mouse_y;
extern DxBallInt dxball_cursor_warp_disabled;
/* Controlled Win32 SetCursorPos import; configured by the platform backend. */
extern DxBallInt (DXBALL_DDCALL *dxball_set_cursor_position)(DxBallInt x, DxBallInt y);
void dxball_update_paddle_position(void);

#ifdef __cplusplus
}
#endif
#endif
