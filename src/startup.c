#include "startup.h"
#include "platform.h"
#include "round.h"
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32)
#include <io.h>
#else
#include <unistd.h>
#endif

DxBallScoreRecord dxball_scores[15];
char dxball_board_filename[12] = "default.bds";
DxBallStartupFileOps dxball_startup_file_ops = {fopen, fread, fwrite, fclose, access};
DxBallRandomOps dxball_random_ops = {srand, rand};
void (*dxball_startup_load_boards)(const char *path) = dxball_read_board_bank;

static const char *const default_score_names[15] = {
    " **** DX-BALL by Michael P. Welch ****",
    " Dedicated to those who love the Amiga",
    " and its most popular shareware",
    " game... MegaBall. The Mackey brothers",
    " did a great thing with the breakout",
    " concept. So wonderful in fact, that",
    " my wife enjoyed MegaBall 3 way more",
    " than my game `Scorched Tanks.'",
    " I've finally written a game that",
    " holds her interest.  :)",
    " *****--------------------------*****",
    " \\\\\\This is a 100% Direct X game.///",
    "           ///Hope you like it!\\\\\\",
    " *****--------------------------*****",
    " *****--------------------------*****",
};

void dxball_initialize_scores(void)
{
    DxBallInt i;
    for (i = 0; i < 15; ++i) {
        strcpy(dxball_scores[i].name, default_score_names[i]);
        dxball_scores[i].score = 150 - i * 10;
    }
    if (dxball_startup_file_ops.access("score.dat", 0) == -1) {
        dxball_board_file = dxball_startup_file_ops.open("score.dat", "wb");
        if (dxball_board_file != NULL) {
            dxball_startup_file_ops.write(dxball_scores, 44, 15, dxball_board_file);
            dxball_startup_file_ops.close(dxball_board_file);
        }
    }
}

void dxball_read_scores(void)
{
    dxball_board_file = dxball_startup_file_ops.open("score.dat", "rb");
    if (dxball_board_file != NULL) {
        dxball_startup_file_ops.read(dxball_scores, 44, 15, dxball_board_file);
        dxball_startup_file_ops.close(dxball_board_file);
    }
}

void dxball_seed_random(void)
{
    dxball_random_ops.seed(dxball_clock_ops.time_ms() % 300);
}

DxBallInt dxball_random_range(DxBallInt limit)
{
    return dxball_random_ops.next() % limit;
}

void dxball_release_sprite_banks(void)
{
    DxBallInt bank, slot;
    for (bank = 0; bank < 3; ++bank) {
        dxball_sprite_banks[bank].count = 0;
        slot = 0;
        dxball_select_sprite_bank(bank);
        while (slot <= 254) {
            dxball_release_sprite(slot);
            ++slot;
        }
    }
    return;
}

void dxball_initialize_device_state(void)
{
    DxBallUInt start;
    DxBallInt result;
    DxBallSurfaceDesc desc;
    DxBallInt i;

    desc.size = 108;
    desc.flags = 7;
    desc.caps = 0x840;
    desc.height = 480;
    desc.width = 640;
    result = dxball_direct_draw->vtable->create_surface(dxball_direct_draw,
        &desc, &dxball_background_surface, NULL);
    if (result != 0) {
        dxball_process_exit(1);
    } else {
        dxball_end_requested = 0;
        dxball_display_mode = 4;
        dxball_return_to_menu = 4;
        dxball_initialize_scores();
        dxball_read_scores();
        dxball_read_board_bank(dxball_board_filename);
        dxball_seed_random();
        dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
        dxball_initialize_palette();
        start = dxball_current_time();
        for (i = 0; i <= 31; ++i)
            dxball_direct_draw->vtable->wait_vertical_blank(dxball_direct_draw, 1, NULL);
        if (dxball_current_time() - start > 400) {
            dxball_wait_vertical_blank = 1;
        } else {
            dxball_wait_vertical_blank = 0;
        }
        if (dxball_reduced_particles == 1)
            dxball_wait_vertical_blank = 0;
        if (dxball_software_only == 0 && dxball_wait_vertical_blank == 0)
            dxball_reduced_particles = 1;
        dxball_frame_wait_tick = dxball_current_time();
    }
    return;
}
