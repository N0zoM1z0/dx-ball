#include "platform.h"
#include "paddle.h"
#include "bonuses.h"
#include "round.h"
#include "trig.h"
#include <stdlib.h>
#include <string.h>

DxBallWindowApi dxball_window_api;
DxBallPlatformOps dxball_platform_ops;
DxBallKeyModeOps dxball_key_mode_ops = { {NULL, dxball_game_key, NULL, NULL}, NULL };
DxBallHandle dxball_main_window, dxball_instance_semaphore;
DxBallInt dxball_application_active, dxball_shift_pressed, dxball_control_pressed;
DxBallInt dxball_sound_suspended, dxball_software_only, dxball_low_video_memory;
DxBallPoint dxball_cursor_point;
DxBallDDClipper *dxball_direct_clipper;

static DxBallInt create_game_window(DxBallHandle instance, DxBallInt show)
{
    DxBallWindowClass window_class;
    window_class.style = 3;
    window_class.procedure = dxball_window_proc;
    window_class.class_extra = window_class.window_extra = 0;
    window_class.instance = instance;
    window_class.icon = dxball_window_api.load_icon(instance, 0x7f00);
    window_class.cursor = dxball_window_api.load_cursor(0, 0x7f00);
    window_class.background = dxball_window_api.stock_object(4);
    window_class.menu = window_class.name = "DX-Ball";
    dxball_window_api.register_class(&window_class);
    dxball_main_window = dxball_window_api.create_window_ex(0, "DX-Ball", "DX-Ball",
        0x80000000UL, 0, 0, 640, 480, 0, 0, instance, NULL);
    if (dxball_main_window == 0) return 0;
    dxball_window_api.show_window(dxball_main_window, show);
    dxball_window_api.update_window(dxball_main_window);
    dxball_window_api.set_focus(dxball_main_window);
    dxball_window_api.show_window(dxball_main_window, 0);
    dxball_platform_ops.prepare_sound(dxball_main_window);
    dxball_window_api.show_window(dxball_main_window, 5);
    return 1;
}

static DxBallInt window_failure(const char *message)
{
    if (message != NULL) {
        dxball_window_api.show_window(dxball_main_window, 0);
        dxball_window_api.message_box(dxball_main_window, message, "DX-Ball", 0);
    }
    dxball_window_api.destroy_window(dxball_main_window);
    return 0;
}

DxBallInt dxball_initialize_fullscreen(DxBallHandle instance, DxBallInt show)
{
    DxBallDrawCaps caps;
    DxBallSurfaceDesc surface;
    DxBallDDSurface *primary, *secondary, *working;
    DxBallInt result;
    DxBallUInt attached = 4;
    if (!create_game_window(instance, show)) return 0;
    if (dxball_window_api.direct_draw_create(NULL, &dxball_direct_draw, NULL) != 0)
        return window_failure("Direct X could not initialize. (DX Object failed)");
    if (((DxBallSetCooperativeLevel)dxball_direct_draw->vtable->slots_7_to_21[13])(dxball_direct_draw, dxball_main_window, 0x11) != 0)
        return window_failure("Direct X could not initialize. (Exclusive/Fullscreen failed)");
    if (((DxBallSetDisplayMode)dxball_direct_draw->vtable->slots_7_to_21[14])(dxball_direct_draw, 640, 480, 8) != 0)
        return window_failure("Direct X could not initialize. (640x480 failed)");
    dxball_draw_to_primary = 0;
    memset(&caps, 0, sizeof(caps)); caps.size = 316;
    ((DxBallGetCaps)dxball_direct_draw->vtable->slots_7_to_21[4])(dxball_direct_draw, &caps, NULL);
    dxball_reduced_particles = dxball_software_only = (caps.caps & 0x02000000UL) != 0;
    if (dxball_software_only == 0 && caps.free_video_memory < 310000UL) {
        dxball_reduced_particles = 1; dxball_low_video_memory = 1;
    }
    memset(&surface, 0, sizeof(surface)); surface.size = 108;
    if (dxball_display_buffer_count == 0) { surface.flags = 1; surface.caps = 0x200; }
    else {
        surface.flags = 0x21; surface.caps = 0x218;
        surface.ancillary[0] = (DxBallUInt)dxball_display_buffer_count;
    }
    primary = (DxBallDDSurface *)dxball_primary_surface;
    result = dxball_direct_draw->vtable->create_surface(dxball_direct_draw, &surface, &primary, NULL);
    dxball_primary_surface = (DxBallSurface)primary;
    if (result != 0)
        return window_failure("Direct X could not initialize. (Primary Failed)");
    if (dxball_display_buffer_count != 0) {
        secondary = (DxBallDDSurface *)dxball_secondary_surface;
        result = ((DxBallGetAttachedSurface)primary->vtable->slot_12)(primary, &attached, &secondary);
        dxball_secondary_surface = (DxBallSurface)secondary;
        if (result != 0) return window_failure(NULL);
    }
    surface.flags = 7; surface.caps = 0x40; surface.height = 480; surface.width = 640;
    working = (DxBallDDSurface *)dxball_board_surface;
    result = dxball_direct_draw->vtable->create_surface(dxball_direct_draw, &surface, &working, NULL);
    dxball_board_surface = (DxBallSurface)working;
    if (result != 0)
        return window_failure(NULL);
    if (dxball_clip_regions == 1) {
        if (((DxBallCreateClipper)dxball_direct_draw->vtable->slots_0_to_4[4])(dxball_direct_draw, 0, &dxball_direct_clipper, NULL) != 0)
            return window_failure(NULL);
        if (dxball_direct_clipper->vtable->set_window(dxball_direct_clipper, 0, dxball_main_window) != 0)
            return window_failure(NULL);
        if (((DxBallSetClipper)primary->vtable->set_clipper)(primary, dxball_direct_clipper) != 0)
            return window_failure(NULL);
        secondary = (DxBallDDSurface *)dxball_secondary_surface;
        if (secondary != NULL && ((DxBallSetClipper)secondary->vtable->set_clipper)(secondary, dxball_direct_clipper) != 0)
            return window_failure(NULL);
    }
    dxball_initialize_sprite_banks();
    dxball_select_surface(dxball_primary_surface);
    return 1;
}

