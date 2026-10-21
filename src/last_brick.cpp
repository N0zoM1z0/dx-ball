#include "state_types.h"
extern "C" {
DxBallInt dxball_random_range(DxBallInt limit);
#if defined(_WIN32)
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);
#else
DxBallUInt timeGetTime(void);
#endif
}

extern "C" {
#include "clock_api.h"
#include "display.h"
#include "device.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "particles.h"
#include "sound.h"
#include "startup.h"
}

#include <stdlib.h>
#include <string.h>
#include "runtime_absolute.h"

/* FUNCTION: DXBALL 0x00415F40 */
void dxball_last_brick(void)
{
    DxBallInt remaining;
    if (dxball_last_brick_deadline == 0) {
        dxball_last_brick_deadline = (DxBallInt)((DxBallUInt)timeGetTime() + (DxBallUInt)dxball_random_range(20000) + 40000u);
    }
    remaining = (DxBallInt)((DxBallUInt)dxball_last_brick_deadline - timeGetTime());
    if (remaining < 1) {
        DxBallInt tile_y;
        DxBallInt brick_x;
        DxBallRect rect;
        DxBallInt brick_center_x;
        DxBallInt draw_x;
        DxBallInt scanColumn;
        DxBallInt y;
        DxBallInt brick;
        DxBallInt tile_center_y;
        DxBallInt scanRow;
        dxball_stop_sound(21);
        dxball_play_sound(22, 0, 0, 0);
        for (scanColumn = 0; scanColumn < DXBALL_BOARD_WIDTH; ++scanColumn) {
            for (scanRow = 0; scanRow < DXBALL_BOARD_HEIGHT; ++scanRow) {
                brick = (signed char)dxball_board_tiles[scanColumn + scanRow * DXBALL_BOARD_WIDTH];
                if (brick != 0 && brick != 2) {
                    brick_x = scanColumn;
                    tile_y = scanRow;
                    brick_center_x = brick_x * 30 + 35;
                    tile_center_y = tile_y * 15 + 57;
                }
            }
        }
        dxball_queue_explosion_at(brick_x, tile_y);
        dxball_spawn_fire_effect(brick_center_x, tile_center_y);
        if (dxball_reduced_particles != 0) {
            DxBallInt i;
            for (i = 0; i < 15; ++i) {
                dxball_spawn_particle(brick_center_x - 15 + dxball_random_range(30),
                    tile_center_y - 7 + dxball_random_range(15),
                    6 - dxball_random_range(14), 4 - dxball_random_range(11), 16, 1);
            }
        } else {
            DxBallInt i;
            for (i = 0; i < 30; ++i) {
                dxball_spawn_particle(brick_center_x - 15 + dxball_random_range(30),
                    tile_center_y - 7 + dxball_random_range(15),
                    6 - dxball_random_range(14), 4 - dxball_random_range(11), 16, 1);
            }
        }
        dxball_select_sprite_bank(2);
        draw_x = brick_center_x - dxball_sprite_banks[dxball_sprite_bank].sprites[1]->width / 2;
        y = (DxBallInt)((DxBallUInt)tile_center_y
                      - (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[1]->height);
        rect.left = 0;
        rect.top = 0;
        rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[1]->width;
        rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[1]->height;
        if (draw_x < 0) { rect.left = dxball_crt_absolute(draw_x); draw_x = 0; }
        if (dxball_sprite_banks[dxball_sprite_bank].sprites[1]->width + draw_x > 639)
            rect.right -= dxball_sprite_banks[dxball_sprite_bank].sprites[1]->width + draw_x - 639;
        if (y < 0) { rect.top = dxball_crt_absolute(y); y = 0; }
        if (dxball_sprite_banks[dxball_sprite_bank].sprites[1]->height + y > 479)
            rect.bottom -= dxball_sprite_banks[dxball_sprite_bank].sprites[1]->height + y - 479;
        dxball_lightning_x = draw_x;
        dxball_lightning_y = y;
        dxball_lightning_rect.top = rect.top;
        dxball_lightning_rect.bottom = rect.bottom;
        dxball_lightning_rect.left = rect.left;
        dxball_lightning_rect.right = rect.right;
        dxball_lightning_frames = 4;
        dxball_last_brick_deadline = 0;
        dxball_select_sprite_bank(0);
    } else {
        dxball_update_sound(21, 0, 0, -((remaining / 2 > 3 ? remaining / 2 : 3) / 3));
    }
    return;
}
