#include "intro.h"
#include "platform.h"
#include "paddle.h"
#include "round.h"
#include "effects.h"
#include "trig.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>

DxBallIntroPoint dxball_intro_points[287];
DxBallIntroOffset dxball_intro_offsets[360];
DxBallUInt dxball_intro_tick;
DxBallInt dxball_intro_cursor_x, dxball_intro_cursor_y;
DxBallInt dxball_scroller_length, dxball_scroller_shift, dxball_scroller_index;
DxBallInt dxball_scroller_reserved, dxball_scroller_advance;
DxBallInt dxball_credit_angle, dxball_credit_first_y, dxball_credit_second_y;
DxBallInt dxball_splash_span = 120, dxball_splash_phase = 1, dxball_splash_offset;

/* The point cloud spells DX-BALL on a 41-column, seven-row grid. */
static const char point_mask[7][42] = {
    ".........................................",
    ".###...#...#.....####....#...#.....#.....",
    ".#..#...#.#......#...#..#.#..#.....#.....",
    ".#...#...#...###.#..#..#...#.#.....#.....",
    ".#..#...#.#......#...#.#####.#.....#.....",
    ".###...#...#.....####..#...#.#####.#####.",
    "........................................."
};

static DxBallInt angle_index(DxBallInt angle)
{
    return angle < 0 ? 360 - (-angle) % 360 : angle % 360;
}
DxBallInt dxball_raw_sine(DxBallInt angle) { return dxball_sine_table[angle_index(angle)]; }
DxBallInt dxball_raw_cosine(DxBallInt angle) { return dxball_cosine_table[angle_index(angle)]; }
DxBallInt dxball_wave_x(DxBallInt origin, DxBallInt angle, DxBallInt amplitude)
{
    return origin + dxball_raw_cosine(angle) * amplitude / 1024;
}
DxBallInt dxball_wave_y(DxBallInt origin, DxBallInt angle, DxBallInt amplitude)
{
    return origin + dxball_raw_sine(angle) * amplitude / 1024;
}

static void scene_blt(DxBallSurface destination, DxBallSurface source, const DxBallRect *rect)
{
    DxBallDDSurface *surface = (DxBallDDSurface *)destination;
    surface->vtable->blt(surface, rect, (DxBallDDSurface *)source, rect, 0x1000000, NULL);
}
static void update_intro_cursor(void)
{
    dxball_intro_cursor_x = dxball_mouse_x;
    dxball_intro_cursor_y = dxball_mouse_y;
    if (dxball_intro_cursor_x > 599) dxball_intro_cursor_x = 599;
    if (dxball_intro_cursor_x < 8) dxball_intro_cursor_x = 8;
    if (dxball_intro_cursor_y > 447) dxball_intro_cursor_y = 447;
}
static void dispose_scene(DxBallInt fade)
{
    DxBallRect rect = {0, 0, 640, 480};
    if (fade != 0) {
        dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
        dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
        if (dxball_draw_to_primary == 0) scene_blt(dxball_secondary_surface, dxball_board_surface, &rect);
        dxball_runtime_ops.release_sprite_banks();
        dxball_runtime_ops.release_sounds();
        dxball_platform_ops.close_music();
    }
}

void dxball_initialize_intro_points(void)
{
    DxBallInt i, x = 116, y = 41, angle = 0;
    DxBallIntroPoint *point;
    for (i = 0; i < 287; ++i) {
        point = dxball_intro_points + i;
        point->x = x; point->y = y; point->angle = angle;
        point->kind = point_mask[i / 41][i % 41] == '#';
        if (point->kind == 1) { point->y -= 5; point->angle += 30; }
        angle += 20;
        if (x - 106 > 400) { x = 116; angle = y - 31; y += 10; }
        else x += 10;
    }
    for (i = 0; i < 360; ++i) {
        dxball_intro_offsets[i].x = dxball_wave_x(0, i, 4);
        dxball_intro_offsets[i].y = dxball_wave_y(0, i, 3);
    }
}