DxBallInt dxball_initialize_compatible(DxBallHandle instance, DxBallInt show)
{
    DxBallDrawCaps caps;
    DxBallSurfaceDesc surface;
    DxBallDDSurface *primary, *working;
    DxBallInt result;
    if (!create_game_window(instance, show)) return 0;
    if (dxball_window_api.direct_draw_create(NULL, &dxball_direct_draw, NULL) != 0)
        return window_failure("Direct X could not initialize. (DX Object failed)");
    if (((DxBallSetCooperativeLevel)dxball_direct_draw->vtable->slots_7_to_21[13])(dxball_direct_draw, dxball_main_window, 8) != 0)
        return window_failure("Direct X could not initialize.(Coop Normal failed)");
    dxball_draw_to_primary = 1; dxball_display_buffer_count = 0;
    memset(&caps, 0, sizeof(caps)); caps.size = 316;
    ((DxBallGetCaps)dxball_direct_draw->vtable->slots_7_to_21[4])(dxball_direct_draw, &caps, NULL);
    dxball_software_only = (caps.caps & 0x02000000UL) != 0;
    memset(&surface, 0, sizeof(surface)); surface.size = 108; surface.flags = 1; surface.caps = 0x200;
    primary = (DxBallDDSurface *)dxball_primary_surface;
    result = dxball_direct_draw->vtable->create_surface(dxball_direct_draw, &surface, &primary, NULL);
    dxball_primary_surface = (DxBallSurface)primary;
    if (result != 0)
        return window_failure("Direct X could not initialize. (Primary failed)");
    surface.flags = 7; surface.caps = 0x40; surface.height = 480; surface.width = 640;
    working = (DxBallDDSurface *)dxball_board_surface;
    result = dxball_direct_draw->vtable->create_surface(dxball_direct_draw, &surface, &working, NULL);
    dxball_board_surface = (DxBallSurface)working;
    if (result != 0)
        return window_failure("Direct X could not initialize. (Offscreen failed)");
    if (dxball_clip_regions == 1) {
        if (((DxBallCreateClipper)dxball_direct_draw->vtable->slots_0_to_4[4])(dxball_direct_draw, 0, &dxball_direct_clipper, NULL) != 0)
            return window_failure("Direct X could not initialize.(Clipper failed)");
        if (dxball_direct_clipper->vtable->set_window(dxball_direct_clipper, 0, dxball_main_window) != 0)
            return window_failure("Direct X could not initialize. (Clipper SetHWnd failed)");
        if (((DxBallSetClipper)primary->vtable->set_clipper)(primary, dxball_direct_clipper) != 0)
            return window_failure("Direct X could not initialize. (Clipper->Primary failed)");
    }
    dxball_initialize_sprite_banks();
    dxball_select_surface(dxball_primary_surface);
    return 1;
}

