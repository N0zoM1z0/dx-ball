#include "core.h"
extern "C" {
#include "bonuses.h"
#include "effects.h"
#include "paddle.h"
#include "startup.h"
void dxball_queue_region(DxBallRect rect);
void dxball_draw_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y);
DxBallUInt dxball_current_time(void);
DxBallInt dxball_elapsed(DxBallUInt start, DxBallUInt interval);
#if defined(_WIN32)
__declspec(dllimport) unsigned long DXBALL_DDCALL timeGetTime(void);
#else
DxBallUInt DXBALL_DDCALL timeGetTime(void);
#endif
extern DxBallInt dxball_paddle_frame, dxball_paddle_overlay_sprite, dxball_paddle_overlay_width;
extern DxBallUInt dxball_paddle_tick, dxball_paddle_overlay_deadline;
}

extern "C" void dxball_draw_paddle(void)
{
    DxBallInt factor;
    {
        DxBallInt base_width;
        base_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
        factor = dxball_paddle_width / base_width;
    }
    {
        DxBallInt sprite, offset_y;
        offset_y = 0;
        sprite = factor * 4 + dxball_paddle_frame;
        if (dxball_elapsed(dxball_paddle_tick, 64)) {
            ++dxball_paddle_frame;
            if (dxball_paddle_frame > 3) dxball_paddle_frame = 0;
            dxball_paddle_tick = dxball_current_time();
        }
        if (dxball_bonus_8_active == 1) {
            sprite += 104; offset_y = 15;
        } else if (dxball_attached_ball_cue == 1) {
            sprite += 84;
            offset_y = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height - 14;
        } else {
            sprite += 64; offset_y = 0;
        }
        if (dxball_attached_ball_cue == 1) {
            DxBallInt margin;
            if (dxball_paddle_overlay_deadline < timeGetTime() ||
                dxball_paddle_overlay_width != dxball_paddle_width) {
                dxball_paddle_overlay_sprite = dxball_random_range(4) + factor * 4 + 124;
                dxball_paddle_overlay_deadline = timeGetTime() + 33;
                dxball_paddle_overlay_width = dxball_paddle_width;
            }
            if (dxball_bonus_8_active == 1)
                margin = (DxBallInt)((long double)dxball_paddle_width * 0.075);
            else
                margin = (DxBallInt)((long double)dxball_paddle_width * 0.03);
            {
                DxBallRect rect, dirty;
                {
                    DxBallInt x, y;
                    x = dxball_paddle_x - dxball_paddle_width / 2 + margin;
                    y = dxball_paddle_y - 14;
                    rect.left = margin; rect.top = 0;
                    rect.right = dxball_paddle_width - margin;
                    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_overlay_sprite]->height;
                    dirty.left = x; dirty.top = rect.top + y;
                    dirty.right = dxball_paddle_width + x; dirty.bottom = rect.bottom + y;
                    ((DxBallDDSurface *)dxball_effect_surface)->blt_fast(x, y,
                        dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_overlay_sprite]->surface,
                        &rect, 0x11);
                    dxball_queue_region(dirty);
                }
            }
        }
        dxball_draw_effect_sprite(sprite, dxball_paddle_x - dxball_paddle_width / 2,
            dxball_paddle_y - offset_y);
    }
    return;
}