void dxball_update_intro_points(void)
{
    DxBallRect rect = {112, 37, 530, 115};
    DxBallSurfaceDesc desc;
    DxBallDDSurface *surface;
    DxBallIntroPoint *point;
    DxBallIntroOffset offset;
    DxBallInt i;
    if (dxball_elapsed(dxball_intro_tick, 50)) {
        dxball_select_surface(dxball_board_surface);
        surface = (DxBallDDSurface *)dxball_active_surface;
        surface->vtable->blt_fast(surface, 112, 37, (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
        memset(&desc, 0, sizeof(desc)); desc.size = 108; desc.flags = 14;
        surface->vtable->get_desc(surface, &desc);
        while (surface->vtable->lock(surface, NULL, &desc, 0, NULL) != 0) {}
        for (i = 0; i < 287; ++i) {
            point = dxball_intro_points + i;
            if (point->kind == 0) {
                point->angle += 30;
                if (point->angle > 359) point->angle %= 360;
                offset = dxball_intro_offsets[point->angle];
                desc.pixels[(point->y + offset.y) * desc.pitch + point->x + offset.x] = 200;
            }
        }
        surface->vtable->unlock(surface, NULL);
        for (i = 0; i < 287; ++i) {
            point = dxball_intro_points + i;
            if (point->kind == 1) {
                point->angle += 30;
                if (point->angle > 359) point->angle %= 360;
                offset = dxball_intro_offsets[point->angle];
                dxball_draw_keyed_sprite(1, point->x + offset.x, point->y + offset.y);
            }
        }
        dxball_invalidate_region(rect.left, rect.top, rect.right, rect.bottom);
        dxball_animate_palette(200, 207, 1);
        dxball_intro_tick = dxball_current_time();
    }
}

void dxball_initialize_intro(void)
{
    dxball_runtime_ops.reset_regions();
    dxball_runtime_ops.clear_surface(dxball_background_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "mainmenu.pcx", 2, 0, 0);
    dxball_runtime_ops.load_sprite_bank(0, 1, "mainmenu.sbk");
    dxball_runtime_ops.load_sprite_bank(1, 0, "thefont.sbk");
    dxball_runtime_ops.load_sprite_bank(2, 0, "sfont.sbk");
    dxball_select_sprite_bank(0); dxball_select_font_bank(1);
    dxball_platform_ops.load_music("ethno_pa.mds", 1);
    dxball_runtime_ops.bind_board_surface(dxball_board_surface); dxball_intro_tick = 0;
    dxball_runtime_ops.bind_display_surface(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface);
    dxball_redraw_mode(); dxball_initialize_intro_points(); dxball_update_intro_points();
    dxball_restore_regions();
    if (dxball_draw_to_primary == 0) dxball_present();
    dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
}

void dxball_redraw_intro(void)
{
    DxBallRect rect = {0, 0, 640, 480};
    char text[32];
    dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
    if (dxball_draw_to_primary == 0) dxball_runtime_ops.clear_surface(dxball_secondary_surface, 0);
    dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
    scene_blt(dxball_board_surface, dxball_background_surface, &rect);
    dxball_select_surface(dxball_board_surface); dxball_select_font_bank(2);
    dxball_wait_frames(1);
    if (dxball_score != 0) {
        sprintf(text, "Last Score - %u", (DxBallUInt)dxball_score);
        dxball_runtime_ops.draw_text(3, 10, (DxBallInt)strlen(text), text);
    }
    dxball_wait_frames(1); dxball_runtime_ops.draw_text(615, 10, 6, "V 1.07");
    dxball_wait_frames(1); dxball_runtime_ops.draw_text(485, 130, 19, "By Michael P. Welch");
    dxball_wait_frames(1); dxball_runtime_ops.draw_text(3, 465, 59, "Copyright  1996  by Michael P. Welch,  All Rights Reserved.");
    dxball_wait_frames(1); dxball_runtime_ops.draw_text(3, 475, 109, "You may freely distribute this game so long as it's not sold for profit without the author's written consent.");
    dxball_select_font_bank(1);
    dxball_wait_frames(1); dxball_runtime_ops.draw_centered_text(317, 210, 22, "BASED ON  ``MEGABALL``");
    dxball_wait_frames(1); dxball_runtime_ops.draw_centered_text(317, 250, 19, "BY ED AND AL MACKEY");
    scene_blt(dxball_primary_surface, dxball_board_surface, &rect);
    if (dxball_draw_to_primary == 0) scene_blt(dxball_secondary_surface, dxball_board_surface, &rect);
}

void dxball_intro_frame(void)
{
    if (dxball_draw_to_primary != 0) dxball_wait_frames(1);
    dxball_restore_regions(); update_intro_cursor(); dxball_update_intro_points();
    if (dxball_draw_to_primary == 0) dxball_present();
    dxball_rotate_palette_right(48, 63, 1);
    if (dxball_mouse_action == 1) { dxball_end_requested = 1; dxball_return_to_menu = 1; dxball_mouse_action = 0; }
    if (dxball_mouse_action == 2) dxball_mouse_action = 0;
}
void dxball_intro_key(char key)
{
    if (key == 0x70 && dxball_control_pressed != 0) { dxball_end_requested = 1; dxball_return_to_menu = 2; }
}
void dxball_dispose_intro(DxBallInt fade) { dispose_scene(fade); }

void dxball_initialize_splash(void)
{
    DxBallColorKey key = {0, 0};
    DxBallDDSurface *surface;
    DxBallInt i;
    dxball_runtime_ops.reset_regions(); dxball_runtime_ops.clear_surface(dxball_background_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "intro.pcx", 2, 0, 0);
    dxball_runtime_ops.load_sprite_bank(0, 0, "candy.sbk");
    dxball_runtime_ops.load_sprite_bank(1, 0, "chisel2.sbk");
    dxball_select_sprite_bank(0); dxball_select_font_bank(1);
    dxball_runtime_ops.load_sound(0, "whine.wav");
    dxball_runtime_ops.bind_board_surface(dxball_board_surface);
    dxball_runtime_ops.bind_display_surface(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface);
    dxball_scroller_reserved = 0; dxball_scroller_length = (DxBallInt)strlen(dxball_welcome_text);
    dxball_scroller_index = dxball_scroller_shift = dxball_scroller_advance = 0;
    dxball_credit_first_y = dxball_credit_second_y = dxball_credit_angle = 0;
    surface = (DxBallDDSurface *)dxball_board_surface; surface->vtable->set_color_key(surface, 8, &key);
    dxball_redraw_mode(); dxball_display_ops.update_sound(0, 0, 0, 0);
    for (i = 48; i <= dxball_splash_span + 48; ++i)
        dxball_saved_palette[i].red = dxball_saved_palette[i].green = dxball_saved_palette[i].blue = 0;
    dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
}

void dxball_redraw_splash(void)
{
    DxBallRect full = {0, 0, 640, 480}, logo = {0, 19, 639, 169};
    DxBallInt y;
    dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
    if (dxball_draw_to_primary == 0) dxball_fill_rect(dxball_secondary_surface, 0, 0, 639, 479, 0);
    dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
    scene_blt(dxball_board_surface, dxball_background_surface, &full);
    scene_blt(dxball_primary_surface, dxball_board_surface, &logo);
    if (dxball_draw_to_primary == 0) {
        dxball_runtime_ops.bind_display_surface(dxball_primary_surface); dxball_draw_waving_credits();
        dxball_runtime_ops.bind_display_surface(dxball_secondary_surface);
    }
    for (y = 155; y <= dxball_splash_span * 2 + 155; y += 2) {
        dxball_draw_line(dxball_primary_surface, 0, y, 639, y, (DxBallByte)((y - 155) / 2 + 48));
        dxball_draw_line(dxball_primary_surface, 0, y + 1, 639, y + 1, (DxBallByte)((y - 155) / 2 + 48));
    }
    dxball_select_surface(dxball_primary_surface); dxball_select_font_bank(0);
    dxball_runtime_ops.draw_text(20, 190, 11, "VIDEO CARD:");
    if (dxball_software_only != 0) {
        dxball_runtime_ops.draw_text(180, 190, 24, "NO HARDWARE ACCELERATION");
        dxball_runtime_ops.draw_text(210, 210, 28, "DEFAULT TO >COMPATIBLE< MODE");
    } else if (dxball_low_video_memory != 0) {
        dxball_runtime_ops.draw_text(180, 190, 16, "LOW VIDEO MEMORY");
        dxball_runtime_ops.draw_text(210, 210, 28, "DEFAULT TO >COMPATIBLE< MODE");
    } else if (dxball_wait_vertical_blank == 0) {
        dxball_runtime_ops.draw_text(180, 190, 25, "REFRESH RATE ABOVE 60 MHZ");
        dxball_runtime_ops.draw_text(210, 210, 28, "DEFAULT TO >COMPATIBLE< MODE");
    } else {
        dxball_runtime_ops.draw_text(180, 190, 27, "HARDWARE ACCELERATION FOUND");
        dxball_runtime_ops.draw_text(210, 210, 13, "AND SUPPORTED");
    }
    dxball_runtime_ops.draw_text(20, 245, 7, "AUTHOR:");
    dxball_runtime_ops.draw_text(180, 245, 16, "MICHAEL P. WELCH");
    dxball_runtime_ops.draw_text(20, 265, 7, "3D GFX:");
    dxball_runtime_ops.draw_text(180, 265, 14, "SEUMAS McNALLY");
    dxball_runtime_ops.draw_text(20, 300, 7, "E-MAIL:");
    dxball_runtime_ops.draw_text(180, 300, 18, "MWELCH@NETWAVE.NET");
    dxball_runtime_ops.draw_centered_text(320, 330, 41, "SEND COMMENTS, BUGS, AND GREETINGS TO GET");
    dxball_runtime_ops.draw_centered_text(320, 350, 37, "HINT FOR LEVEL EDITOR AND OTHER TIPS.");
    if (dxball_draw_to_primary == 0) scene_blt(dxball_secondary_surface, dxball_primary_surface, &full);
}

void dxball_update_scroller(void)
{
    DxBallRect rect = {40, 440, 639, 475};
    DxBallDDSurface *surface = (DxBallDDSurface *)dxball_board_surface;
    dxball_select_font_bank(1); dxball_scroller_shift += 4;
    if (dxball_scroller_advance < dxball_scroller_shift) {
        ++dxball_scroller_index;
        if (dxball_scroller_index > dxball_scroller_length - 1) dxball_scroller_index = 0;
        dxball_select_surface(dxball_board_surface);
        dxball_scroller_advance = dxball_draw_glyph(dxball_welcome_text[dxball_scroller_index], 600, 470) + 1;
        if (dxball_scroller_advance == 1) dxball_scroller_advance = 15;
        dxball_scroller_shift = 0;
    }
    surface->vtable->blt_fast(surface, 36, 440, surface, &rect, 0x10);
}
void dxball_draw_scroller_wave(void)
{
    DxBallRect rect = {0, 440, 0, 475};
    DxBallDDSurface *surface = (DxBallDDSurface *)(dxball_reduced_particles == 0 ? dxball_effect_surface : dxball_primary_surface);
    DxBallInt x, y;
    for (x = 40; x <= 595; x += 5) {
        rect.left = x; rect.right = x + 5; y = 420 + (DxBallInt)(dxball_sine(x) * 20.0);
        surface->vtable->blt_fast(surface, x, y, (DxBallDDSurface *)dxball_board_surface, &rect, 0x10);
    }
}
void dxball_draw_waving_credits(void)
{
    DxBallRect first = {0, 335, 639, 353}, second = {0, 362, 639, 380};
    DxBallDDSurface *surface = (DxBallDDSurface *)(dxball_reduced_particles == 0 ? dxball_effect_surface : dxball_primary_surface);
    dxball_credit_angle += 20;
    if (dxball_credit_angle > 359) dxball_credit_angle %= 360;
    dxball_credit_first_y = (DxBallInt)(dxball_sine(dxball_credit_angle) * 3.0);
    dxball_credit_second_y = (DxBallInt)(dxball_sine(-dxball_credit_angle) * 3.0);
    surface->vtable->blt_fast(surface, 0, dxball_credit_first_y + 3, (DxBallDDSurface *)dxball_board_surface, &first, 0x10);
    surface->vtable->blt_fast(surface, 0, dxball_credit_second_y + 127, (DxBallDDSurface *)dxball_board_surface, &second, 0x10);
}
void dxball_pulse_splash_palette(void)
{
    DxBallInt i, middle;
    if (dxball_cursor_warp_disabled != 0) return;
    for (i = 48; i <= dxball_splash_span + 48; ++i) {
        if (dxball_live_palette[i].red != 0) dxball_live_palette[i].red -= 4;
        if (dxball_live_palette[i].blue != 0) dxball_live_palette[i].blue -= 2;
    }
    middle = dxball_splash_span / 2 + 48;
    dxball_splash_offset = (DxBallInt)(dxball_sine(dxball_splash_phase) * (dxball_splash_span / 2 - 1));
    ++dxball_splash_phase;
    if (dxball_splash_phase > 359) dxball_splash_phase %= 360;
    dxball_live_palette[middle + dxball_splash_offset].red = 160;
    dxball_live_palette[middle + dxball_splash_offset + 1].red = 160;
    dxball_live_palette[middle - dxball_splash_offset].blue = 160;
    dxball_live_palette[middle - dxball_splash_offset + 1].blue = 160;
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, 48, dxball_splash_span + 48, dxball_live_palette + 48);
}
void dxball_splash_frame(void)
{
    dxball_display_ops.update_sound(0, 0, 0, 0);
    if (dxball_draw_to_primary != 0) dxball_wait_frames(1);
    dxball_restore_regions(); update_intro_cursor(); dxball_update_scroller(); dxball_draw_scroller_wave();
    if (dxball_draw_to_primary == 0) dxball_present();
    dxball_rotate_rgb_colors(189, 66, dxball_splash_colors); dxball_pulse_splash_palette();
    if (dxball_mouse_action == 1) { dxball_end_requested = 1; dxball_return_to_menu = 0; dxball_mouse_action = 0; }
    if (dxball_mouse_action == 2) dxball_mouse_action = 0;
}
void dxball_splash_key(void) { dxball_end_requested = 1; dxball_return_to_menu = 0; }
void dxball_dispose_splash(DxBallInt fade) { dxball_gameplay_ops.stop_sound(0); dispose_scene(fade); }

/* Retained program text and 22 RGB triples; no external game assets. */
const char dxball_welcome_text[] =
    " WELCOME TO DX-BALL.     GREETINGS GO OUT TO:  ED + AL MACKEY, SIMEON, LARRY, MI"
    "KE BOEH, DARK UNICORN PRODUCTIONS (SHANE, JOHN, SEUMAS, ERIC (SIDEWINDER), REMEM"
    "BER KIT...), AND THE 'MAD TESTER' CHAY-BOB.     LAST MINUTE SUPER THANKS GOES TO"
    " SHANE MONROE FOR THE DX-BALL WEB PAGE.    IT ROCKS!     THIS PROJECT WAS MANY L"
    "ONG MONTHS IN THE MAKING.    LATE NIGHTS, LOTS OF MOUNTAIN DEW, AND MANY PROGRAM"
    "MING BOOKS GOT THIS, MY FIRST DIRECT X AND PC GAME, FINISHED FOR YOUR VIEWING PL"
    "EASURE.      ABOUT THE GAME: I KNOW 'BREAKOUT' GAMES HAVE BEEN DONE TO DEATH, BU"
    "T I HAVEN'T FOUND ONE YET THAT'S AS COMPELLING AS MEGABALL FOR THE AMIGA COMPUTE"
    "R.    SINCE MEGABALL IS MY WIFE'S FAVORITE GAME, I THOUGHT I'D MAKE HER A VERSIO"
    "N THAT SHE CAN PLAY ON MY PENTIUM 60.  :)      BY THE WAY, DX-BALL IS MEANT TO B"
    "E AN AMIGA GAME TRAPPED IN A PC'S BODY.   (SMILE)    ALSO GOT SOME RETRO COMMODO"
    "RE 64 MIXED IN HERE AND THERE...  IF ONLY I HAD A DIRECT SOUND 'MOD' PLAYER, THE"
    "N EVERYTHING WOULD BE PERFECT!      ABOUT THE AUTHOR: HI I'M MIKE, BUT SOME CALL"
    " ME 'SCORCH.'    I'M THAT KID WHO WROTE THE AMIGA GAME 'SCORCHED TANKS.'    I KN"
    "OW, I KNOW, ALL YOU PC PEOPLE ARE SAYING 'NO STUPID, THAT'S SCORCHED EARTH!'    "
    "WELL, 'S-TANKS' WAS THE AMIGA ANSWER TO 'EARTH.'    THE WHOLE SCORCH PROJECT WAS"
    " VERY EXCELLENT AND THE RESPONSE FROM MY FELLOW AMI FANS WAS INCREDIBLE.    CERT"
    "AINLY, '94 WAS THE BEGINNING OF THE REST OF MY LIFE, AND I MUST SAY THANKS TO MY"
    " FRIENDS ALL OVER THE WORLD.        HEY, IF YOU'RE STILL READING THIS SCROLLER, "
    "THEN MORE POWER TO YA!   LET'S TALK ABOUT CODE...   DX-BALL WAS WRITTEN TO BE CO"
    "MPATIBLE WITH EVERY POSSIBLE PC THAT CAN INSTALL DIRECT X 2.    I BOUGHT 4 VIDEO"
    " CARDS ON MY OWN AND BORROWED 2 VIDEO CARDS FROM MY GOOD FRIEND MIKE BOEH.    I "
    "TOOK DX-BALL TO WORK, NEIGHBOR'S HOUSE, FATHER-IN-LAW'S HOUSE, BROTHER-IN-LAW'S "
    "HOUSE, AND EVEN HAD IT TESTED WITH WINDOWS NT AS SOON AS THE NEW RELEASE SUPPORT"
    "ED DIRECT X.    I EVEN ASKED/FORCED MY FRIENDS TO TAKE IT HOME AND TRY IT ON THE"
    "IR PC'S.  :O  MAN I FOUND A LOT OF BUGS IN THE GAME, AND LOTS OF QUIRKS IN DIREC"
    "T X.    I HOPE I GOT THEM ALL, BUT IF I DIDN'T, I KNOW I CAN COUNT ON 'YOU' TO S"
    "END ME AN E-MAIL.    SO I FOUND OUT TWO IMPORTANT THINGS FROM MY EXPERIMENTS.   "
    " FIRST OF ALL, DIRECT X'S HARDWARE ACCELERATION IS VERY COOL.    SECOND, I LEARN"
    "ED THAT NOT EVERY VIDEO CARD SUPPORTS IT.    FOR INSTANCE, VIDEO CARDS WITH: S3,"
    " MACH32/64, MATROX, TSENG, AND OTHERS WITH HARDWARE SUPPORT CAN SPEED-UP GRAPHIC"
    "S 'BLITTING' BY AT LEAST 3X IF DONE PROPERLY.    BUT THERE ARE VERY COMMON VIDEO"
    " CARDS WITH TRIDENT OR ARK CHIPSETS THAT HAVE NO SUPPORT.    THEY WILL RUN DIREC"
    "T X GAMES, BUT THE EMULATION MODE CAN SLOW IT WAY DOWN.    UNTIL THE DAY THAT EV"
    "ERYONE GETS A NEW COMPUTER OR VIDEO CARD, DIRECT X WILL NOT REACH IT'S FULL POTE"
    "NTIAL.    BUT FOR NOW, US PROGRAMMERS WILL WORK OUR BRAINS OUT TO GIVE EVERYONE "
    "A CHANCE TO PLAY OUR GAMES.    DX-BALL RUNS ON ALL VIDEO CARDS, EITHER IN THE BL"
    "AZING FAST MODE, OR IN THE 'COMPATIBILITY' MODE THAT KEEPS UP WITH THE 60 FPS ST"
    "ANDARD.    I ONLY ASK THAT IF YOUR SYSTEM HAS A VERY HIGH REFRESH RATE... THEN M"
    "AYBE YOU OUGHT TO LOWER IT FOR THE SAKE OF PLAYING DX-BALL AT A NORMAL SPEED.  :"
    ")    WELL, I'VE TALKED ABOUT EVERYTHING NOW AND IT'S TIME TO WRAP-UP THIS EXTRA "
    "LONG SCROLLER.    THANKS FOR READING, AND ENJOY THE GAME.                       "
    "                          MADE YOU LOOK!  HEHEHEHEHEHE                          "
    "                                        "
;
DxBallInt dxball_splash_colors[66] = {
    0, 20, 240,
    0, 40, 240,
    0, 60, 240,
    0, 80, 240,
    0, 100, 240,
    0, 120, 240,
    0, 140, 240,
    0, 160, 240,
    0, 180, 240,
    0, 200, 240,
    0, 220, 240,
    0, 240, 240,
    0, 220, 240,
    0, 200, 240,
    0, 180, 240,
    0, 160, 240,
    0, 140, 240,
    0, 120, 240,
    0, 100, 240,
    0, 80, 240,
    0, 60, 240,
    0, 40, 240,
};
