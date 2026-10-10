#include "platform.h"
#include "file.h"
#include "paddle.h"
#include "bonuses.h"
#include "round.h"
#include "trig.h"
#include "intro.h"
#include "gameover.h"
#include "editor.h"
#include "midi.h"
#include "sound.h"
#include <stdlib.h>
#include <string.h>

DxBallInt (DXBALL_DDCALL *dxball_window_get_cursor_pos)(DxBallPoint *);
DxBallInt (DXBALL_DDCALL *dxball_window_peek_message)(DxBallMessage *, DxBallHandle, DxBallUInt, DxBallUInt, DxBallUInt);
DxBallInt (DXBALL_DDCALL *dxball_window_wait_message)(void);
DxBallInt (DXBALL_DDCALL *dxball_window_get_message)(DxBallMessage *, DxBallHandle, DxBallUInt, DxBallUInt);
DxBallInt (DXBALL_DDCALL *dxball_window_translate_message)(const DxBallMessage *);
DxBallWindowResult (DXBALL_DDCALL *dxball_window_dispatch_message)(const DxBallMessage *);
DxBallWindowResult (DXBALL_DDCALL *dxball_window_default_window_proc)(DxBallHandle, DxBallUInt, DxBallHandle, DxBallWindowResult);
DxBallInt (DXBALL_DDCALL *dxball_window_post_message)(DxBallHandle, DxBallUInt, DxBallHandle, DxBallWindowResult);
void (DXBALL_DDCALL *dxball_window_post_quit_message)(DxBallInt);
DxBallHandle (DXBALL_DDCALL *dxball_window_set_cursor)(DxBallHandle);
DxBallHandle (DXBALL_DDCALL *dxball_window_set_capture)(DxBallHandle);
DxBallInt (DXBALL_DDCALL *dxball_window_release_capture)(void);
DxBallInt (DXBALL_DDCALL *dxball_window_get_version_ex)(DxBallVersionInfo *);
DxBallHandle (DXBALL_DDCALL *dxball_window_load_icon)(DxBallHandle, DxBallHandle);
DxBallHandle (DXBALL_DDCALL *dxball_window_load_cursor)(DxBallHandle, DxBallHandle);
DxBallHandle (DXBALL_DDCALL *dxball_window_stock_object)(DxBallInt);
DxBallUInt (DXBALL_DDCALL *dxball_window_register_class)(const DxBallWindowClass *);
DxBallHandle (DXBALL_DDCALL *dxball_window_create_window_ex)(DxBallUInt, const char *, const char *,
        DxBallUInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt,
        DxBallHandle, DxBallHandle, DxBallHandle, void *);
DxBallInt (DXBALL_DDCALL *dxball_window_show_window)(DxBallHandle, DxBallInt);
DxBallInt (DXBALL_DDCALL *dxball_window_update_window)(DxBallHandle);
DxBallHandle (DXBALL_DDCALL *dxball_window_set_focus)(DxBallHandle);
DxBallInt (DXBALL_DDCALL *dxball_window_destroy_window)(DxBallHandle);
DxBallInt (DXBALL_DDCALL *dxball_window_message_box)(DxBallHandle, const char *, const char *, DxBallUInt);
DxBallHandle (DXBALL_DDCALL *dxball_window_open_semaphore)(DxBallUInt,
    DxBallInt, const char *);
DxBallHandle (DXBALL_DDCALL *dxball_window_create_semaphore)(
    const DxBallSecurityAttributes *, DxBallInt, DxBallInt, const char *);
const char dxball_semaphore_open_name[] = "DX-Ball";
const char dxball_semaphore_create_name[] = "DX-Ball";
static void load_platform_music(const char *path, DxBallInt play)
{ (void)dxball_load_music(path, play); }
DxBallPlatformOps dxball_platform_ops = {
    dxball_prepare_sound, dxball_initialize_sound, dxball_pause_sound,
    dxball_resume_music, dxball_pause_music, dxball_close_music,
    dxball_release_audio, load_platform_music, exit
};
DxBallKeyModeOps dxball_key_mode_ops = { {dxball_intro_key, dxball_game_key, dxball_editor_key, dxball_game_over_key}, dxball_splash_key };
DxBallHandle dxball_main_window, dxball_instance_semaphore;
DxBallInt dxball_application_active, dxball_shift_pressed, dxball_control_pressed;
DxBallInt dxball_sound_suspended, dxball_low_video_memory;
DxBallInt dxball_software_only = 1;
DxBallPoint dxball_cursor_point;
DxBallDDClipper *dxball_direct_clipper;