DxBallHandle dxball_claim_instance(void)
{
    DxBallSecurityAttributes attributes;
    attributes.length = 12; attributes.descriptor = NULL; attributes.inherit = 1;
    if (dxball_window_api.open_semaphore(2, 0, "DX-Ball") != 0) return 0;
    dxball_instance_semaphore = dxball_window_api.create_semaphore(&attributes, 0, 1, "DX-Ball");
    return dxball_instance_semaphore;
}

void dxball_close_instance(void)
{
    if (dxball_instance_semaphore != 0) {
        dxball_window_api.close_handle(dxball_instance_semaphore);
        dxball_instance_semaphore = 0;
    }
}

void dxball_detect_clock(void)
{
    DxBallVersionInfo version;
    memset(&version, 0, sizeof(version)); version.size = 148;
    dxball_window_api.get_version_ex(&version);
    dxball_high_resolution_clock = version.platform != 1;
}

DxBallHandle DXBALL_DDCALL dxball_win_main(DxBallHandle instance,
    DxBallHandle previous, DxBallHandle command_line, DxBallInt show)
{
    DxBallMessage message;
    DxBallInt initialized;
    (void)previous; (void)command_line;
    if (dxball_claim_instance() == 0) {
        dxball_window_api.message_box(0, "DX-Ball is already running.", "DX-Ball", 0);
        dxball_platform_ops.exit_process(0);
        abort(); /* The original process-exit boundary cannot return. */
    }
    initialized = dxball_cursor_warp_disabled == 0 ? dxball_initialize_fullscreen(instance, show)
        : dxball_initialize_compatible(instance, show);
    if (initialized == 0) return 0;
    dxball_detect_clock(); dxball_initialize_trig();
    dxball_control_pressed = dxball_shift_pressed = 0;
    dxball_window_api.get_cursor_pos(&dxball_cursor_point);
    dxball_mouse_x = dxball_cursor_point.x; dxball_mouse_y = dxball_cursor_point.y;
    dxball_mouse_action = 0;
    for (;;) {
        while (dxball_window_api.peek_message(&message, 0, 0, 0, 0) == 0) {
            if (dxball_application_active == 0) dxball_window_api.wait_message();
            else dxball_dispatch_frame();
        }
        if (dxball_window_api.get_message(&message, 0, 0, 0) == 0) break;
        dxball_window_api.translate_message(&message);
        dxball_window_api.dispatch_message(&message);
    }
    return message.wparam;
}

void dxball_initialize_sprite_banks(void)
{
    DxBallInt bank, slot;
    for (bank = 0; bank < 3; ++bank) {
        dxball_sprite_banks[bank].count = 0;
        for (slot = 0; slot < 255; ++slot) dxball_sprite_banks[bank].sprites[slot] = NULL;
    }
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
        dxball_close_instance(); dxball_window_api.post_quit_message((DxBallInt)wparam);
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
    case 0x20: dxball_window_api.set_cursor(0); return 1;
    case 0x48:
        if (wparam == 1) dxball_sound_suspended = 1;
        if (wparam == 3 || wparam == 2) dxball_sound_suspended = 0;
        break;
    case 0x100:
        if (wparam == 0x1b) {
            if (dxball_display_mode == 0) {
                dxball_cleanup_mode(1); dxball_window_api.post_message(window, 0x10, 0, 0);
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
        dxball_window_api.get_cursor_pos(&dxball_cursor_point);
        dxball_mouse_x = dxball_cursor_point.x; dxball_mouse_y = dxball_cursor_point.y;
        return dxball_window_api.default_window_proc(window, message, wparam, lparam);
    case 0x201: dxball_window_api.set_capture(window); dxball_mouse_action = 1; break;
    case 0x202: case 0x205: dxball_window_api.release_capture(); dxball_mouse_action = 0; break;
    case 0x204: dxball_window_api.set_capture(window); dxball_mouse_action = 2; break;
    case 0x218:
        if (wparam == 0 || wparam == 4) dxball_sound_suspended = 1;
        if (wparam == 2 || wparam == 6 || wparam == 7) dxball_sound_suspended = 0;
        break;
    case 0x311:
        if (dxball_direct_draw != NULL && dxball_primary_surface != 0 && dxball_device_reset_requested == 0)
            dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, 0, 256, dxball_live_palette);
        break;
    default: return dxball_window_api.default_window_proc(window, message, wparam, lparam);
    }
    return 0;
}
