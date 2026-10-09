#include "gameover.h"
#include "startup.h"
#include "platform.h"
#include "intro.h"
#include "paddle.h"
#include "round.h"
#include "ui.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char dxball_score_name[40];
DxBallInt dxball_score_name_length, dxball_selected_score_index;
DxBallUInt dxball_score_blink_tick;
DxBallInt dxball_score_cursor_visible, dxball_show_high_scores;
DxBallInt dxball_entering_score_name;

static void copy_scene(DxBallSurface destination, DxBallSurface source)
{
    DxBallRect rect = {0, 0, 640, 480};
    DxBallDDSurface *surface = (DxBallDDSurface *)destination;
    surface->vtable->blt(surface, &rect, (DxBallDDSurface *)source, &rect, 0x1000000, NULL);
}

DxBallInt dxball_insert_high_score(const char *name, DxBallUInt score)
{
    DxBallInt rank, i;
    dxball_read_scores();
    if (score < dxball_scores[14].score) return -1;
    for (rank = 14; rank >= 0 && dxball_scores[rank].score <= score; --rank) {}
    ++rank;
    for (i = 13; i >= rank; --i) {
        strcpy(dxball_scores[i + 1].name, dxball_scores[i].name);
        dxball_scores[i + 1].score = dxball_scores[i].score;
    }
    strcpy(dxball_scores[rank].name, name);
    dxball_scores[rank].score = score;
    if (dxball_startup_file_ops.access("score.dat", 2) == 0) {
        dxball_board_file = dxball_startup_file_ops.open("score.dat", "wb");
        if (dxball_board_file != NULL) {
            dxball_startup_file_ops.write(dxball_scores, 44, 15, dxball_board_file);
            dxball_startup_file_ops.close(dxball_board_file);
        }
    }
    return rank;
}

void dxball_draw_high_scores(void)
{
    DxBallInt i, y = 170, count;
    char value[20];
    for (i = 0; i < 15; ++i, y += 20) {
        if (dxball_selected_score_index == i) {
            dxball_draw_line(dxball_active_surface, 5, y - 14, 635, y - 14, 200);
            dxball_draw_line(dxball_active_surface, 5, y + 5, 635, y + 5, 200);
            dxball_draw_line(dxball_active_surface, 5, y - 14, 5, y + 4, 200);
            dxball_draw_line(dxball_active_surface, 635, y - 14, 635, y + 4, 200);
        }
        dxball_draw_text(10, y, (DxBallInt)strlen(dxball_scores[i].name), dxball_scores[i].name);
        sprintf(value, "%u", dxball_scores[i].score);
        count = (DxBallInt)strlen(value);
        dxball_draw_text(630 - dxball_measure_text(count, value), y, count, value);
    }
}

