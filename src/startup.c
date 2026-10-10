#include "startup.h"
#include "platform.h"
#include "round.h"
#include "clock_api.h"
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

void dxball_initialize_scores(void)
{
    dxball_scores[0].name[0] = 0;
    strcat(dxball_scores[0].name, " **** DX-BALL by Michael P. Welch ****");
    dxball_scores[0].score = 150;
    dxball_scores[1].name[0] = 0;
    strcat(dxball_scores[1].name, " Dedicated to those who love the Amiga");
    dxball_scores[1].score = 140;
    dxball_scores[2].name[0] = 0;
    strcat(dxball_scores[2].name, " and its most popular shareware");
    dxball_scores[2].score = 130;
    dxball_scores[3].name[0] = 0;
    strcat(dxball_scores[3].name, " game... MegaBall. The Mackey brothers");
    dxball_scores[3].score = 120;
    dxball_scores[4].name[0] = 0;
    strcat(dxball_scores[4].name, " did a great thing with the breakout");
    dxball_scores[4].score = 110;
    dxball_scores[5].name[0] = 0;
    strcat(dxball_scores[5].name, " concept. So wonderful in fact, that");
    dxball_scores[5].score = 100;
    dxball_scores[6].name[0] = 0;
    strcat(dxball_scores[6].name, " my wife enjoyed MegaBall 3 way more");
    dxball_scores[6].score = 90;
    dxball_scores[7].name[0] = 0;
    strcat(dxball_scores[7].name, " than my game `Scorched Tanks.'");
    dxball_scores[7].score = 80;
    dxball_scores[8].name[0] = 0;
    strcat(dxball_scores[8].name, " I've finally written a game that");
    dxball_scores[8].score = 70;
    dxball_scores[9].name[0] = 0;
    strcat(dxball_scores[9].name, " holds her interest.  :)");
    dxball_scores[9].score = 60;
    dxball_scores[10].name[0] = 0;
    strcat(dxball_scores[10].name, " *****--------------------------*****");
    dxball_scores[10].score = 50;
    dxball_scores[11].name[0] = 0;
    strcat(dxball_scores[11].name, " \\\\\\This is a 100% Direct X game.///");
    dxball_scores[11].score = 40;
    dxball_scores[12].name[0] = 0;
    strcat(dxball_scores[12].name, "           ///Hope you like it!\\\\\\");
    dxball_scores[12].score = 30;
    dxball_scores[13].name[0] = 0;
    strcat(dxball_scores[13].name, " *****--------------------------*****");
    dxball_scores[13].score = 20;
    dxball_scores[14].name[0] = 0;
    strcat(dxball_scores[14].name, " *****--------------------------*****");
    dxball_scores[14].score = 10;
    if (access("score.dat", 0) == -1) {
        dxball_board_file = fopen("score.dat", "wb");
        if (dxball_board_file == NULL) return;
        fwrite(dxball_scores, sizeof(dxball_scores[0]), 15, dxball_board_file);
        fclose(dxball_board_file);
    }
    return;
}

void dxball_read_scores(void)
{
    dxball_board_file = fopen("score.dat", "rb");
    if (dxball_board_file == NULL) return;
    fread(dxball_scores, sizeof(dxball_scores[0]), 15, dxball_board_file);
    fclose(dxball_board_file);
    return;
}

void dxball_seed_random(void)
{
    DxBallUInt seed;
    seed = dxball_time_get_time() % 300;
    srand(seed);
    return;
}

DxBallInt dxball_random_range(DxBallInt limit)
{
    limit = rand() % limit;
    return limit;
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
