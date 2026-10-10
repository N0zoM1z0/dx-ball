#include "gameover.h"
#include "startup.h"
#include "platform.h"
#include "intro.h"
#include "paddle.h"
#include "round.h"
#include "ui.h"
#include "midi.h"
#include "sound.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32)
#include <io.h>
#else
#include <unistd.h>
#endif

char dxball_score_name[40];
DxBallInt dxball_score_name_length, dxball_selected_score_index;
DxBallUInt dxball_score_blink_tick;
DxBallInt dxball_score_cursor_visible, dxball_show_high_scores;
DxBallInt dxball_entering_score_name;

DxBallInt dxball_insert_high_score(const char *name, DxBallUInt score)
{
    DxBallInt rank, i;
    dxball_read_scores();
    if (score < dxball_scores[14].score) return -1;
    rank = 14;
    while (rank >= 0 && dxball_scores[rank].score <= score) {
        --rank;
    }
    ++rank;
    if (rank == 14) {
        strcpy(dxball_scores[rank].name, name);
        dxball_scores[rank].score = score;
    } else {
        i = 13;
        while (i >= rank) {
            strcpy(dxball_scores[i + 1].name, dxball_scores[i].name);
            dxball_scores[i + 1].score = dxball_scores[i].score;
            --i;
        }
        strcpy(dxball_scores[rank].name, name);
        dxball_scores[rank].score = score;
    }
    if (access("score.dat", 2) == 0) {
        dxball_board_file = fopen("score.dat", "wb");
        if (dxball_board_file == NULL) return rank;
        fwrite(dxball_scores, sizeof(dxball_scores[0]), 15, dxball_board_file);
        fclose(dxball_board_file);
    }
    return rank;
}

void dxball_draw_high_scores(void)
{
    DxBallInt y, i, x = 10;
    char value[20];
    DxBallInt count;
    y = 170;
    for (i = 0; i <= 14; ++i) {
        if (i == dxball_selected_score_index) {
            dxball_draw_line(dxball_active_surface, 5, y - 14, 635, y - 14, 200);
            dxball_draw_line(dxball_active_surface, 5, y + 5, 635, y + 5, 200);
            dxball_draw_line(dxball_active_surface, 5, y - 14, 5, y + 4, 200);
            dxball_draw_line(dxball_active_surface, 635, y - 14, 635, y + 4, 200);
        }
        count = (DxBallInt)strlen(dxball_scores[i].name);
        dxball_draw_text(x, y, count, dxball_scores[i].name);
        _ultoa((unsigned long)dxball_scores[i].score, value, 10);
        count = (DxBallInt)strlen(value);
        dxball_draw_text(630 - dxball_measure_text(count, value), y, count, value);
        y += 20;
    }
    return;
}

void dxball_initialize_game_over(void)
{
    dxball_reset_regions();
    dxball_clear_surface((DxBallSurface)dxball_background_surface, 0);
    dxball_load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
    dxball_load_sprite_bank(0, 1, "mainmenu.sbk");
    dxball_load_sprite_bank(1, 0, "sysfont.sbk");
    dxball_select_sprite_bank(0); dxball_select_font_bank(1);
    dxball_load_music("acker-gs.mds", 1);
    dxball_bind_board_surface((DxBallSurface)dxball_board_surface);
    if (dxball_draw_to_primary == 0) {
        dxball_bind_display_surface((DxBallSurface)dxball_secondary_surface);
    } else {
        dxball_bind_display_surface((DxBallSurface)dxball_primary_surface);
    }
    dxball_read_scores();
    dxball_score_name[0] = 0;
    dxball_score_name_length = 0; dxball_score_blink_tick = 0;
    dxball_score_cursor_visible = 0; dxball_selected_score_index = -1;
    if (dxball_scores[14].score <= (DxBallUInt)dxball_score) {
        dxball_entering_score_name = 1;
    } else {
        dxball_entering_score_name = 0;
    }
    dxball_show_high_scores = 0;
    dxball_redraw_mode(); dxball_palette_transition(1, 6, 0, 255, 1);
    return;
}

void dxball_redraw_game_over(void)
{
    DxBallRect rect = {0, 0, 640, 480};
    char value[100];
    dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
    if (dxball_draw_to_primary == 0) dxball_clear_surface((DxBallSurface)dxball_secondary_surface, 0);
    dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
    ((DxBallDDSurface *)dxball_board_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_board_surface, &rect,
        (DxBallDDSurface *)dxball_background_surface, &rect, 0x1000000, NULL);
    dxball_select_surface((DxBallSurface)dxball_board_surface);
    if (dxball_show_high_scores == 1) dxball_draw_high_scores();
    else if (dxball_entering_score_name == 1) {
        dxball_draw_centered_text(320, 170, 22, "You have a high score!");
        dxball_draw_text(70, 200, 16, "Enter your name:");
    } else {
        dxball_draw_centered_text(320, 170, 11, "Your score:");
        _ultoa((unsigned long)(DxBallUInt)dxball_score, value, 10);
        dxball_draw_centered_text(320, 200, (DxBallInt)strlen(value), value);
    }
    ((DxBallDDSurface *)dxball_primary_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_primary_surface, &rect,
        (DxBallDDSurface *)dxball_board_surface, &rect, 0x1000000, NULL);
    if (dxball_draw_to_primary == 0) {
        ((DxBallDDSurface *)dxball_secondary_surface)->vtable->blt(
            (DxBallDDSurface *)dxball_secondary_surface, &rect,
            (DxBallDDSurface *)dxball_board_surface, &rect, 0x1000000, NULL);
    }
    return;
}