const char dxball_fullscreen_name[] = "DX-Ball";
const char dxball_fullscreen_factory_title[] = "DX-Ball";
const char dxball_fullscreen_factory_message[] = "Direct X could not initialize. (DX Object failed)";
const char dxball_fullscreen_cooperative_title[] = "DX-Ball";
const char dxball_fullscreen_cooperative_message[] = "Direct X could not initialize. (Exclusive/Fullscreen failed)";
const char dxball_fullscreen_display_title[] = "DX-Ball";
const char dxball_fullscreen_display_message[] = "Direct X could not initialize. (640x480 failed)";
const char dxball_fullscreen_primary_title[] = "DX-Ball";
const char dxball_fullscreen_primary_message[] = "Direct X could not initialize. (Primary Failed)";
const char dxball_compatible_name[] = "DX-Ball";
const char dxball_compatible_factory_title[] = "DX-Ball";
const char dxball_compatible_factory_message[] = "Direct X could not initialize. (DX Object failed)";
const char dxball_compatible_cooperative_title[] = "DX-Ball";
const char dxball_compatible_cooperative_message[] = "Direct X could not initialize.(Coop Normal failed)";
const char dxball_compatible_primary_title[] = "DX-Ball";
const char dxball_compatible_primary_message[] = "Direct X could not initialize. (Primary failed)";
const char dxball_compatible_board_title[] = "DX-Ball";
const char dxball_compatible_board_message[] = "Direct X could not initialize. (Offscreen failed)";
const char dxball_compatible_clipper_title[] = "DX-Ball";
const char dxball_compatible_clipper_message[] = "Direct X could not initialize.(Clipper failed)";
const char dxball_compatible_clip_window_title[] = "DX-Ball";
const char dxball_compatible_clip_window_message[] = "Direct X could not initialize. (Clipper SetHWnd failed)";
const char dxball_compatible_primary_clipper_title[] = "DX-Ball";
const char dxball_compatible_primary_clipper_message[] = "Direct X could not initialize. (Clipper->Primary failed)";