void dxball_initialize_game_over(void)
{
    dxball_runtime_ops.reset_regions();
    dxball_runtime_ops.clear_surface(dxball_background_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
    dxball_runtime_ops.load_sprite_bank(0, 1, "mainmenu.sbk");
    dxball_runtime_ops.load_sprite_bank(1, 0, "sysfont.sbk");
    dxball_select_sprite_bank(0); dxball_select_font_bank(1);
    dxball_platform_ops.load_music("acker-gs.mds", 1);
    dxball_runtime_ops.bind_board_surface(dxball_board_surface);
    dxball_runtime_ops.bind_display_surface(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface);
    dxball_read_scores();
    dxball_score_name[0] = 0;
    dxball_score_name_length = 0; dxball_score_blink_tick = 0;
    dxball_score_cursor_visible = 0; dxball_selected_score_index = -1;
    dxball_entering_score_name = dxball_scores[14].score <= (DxBallUInt)dxball_score;
    dxball_show_high_scores = 0;
    dxball_redraw_mode(); dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
}

void dxball_redraw_game_over(void)
{
    char value[100];
    dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
    if (dxball_draw_to_primary == 0) dxball_runtime_ops.clear_surface(dxball_secondary_surface, 0);
    dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
    copy_scene(dxball_board_surface, dxball_background_surface);
    dxball_select_surface(dxball_board_surface);
    if (dxball_show_high_scores == 1) dxball_draw_high_scores();
    else if (dxball_entering_score_name == 1) {
        dxball_draw_centered_text(320, 170, 22, "You have a high score!");
        dxball_draw_text(70, 200, 16, "Enter your name:");
    } else {
        dxball_draw_centered_text(320, 170, 11, "Your score:");
        sprintf(value, "%u", (DxBallUInt)dxball_score);
        dxball_draw_centered_text(320, 200, (DxBallInt)strlen(value), value);
    }
    copy_scene(dxball_primary_surface, dxball_board_surface);
    if (dxball_draw_to_primary == 0) copy_scene(dxball_secondary_surface, dxball_board_surface);
}

void dxball_game_over_frame(void)
{
    DxBallInt count;
    if (dxball_draw_to_primary != 0) dxball_wait_frames(1);
    dxball_restore_regions();
    dxball_intro_cursor_x = dxball_mouse_x; dxball_intro_cursor_y = dxball_mouse_y;
    if (dxball_intro_cursor_x > 599) dxball_intro_cursor_x = 599;
    if (dxball_intro_cursor_x < 8) dxball_intro_cursor_x = 8;
    if (dxball_intro_cursor_y > 447) dxball_intro_cursor_y = 447;
    if (dxball_entering_score_name == 1) {
        dxball_select_surface(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface);
        count = (DxBallInt)strlen(dxball_score_name);
        dxball_draw_text(70, 230, count, dxball_score_name);
        if (dxball_score_cursor_visible == 1)
            dxball_draw_text(71 + dxball_measure_text(count, dxball_score_name), 230, 1, "_");
        if (dxball_elapsed(dxball_score_blink_tick, 300)) {
            dxball_score_cursor_visible = 1 - dxball_score_cursor_visible;
            dxball_score_blink_tick = dxball_current_time();
        }
        dxball_queue_region(0, 210, 639, 234);
    }
    if (dxball_draw_to_primary == 0) dxball_present();
    if (dxball_show_high_scores == 1 && dxball_entering_score_name == 0) {
        if (dxball_elapsed(dxball_score_blink_tick, 100)) {
            dxball_score_blink_tick = dxball_current_time();
            dxball_animate_palette(200, 207, 1);
        }
    }
    if (dxball_mouse_action == 1) {
        if (dxball_entering_score_name == 0) {
            if (dxball_show_high_scores == 0) {
                dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
                dxball_show_high_scores = 1;
                dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
                dxball_redraw_mode(); dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
            } else { dxball_end_requested = 1; dxball_return_to_menu = 0; }
        } else dxball_wait_frames(1);
        dxball_mouse_action = 0;
    }
    if (dxball_mouse_action == 2) dxball_mouse_action = 0;
}

void dxball_edit_score_name(char key)
{
    if (key == '\r') {
        dxball_selected_score_index = dxball_insert_high_score(dxball_score_name, (DxBallUInt)dxball_score);
        dxball_entering_score_name = 0;
        dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_show_high_scores = 1;
        dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "highscor.pcx", 2, 0, 0);
        dxball_redraw_mode(); dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
    }
    if (key == '\b' && dxball_score_name_length > 0)
        dxball_score_name[--dxball_score_name_length] = 0;
    if (key == ' ' || (key >= '0' && key <= '9') || (key >= 'A' && key <= 'Z')) {
        if (key >= 'A' && key <= 'Z') {
            key = (char)tolower(key);
            if (dxball_shift_pressed == 1) key = (char)toupper(key);
        }
        if (dxball_score_name_length < 30) {
            dxball_score_name[dxball_score_name_length] = key;
            dxball_score_name[dxball_score_name_length + 1] = 0;
            ++dxball_score_name_length;
        } else dxball_wait_frames(1);
    }
}
void dxball_game_over_key(char key)
{
    if (dxball_entering_score_name == 1) dxball_edit_score_name(key);
}

void dxball_dispose_game_over(DxBallInt fade)
{
    if (fade != 0) {
        dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
        dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
        if (dxball_draw_to_primary == 0) copy_scene(dxball_secondary_surface, dxball_board_surface);
        dxball_runtime_ops.release_sprite_banks(); dxball_runtime_ops.release_sounds();
        dxball_platform_ops.close_music();
    }
}