void dxball_game_over_frame(void)
{
    DxBallRect name_region;
    if (dxball_draw_to_primary != 0) dxball_wait_frames(1);
    dxball_restore_regions();
    dxball_intro_cursor_x = dxball_mouse_x; dxball_intro_cursor_y = dxball_mouse_y;
    if (dxball_intro_cursor_x > 599) dxball_intro_cursor_x = 599;
    if (dxball_intro_cursor_x < 8) dxball_intro_cursor_x = 8;
    if (dxball_intro_cursor_y > 447) dxball_intro_cursor_y = 447;
    if (dxball_entering_score_name == 1) {
        name_region.left = 0;
        name_region.top = 210;
        name_region.right = 639;
        name_region.bottom = 234;
        if (dxball_draw_to_primary == 0) {
            dxball_select_surface((DxBallSurface)dxball_secondary_surface);
        } else {
            dxball_select_surface((DxBallSurface)dxball_primary_surface);
        }
        dxball_draw_text(70, 230, (DxBallInt)strlen(dxball_score_name), dxball_score_name);
        if (dxball_score_cursor_visible == 1)
            dxball_draw_text(dxball_measure_text((DxBallInt)strlen(dxball_score_name), dxball_score_name) + 71, 230, 1, "_");
        if (dxball_elapsed(dxball_score_blink_tick, 300)) {
            dxball_score_cursor_visible = 1 - dxball_score_cursor_visible;
            dxball_score_blink_tick = dxball_current_time();
        }
        dxball_queue_region(name_region);
    }
    if (dxball_draw_to_primary == 0) dxball_present();
    if (dxball_show_high_scores == 1 && dxball_entering_score_name == 0) {
        if (dxball_elapsed(dxball_score_blink_tick, 100)) {
            dxball_score_blink_tick = dxball_current_time();
            dxball_animate_palette(200, 207, 1);
        }
    }
    if (dxball_mouse_action == 1) {
        if (dxball_entering_score_name != 0) {
            dxball_wait_frames(1);
        } else {
            if (dxball_show_high_scores == 0) {
                dxball_palette_transition(1, 6, 0, 255, 0);
                dxball_show_high_scores = 1;
                dxball_load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
                dxball_redraw_mode(); dxball_palette_transition(1, 6, 0, 255, 1);
            } else { dxball_end_requested = 1; dxball_return_to_menu = 0; }
        }
        dxball_mouse_action = 0;
    }
    if (dxball_mouse_action == 2) dxball_mouse_action = 0;
    return;
}

void dxball_edit_score_name(char key)
{
    if (key == '\r') {
        dxball_selected_score_index = dxball_insert_high_score(dxball_score_name, (DxBallUInt)dxball_score);
        dxball_entering_score_name = 0;
        dxball_palette_transition(1, 6, 0, 255, 0);
        dxball_show_high_scores = 1;
        dxball_load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
        dxball_redraw_mode(); dxball_palette_transition(1, 6, 0, 255, 1);
    }
    if (key == '\b' && dxball_score_name_length > 0) {
        --dxball_score_name_length;
        dxball_score_name[dxball_score_name_length] = 0;
    }
    if (key == ' ' || (key >= '0' && key <= '9')) {
        if (dxball_score_name_length >= 30) {
            dxball_wait_frames(1);
        } else {
            dxball_score_name[dxball_score_name_length] = key;
            dxball_score_name[dxball_score_name_length + 1] = 0;
            ++dxball_score_name_length;
        }
    }
    if (key >= 'A' && key <= 'Z') {
        key = (char)tolower(key);
        if (dxball_shift_pressed == 1) key = (char)toupper(key);
        if (dxball_score_name_length >= 30) {
            dxball_wait_frames(1);
        } else {
            dxball_score_name[dxball_score_name_length] = key;
            dxball_score_name[dxball_score_name_length + 1] = 0;
            ++dxball_score_name_length;
        }
    }
    return;
}
void dxball_game_over_key(char key)
{
    if (dxball_entering_score_name == 1) {
        dxball_edit_score_name(key);
    } else {
        switch (key) {
        case ' ': break;
        case 'p': break;
        case 'q': break;
        case 'r': break;
        case 't': break;
        case 'u': break;
        case 'v': break;
        case 'w': break;
        case 'x': break;
        case 'y': break;
        case 'z': break;
        case '{': break;
        }
    }
    return;
}

void dxball_dispose_game_over(DxBallInt fade)
{
    DxBallRect rect = {0, 0, 640, 480};
    if (fade != 0) {
        dxball_palette_transition(1, 6, 0, 255, 0);
        dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
        dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
        if (dxball_draw_to_primary == 0) {
            ((DxBallDDSurface *)dxball_secondary_surface)->vtable->blt(
                (DxBallDDSurface *)dxball_secondary_surface, &rect,
                (DxBallDDSurface *)dxball_board_surface, &rect, 0x1000000, NULL);
        }
        dxball_release_sprite_banks(); dxball_release_sounds();
        dxball_close_music();
    }
    return;
}
