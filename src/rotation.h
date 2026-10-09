#ifndef DXBALL_ROTATION_H
#define DXBALL_ROTATION_H
#include "resources.h"

/* Centers are unsigned. Backing must be valid and locks eventually succeed.
   Sprite dimensions are captured before callbacks; surfaces are reacquired.
   The signed width-offset conversions and absolute values must fit i32. */
void dxball_render_rotated_sprite(DxBallUInt center_x, DxBallUInt center_y,
                                  DxBallInt slot, DxBallInt angle);
void dxball_draw_rotated_sprite(DxBallInt slot, DxBallUInt center_x,
                                DxBallUInt center_y, DxBallInt angle);
DxBallInt dxball_rotated_sprite_offset(DxBallInt slot, DxBallInt angle);

DxBallInt dxball_rotated_sprite_y_offset(DxBallInt slot, DxBallInt angle);
DxBallInt dxball_rotated_sprite_width(DxBallInt slot, DxBallInt angle);
DxBallInt dxball_rotated_sprite_height(DxBallInt slot, DxBallInt angle);
#endif