/* FUNCTION: DXBALL 0x0040CF70 */
DxBallInt dxball_initialize_fullscreen(DxBallHandle instance, DxBallInt show)
{
    DxBallWindowClass window_class;
    DxBallDrawCaps caps;
    DxBallSurfaceDesc surface;
    DxBallInt result;
    DxBallUInt attached;
    window_class.style = 3;
    window_class.procedure = dxball_window_proc;
    window_class.class_extra = 0;
    window_class.window_extra = 0;
    window_class.instance = instance;
    window_class.icon = dxball_window_load_icon(instance, 0x7f00);
    window_class.cursor = dxball_window_load_cursor(0, 0x7f00);
    window_class.background = dxball_window_stock_object(4);
    window_class.menu = dxball_fullscreen_name;
    window_class.name = dxball_fullscreen_name;
    dxball_window_register_class(&window_class);
    dxball_main_window = dxball_window_create_window_ex(0, dxball_fullscreen_name, dxball_fullscreen_name,
        0x80000000UL, 0, 0, 640, 480, 0, 0, instance, NULL);
    if (dxball_main_window == 0) return 0;
    dxball_window_show_window(dxball_main_window, show);
    dxball_window_update_window(dxball_main_window);
    dxball_window_set_focus(dxball_main_window);
    dxball_window_show_window(dxball_main_window, 0);
    dxball_prepare_sound(dxball_main_window);
    dxball_window_show_window(dxball_main_window, 5);
    result = dxball_direct_draw_create(NULL, &dxball_direct_draw, NULL);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_fullscreen_factory_message,
            dxball_fullscreen_factory_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    result = ((DxBallSetCooperativeLevel)dxball_direct_draw->vtable->slots_7_to_21[13])(
        dxball_direct_draw, dxball_main_window, 0x11);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_fullscreen_cooperative_message,
            dxball_fullscreen_cooperative_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    result = ((DxBallSetDisplayMode)dxball_direct_draw->vtable->slots_7_to_21[14])(
        dxball_direct_draw, 640, 480, 8);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_fullscreen_display_message,
            dxball_fullscreen_display_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    dxball_draw_to_primary = 0;
    caps.size = 316;
    result = ((DxBallGetCaps)dxball_direct_draw->vtable->slots_7_to_21[4])(
        dxball_direct_draw, &caps, NULL);
    if ((caps.caps & 0x02000000UL) != 0) {
        dxball_software_only = 1;
        dxball_reduced_particles = 1;
    } else {
        dxball_software_only = 0;
        dxball_reduced_particles = 0;
    }
    if (dxball_software_only == 0 && caps.free_video_memory < 310000UL) {
        dxball_reduced_particles = 1;
        dxball_low_video_memory = 1;
    }
    if (dxball_display_buffer_count == 0) {
        surface.size = 108;
        surface.flags = 1;
        surface.caps = 0x200;
    } else {
        surface.size = 108;
        surface.flags = 0x21;
        surface.caps = 0x218;
        surface.ancillary[0] = (DxBallUInt)dxball_display_buffer_count;
    }
    result = dxball_direct_draw->vtable->create_surface(
        dxball_direct_draw, &surface, &dxball_primary_surface, NULL);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_fullscreen_primary_message,
            dxball_fullscreen_primary_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    if (dxball_display_buffer_count != 0) {
        attached = 4;
        result = ((DxBallGetAttachedSurface)dxball_primary_surface->vtable->slot_12)(
            dxball_primary_surface, &attached, &dxball_secondary_surface);
        if (result != 0) {
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
    }
    surface.flags = 7;
    surface.caps = 0x40;
    surface.height = 480;
    surface.width = 640;
    result = dxball_direct_draw->vtable->create_surface(
        dxball_direct_draw, &surface, &dxball_board_surface, NULL);
    if (result != 0) {
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    if (dxball_clip_regions == 1) {
        result = ((DxBallCreateClipper)dxball_direct_draw->vtable->slots_0_to_4[4])(
            dxball_direct_draw, 0, &dxball_direct_clipper, NULL);
        if (result != 0) {
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
        result = dxball_direct_clipper->vtable->set_window(
            dxball_direct_clipper, 0, dxball_main_window);
        if (result != 0) {
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
        result = ((DxBallSetClipper)dxball_primary_surface->vtable->set_clipper)(
            dxball_primary_surface, dxball_direct_clipper);
        if (result != 0) {
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
        if (dxball_secondary_surface != NULL) {
            result = ((DxBallSetClipper)dxball_secondary_surface->vtable->set_clipper)(
                dxball_secondary_surface, dxball_direct_clipper);
            if (result != 0) {
                dxball_window_destroy_window(dxball_main_window);
                return 0;
            }
        }
    }
    dxball_initialize_sprite_banks();
    dxball_select_surface((DxBallSurface)dxball_primary_surface);
    return 1;
}

/* FUNCTION: DXBALL 0x0040D4B0 */
DxBallInt dxball_initialize_compatible(DxBallHandle instance, DxBallInt show)
{
    DxBallWindowClass window_class;
    DxBallDrawCaps caps;
    DxBallSurfaceDesc surface;
    DxBallInt result;
    window_class.style = 3;
    window_class.procedure = dxball_window_proc;
    window_class.class_extra = 0;
    window_class.window_extra = 0;
    window_class.instance = instance;
    window_class.icon = dxball_window_load_icon(instance, 0x7f00);
    window_class.cursor = dxball_window_load_cursor(0, 0x7f00);
    window_class.background = dxball_window_stock_object(4);
    window_class.menu = dxball_compatible_name;
    window_class.name = dxball_compatible_name;
    dxball_window_register_class(&window_class);
    dxball_main_window = dxball_window_create_window_ex(0, dxball_compatible_name, dxball_compatible_name,
        0x80000000UL, 0, 0, 640, 480, 0, 0, instance, NULL);
    if (dxball_main_window == 0) return 0;
    dxball_window_show_window(dxball_main_window, show);
    dxball_window_update_window(dxball_main_window);
    dxball_window_set_focus(dxball_main_window);
    dxball_window_show_window(dxball_main_window, 0);
    dxball_prepare_sound(dxball_main_window);
    dxball_window_show_window(dxball_main_window, 5);
    result = dxball_direct_draw_create(NULL, &dxball_direct_draw, NULL);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_compatible_factory_message,
            dxball_compatible_factory_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    result = ((DxBallSetCooperativeLevel)dxball_direct_draw->vtable->slots_7_to_21[13])(
        dxball_direct_draw, dxball_main_window, 8);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_compatible_cooperative_message,
            dxball_compatible_cooperative_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    dxball_draw_to_primary = 1;
    dxball_display_buffer_count = 0;
    caps.size = 316;
    result = ((DxBallGetCaps)dxball_direct_draw->vtable->slots_7_to_21[4])(
        dxball_direct_draw, &caps, NULL);
    if ((caps.caps & 0x02000000UL) != 0) {
        dxball_software_only = 1;
    } else {
        dxball_software_only = 0;
    }
    surface.size = 108;
    surface.flags = 1;
    surface.caps = 0x200;
    result = dxball_direct_draw->vtable->create_surface(
        dxball_direct_draw, &surface, &dxball_primary_surface, NULL);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_compatible_primary_message,
            dxball_compatible_primary_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    surface.flags = 7;
    surface.caps = 0x40;
    surface.height = 480;
    surface.width = 640;
    result = dxball_direct_draw->vtable->create_surface(
        dxball_direct_draw, &surface, &dxball_board_surface, NULL);
    if (result != 0) {
        dxball_window_show_window(dxball_main_window, 0);
        dxball_window_message_box(dxball_main_window, dxball_compatible_board_message,
            dxball_compatible_board_title, 0);
        dxball_window_destroy_window(dxball_main_window);
        return 0;
    }
    if (dxball_clip_regions == 1) {
        result = ((DxBallCreateClipper)dxball_direct_draw->vtable->slots_0_to_4[4])(
            dxball_direct_draw, 0, &dxball_direct_clipper, NULL);
        if (result != 0) {
            dxball_window_show_window(dxball_main_window, 0);
            dxball_window_message_box(dxball_main_window, dxball_compatible_clipper_message,
                dxball_compatible_clipper_title, 0);
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
        result = dxball_direct_clipper->vtable->set_window(
            dxball_direct_clipper, 0, dxball_main_window);
        if (result != 0) {
            dxball_window_show_window(dxball_main_window, 0);
            dxball_window_message_box(dxball_main_window, dxball_compatible_clip_window_message,
                dxball_compatible_clip_window_title, 0);
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
        result = ((DxBallSetClipper)dxball_primary_surface->vtable->set_clipper)(
            dxball_primary_surface, dxball_direct_clipper);
        if (result != 0) {
            dxball_window_show_window(dxball_main_window, 0);
            dxball_window_message_box(dxball_main_window, dxball_compatible_primary_clipper_message,
                dxball_compatible_primary_clipper_title, 0);
            dxball_window_destroy_window(dxball_main_window);
            return 0;
        }
    }
    dxball_initialize_sprite_banks();
    dxball_select_surface((DxBallSurface)dxball_primary_surface);
    return 1;
}

/* FUNCTION: DXBALL 0x0040DF10 */
DxBallHandle dxball_claim_instance(void)
{
    DxBallSecurityAttributes attributes;
    DxBallHandle opened;
    attributes.length = 12; attributes.descriptor = NULL; attributes.inherit = 1;
    opened = dxball_window_open_semaphore(2, 0, dxball_semaphore_open_name);
    if (opened == 0) {
        dxball_instance_semaphore = dxball_window_create_semaphore(
            &attributes, 0, 1, dxball_semaphore_create_name);
        return dxball_instance_semaphore;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x0040DF80 */
void dxball_close_instance(void)
{
    if (dxball_instance_semaphore != 0) {
        dxball_file_close(dxball_instance_semaphore);
        dxball_instance_semaphore = 0;
    }
    return;
}

void dxball_detect_clock(void)
{
    DxBallVersionInfo version;
    memset(&version, 0, sizeof(version)); version.size = 148;
    dxball_window_get_version_ex(&version);
    dxball_high_resolution_clock = version.platform != 1;
}

const char dxball_instance_running_title[] = "DX-Ball";
const char dxball_instance_running_message[] = "DX-Ball is already running.";

/* FUNCTION: DXBALL 0x0040D930 */
DxBallHandle DXBALL_DDCALL dxball_win_main(DxBallHandle instance,
    DxBallHandle previous, DxBallHandle command_line, DxBallInt show)
{
    DxBallMessage message;
    DxBallInt initialized;
    (void)previous;
    (void)command_line;
    if (dxball_claim_instance() == 0) {
        dxball_window_message_box(0, dxball_instance_running_message,
            dxball_instance_running_title, 0);
        dxball_process_exit(0);
    }
    if (dxball_cursor_warp_disabled != 0) {
        initialized = dxball_initialize_compatible(instance, show);
    } else {
        initialized = dxball_initialize_fullscreen(instance, show);
    }
    if (initialized == 0) return 0;
    dxball_detect_clock();
    dxball_initialize_trig();
    dxball_control_pressed = 0;
    dxball_shift_pressed = 0;
    dxball_window_get_cursor_pos(&dxball_cursor_point);
    dxball_mouse_x = dxball_cursor_point.x;
    dxball_mouse_y = dxball_cursor_point.y;
    dxball_mouse_action = 0;
    for (;;) {
        if (dxball_window_peek_message(&message, 0, 0, 0, 0) != 0) {
            if (dxball_window_get_message(&message, 0, 0, 0) == 0)
                return message.wparam;
            dxball_window_translate_message(&message);
            dxball_window_dispatch_message(&message);
        } else {
            if (dxball_application_active != 0)
                dxball_dispatch_frame();
            else
                dxball_window_wait_message();
        }
    }
}

void dxball_initialize_sprite_banks(void)
{
    DxBallInt bank, slot;
    for (bank = 0; bank < 3; ++bank) {
        dxball_sprite_banks[bank].count = 0;
        slot = 0;
        while (slot <= 254) {
            dxball_sprite_banks[bank].sprites[slot] = NULL;
            ++slot;
        }
    }
    return;
}

void dxball_dispose_working_surface(DxBallInt fade)
{
    DxBallDDSurface *background;
    if (dxball_device_reset_requested != 0) dxball_cleanup_mode(fade);
    background = (DxBallDDSurface *)dxball_background_surface;
    if (background != NULL) {
        background->vtable->release(background);
        dxball_background_surface = 0;
    }
}

void dxball_dispatch_key(char key)
{
    if (dxball_display_mode >= 0 && dxball_display_mode < 4)
        dxball_key_mode_ops.mode[dxball_display_mode](key);
    else if (dxball_display_mode == 4) dxball_key_mode_ops.mode4();
}

void dxball_game_key(char key)
{
    static const char *const music[6] = {
        "12flight.mds", "acker-gs.mds", "brain.mds", "ethno_pa.mds", "freebee.mds", "gmfigaro.mds"
    };
    DxBallInt choice;
    if (dxball_paused == 1) {
        dxball_paused = 0;
        if (dxball_restart_requested == 0) dxball_palette_transition(1, 10, 0, 255, 0);
        dxball_redraw_mode(); dxball_palette_transition(1, 10, 0, 255, 1);
    } else {
        switch (key) {
        case 'P':
            if (dxball_paused == 0) {
                dxball_paused = 1;
                if (dxball_restart_requested == 0) dxball_palette_transition(1, 10, 0, 255, 0);
                dxball_redraw_mode(); dxball_palette_transition(1, 10, 0, 255, 1);
            }
            break;
        case 0x70:
            if (dxball_control_pressed != 0) {
                dxball_bonus_9_active = 0; dxball_bonus_8_active = 0;
                dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[68]->width;
            }
            break;
        case 0x71: if (dxball_control_pressed != 0) dxball_bonus_9_active = 1; break;
        case 0x72: if (dxball_control_pressed != 0) dxball_bonus_8_active = 1; break;
        case 0x73:
            if (dxball_control_pressed != 0)
                dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[68]->width * 2;
            break;
        case 0x74:
            choice = dxball_gameplay_ops.random_range(6);
            dxball_platform_ops.close_music();
            if (choice >= 0 && choice < 6) dxball_platform_ops.load_music(music[choice], 1);
            break;
        case 0x75: dxball_platform_ops.close_music(); break;
        case 0x7b: dxball_pan_scale = dxball_pan_scale * -1.0; break;
        default: break;
        }
    }
}

DxBallWindowResult DXBALL_DDCALL dxball_window_proc(DxBallHandle window,
    DxBallUInt message, DxBallHandle wparam, DxBallWindowResult lparam)
{
    DxBallDDSurface *surface;
    switch (message) {
    case 1: case 0x14: break;
    case 2:
        dxball_dispose_working_surface(0);
        dxball_platform_ops.release_audio(); dxball_platform_ops.close_music();
        if (dxball_direct_draw != NULL) {
            dxball_runtime_ops.release_sprite_banks();
            surface = (DxBallDDSurface *)dxball_board_surface;
            if (surface != NULL) { surface->vtable->release(surface); dxball_board_surface = 0; }
            surface = (DxBallDDSurface *)dxball_primary_surface;
            if (surface != NULL) {
                surface->vtable->release(surface); dxball_primary_surface = 0; dxball_secondary_surface = 0;
            }
            if (dxball_direct_palette != NULL) {
                ((DxBallReleasePalette)dxball_direct_palette->vtable->slots_0_to_5[2])(dxball_direct_palette); dxball_direct_palette = NULL;
            }
            dxball_direct_draw = NULL;
        }
        dxball_close_instance(); dxball_window_post_quit_message((DxBallInt)wparam);
        break;
    case 7:
        dxball_sound_suspended = 0;
        if (dxball_direct_draw != NULL) dxball_platform_ops.initialize_sound(window);
        dxball_platform_ops.resume_music(); break;
    case 8:
        if (dxball_sound_suspended == 0) dxball_platform_ops.pause_sound();
        dxball_platform_ops.pause_music(); dxball_surface_restore_requested = 1; break;
    case 0x1c:
        dxball_application_active = (DxBallInt)wparam;
        dxball_control_pressed = dxball_shift_pressed = 0; break;
    case 0x20: dxball_window_set_cursor(0); return 1;
    case 0x48:
        if (wparam == 1) dxball_sound_suspended = 1;
        if (wparam == 3 || wparam == 2) dxball_sound_suspended = 0;
        break;
    case 0x100:
        if (wparam == 0x1b) {
            if (dxball_display_mode == 0) {
                dxball_cleanup_mode(1); dxball_window_post_message(window, 0x10, 0, 0);
            } else { dxball_end_requested = 1; dxball_return_to_menu = 0; }
        } else dxball_dispatch_key((char)wparam);
        if (wparam == 0x11) dxball_control_pressed = 1;
        if (wparam == 0x10) dxball_shift_pressed = 1;
        break;
    case 0x101:
        if (wparam == 0x11) dxball_control_pressed = 0;
        if (wparam == 0x10) dxball_shift_pressed = 0;
        break;
    case 0x200:
        dxball_window_get_cursor_pos(&dxball_cursor_point);
        dxball_mouse_x = dxball_cursor_point.x; dxball_mouse_y = dxball_cursor_point.y;
        return dxball_window_default_window_proc(window, message, wparam, lparam);
    case 0x201: dxball_window_set_capture(window); dxball_mouse_action = 1; break;
    case 0x202: case 0x205: dxball_window_release_capture(); dxball_mouse_action = 0; break;
    case 0x204: dxball_window_set_capture(window); dxball_mouse_action = 2; break;
    case 0x218:
        if (wparam == 0 || wparam == 4) dxball_sound_suspended = 1;
        if (wparam == 2 || wparam == 6 || wparam == 7) dxball_sound_suspended = 0;
        break;
    case 0x311:
        if (dxball_direct_draw != NULL && dxball_primary_surface != 0 && dxball_device_reset_requested == 0)
            dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, 0, 256, dxball_live_palette);
        break;
    default: return dxball_window_default_window_proc(window, message, wparam, lparam);
    }
    return 0;
}
