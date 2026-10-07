#include "paddle.h"

DxBallInt dxball_paddle_x, dxball_paddle_y, dxball_paddle_width;
DxBallInt dxball_paddle_sprite;
DxBallInt dxball_paddle_previous_x, dxball_paddle_previous_y;
DxBallInt dxball_mouse_x, dxball_mouse_y;
DxBallInt dxball_cursor_warp_disabled;
DxBallInt (DXBALL_DDCALL *dxball_set_cursor_position)(DxBallInt, DxBallInt);

void dxball_update_paddle_position(void)
{
    dxball_paddle_x = dxball_mouse_x;
    dxball_paddle_y = 450;
    if (dxball_paddle_x < dxball_paddle_width / 2 + 21) {
        dxball_paddle_x = dxball_paddle_width / 2 + 21;
    }
    if (618 - dxball_paddle_width / 2 < dxball_paddle_x) {
        dxball_paddle_x = 618 - dxball_paddle_width / 2;
    }
    if (dxball_cursor_warp_disabled == 0 && dxball_paddle_x != dxball_mouse_x) {
        dxball_set_cursor_position(dxball_paddle_x, dxball_mouse_y);
        dxball_mouse_x = dxball_paddle_x;
    }
    dxball_paddle_sprite = 68;
    return;
}
