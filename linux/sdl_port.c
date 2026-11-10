#include <unistd.h>
#include "midi.h"
#include "gameplay.h"
#include "boards.h"
#include "core.h"
#include <SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resources.h"
#include "platform.h"
#include "sound.h"
#include "display.h"
#include "paddle.h"
#include "clock_api.h"
#include "raster_host.h"
#include "file.h"
#include "memory.h"
DxBallInt dxball_sdl_sound_create(void *, DxBallSoundDevice **, void *);
void dxball_sdl_sound_close(void);

typedef struct NativeSurface {
    const DxBallDDSurfaceVTable *vtable;
    int width, height, pitch;
    uint8_t *pixels;
    struct NativeSurface *attached;
    DxBallDDPalette *palette;
} NativeSurface;
typedef struct NativePalette {
    const DxBallDDPaletteVTable *vtable;
    DxBallPaletteEntry colors[256];
} NativePalette;
typedef struct NativeDraw { const DxBallDDrawVTable *vtable; } NativeDraw;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static uint32_t rgba[640 * 480];
static NativeDraw draw_device;
static NativePalette *current_palette;
static DxBallWindowProc game_proc;
static int running = 1;
static int mouse_confined = 1;
static Uint32 cheat_notice_until;
static const char *cheat_notice_title;

static NativeSurface *as_surface(DxBallDDSurface *surface) { return (NativeSurface *)surface; }
static DxBallUInt surface_release(DxBallDDSurface *surface) {
    NativeSurface *item = as_surface(surface);
    if (item->attached) surface_release((DxBallDDSurface *)item->attached);
    free(item->pixels);
    free(item);
    return 0;
}
static DxBallInt surface_desc(DxBallDDSurface *surface, DxBallSurfaceDesc *desc) {
    NativeSurface *item = as_surface(surface);
    desc->width = item->width;
    desc->height = item->height;
    desc->pitch = item->pitch;
    desc->pixels = item->pixels;
    return 0;
}
static DxBallInt surface_lock(DxBallDDSurface *surface, DxBallRect *rect, DxBallSurfaceDesc *desc, DxBallUInt flags, void *event) {
    (void)rect; (void)flags; (void)event;
    return surface_desc(surface, desc);
}
static DxBallInt surface_ok(DxBallDDSurface *surface) { (void)surface; return 0; }
static DxBallInt surface_unlock(DxBallDDSurface *surface, void *ptr) { (void)surface; (void)ptr; return 0; }
static DxBallInt surface_status(DxBallDDSurface *surface, DxBallUInt flags) { (void)surface; (void)flags; return 0; }
static DxBallInt surface_key(DxBallDDSurface *surface, DxBallUInt flags, DxBallColorKey *key) { (void)surface; (void)flags; (void)key; return 0; }
static DxBallInt surface_palette(DxBallDDSurface *surface, DxBallDDPalette *palette) {
    as_surface(surface)->palette = palette;
    current_palette = (NativePalette *)palette;
    return 0;
}
static void copy_pixels(NativeSurface *dst, DxBallRect target, NativeSurface *src, DxBallRect source, int keyed) {
    int tw = target.right - target.left, th = target.bottom - target.top;
    int sw = source.right - source.left, sh = source.bottom - source.top;
    if (tw <= 0 || th <= 0 || sw <= 0 || sh <= 0) return;
    for (int y = 0; y < th; ++y) {
        int dy = target.top + y, sy = source.top + (int)((int64_t)y * sh / th);
        if (dy < 0 || dy >= dst->height || sy < 0 || sy >= src->height) continue;
        for (int x = 0; x < tw; ++x) {
            int dx = target.left + x, sx = source.left + (int)((int64_t)x * sw / tw);
            if (dx < 0 || dx >= dst->width || sx < 0 || sx >= src->width) continue;
            uint8_t value = src->pixels[sy * src->pitch + sx];
            if (!keyed || value != 0) dst->pixels[dy * dst->pitch + dx] = value;
        }
    }
}
static DxBallInt surface_blt(DxBallDDSurface *destination, DxBallRect *target,
    DxBallDDSurface *source, DxBallRect *source_rect, DxBallUInt flags, void *effect) {
    NativeSurface *dst = as_surface(destination);
    DxBallRect dst_rect = target ? *target : (DxBallRect){0, 0, dst->width, dst->height};
    if (flags & 0x400) {
        uint8_t color = effect ? (uint8_t)((DxBallUInt *)effect)[20] : 0;
        for (int y = dst_rect.top; y < dst_rect.bottom; ++y)
            if (y >= 0 && y < dst->height)
                for (int x = dst_rect.left; x < dst_rect.right; ++x)
                    if (x >= 0 && x < dst->width) dst->pixels[y * dst->pitch + x] = color;
        return 0;
    }
    if (!source) return 0;
    NativeSurface *src = as_surface(source);
    DxBallRect src_rect = source_rect ? *source_rect : (DxBallRect){0, 0, src->width, src->height};
    copy_pixels(dst, dst_rect, src, src_rect, (flags & 0x8000) != 0);
    return 0;
}
static DxBallInt surface_blt_fast(DxBallDDSurface *destination, DxBallUInt x, DxBallUInt y,
    DxBallDDSurface *source, DxBallRect *source_rect, DxBallUInt flags) {
    NativeSurface *src = as_surface(source);
    DxBallRect sr = source_rect ? *source_rect : (DxBallRect){0, 0, src->width, src->height};
    DxBallRect dr = {(int)x, (int)y, (int)x + sr.right - sr.left, (int)y + sr.bottom - sr.top};
    copy_pixels(as_surface(destination), dr, src, sr, (flags & 0x1) != 0);
    return 0;
}
static DxBallInt surface_attached(DxBallDDSurface *surface, const DxBallUInt *caps, DxBallDDSurface **out) {
    (void)caps;
    *out = (DxBallDDSurface *)as_surface(surface)->attached;
    return *out ? 0 : -1;
}
static DxBallInt surface_flip(DxBallDDSurface *surface, DxBallDDSurface *other, DxBallUInt flags) {
    (void)other; (void)flags;
    NativeSurface *front = as_surface(surface);
    if (front->attached) {
        uint8_t *pixels = front->pixels;
        front->pixels = front->attached->pixels;
        front->attached->pixels = pixels;
    }
    return 0;
}
static const DxBallDDSurfaceVTable surface_methods = {
    .release = surface_release, .blt = surface_blt, .blt_fast = surface_blt_fast,
    .flip = surface_flip, .slot_12 = (DxBallUnknownDDMethod)surface_attached,
    .get_blt_status = surface_status, .get_desc = surface_desc,
    .is_lost = (DxBallUnknownDDMethod)surface_ok, .lock = surface_lock,
    .restore = surface_ok, .set_color_key = surface_key,
    .set_palette = surface_palette, .unlock = surface_unlock
};
static DxBallUInt palette_release(DxBallDDPalette *palette) { free(palette); current_palette = NULL; return 0; }
static DxBallInt palette_set(DxBallDDPalette *palette, DxBallUInt flags, DxBallUInt start,
    DxBallUInt count, DxBallPaletteEntry *entries) {
    (void)flags;
    if (start > 256 || count > 256 - start) return -1;
    memcpy(((NativePalette *)palette)->colors + start, entries, count * sizeof(*entries));
    return 0;
}
static const DxBallDDPaletteVTable palette_methods = {
    .slots_0_to_5 = {[2] = (DxBallUnknownDDMethod)palette_release},
    .set_entries = palette_set
};
static DxBallInt create_palette(DxBallDDraw *draw, DxBallUInt flags,
    DxBallPaletteEntry *entries, DxBallDDPalette **out, void *outer) {
    (void)draw; (void)flags; (void)outer;
    NativePalette *palette = calloc(1, sizeof(*palette));
    if (!palette) return -1;
    palette->vtable = &palette_methods;
    if (entries) memcpy(palette->colors, entries, sizeof(palette->colors));
    *out = (DxBallDDPalette *)palette;
    current_palette = palette;
    return 0;
}
static NativeSurface *new_surface(int width, int height) {
    NativeSurface *surface = calloc(1, sizeof(*surface));
    if (!surface) return NULL;
    surface->pixels = calloc((size_t)width * height, 1);
    if (!surface->pixels) { free(surface); return NULL; }
    surface->vtable = &surface_methods;
    surface->width = surface->pitch = width;
    surface->height = height;
    return surface;
}
static DxBallInt create_surface(DxBallDDraw *draw, DxBallSurfaceDesc *desc,
    DxBallDDSurface **out, void *outer) {
    (void)draw; (void)outer;
    int width = (desc->flags & 0x4) ? (int)desc->width : 640;
    int height = (desc->flags & 0x2) ? (int)desc->height : 480;
    if (width <= 0 || height <= 0 || width > 4096 || height > 4096) return -1;
    NativeSurface *surface = new_surface(width, height);
    if (!surface) return -1;
    if (desc->caps & 0x200 && desc->caps & 0x18) {
        surface->attached = new_surface(width, height);
        if (!surface->attached) { surface_release((DxBallDDSurface *)surface); return -1; }
    }
    *out = (DxBallDDSurface *)surface;
    return 0;
}
static DxBallInt draw_caps(DxBallDDraw *draw, void *caps, void *hal) {
    (void)draw; (void)hal;
    DxBallDrawCaps *record = (DxBallDrawCaps *)caps;
    record->caps = 0;
    record->free_video_memory = 16 * 1024 * 1024;
    return 0;
}
static DxBallInt draw_cooperative(DxBallDDraw *draw, size_t handle, DxBallUInt flags) {
    (void)draw; (void)handle; (void)flags; return 0;
}
static DxBallInt draw_mode(DxBallDDraw *draw, DxBallUInt width, DxBallUInt height, DxBallUInt depth) {
    (void)draw; return width == 640 && height == 480 && depth == 8 ? 0 : -1;
}
static DxBallInt vertical_blank(DxBallDDraw *draw, DxBallUInt flags, void *event) {
    (void)draw; (void)flags; (void)event; SDL_Delay(1); return 0;
}
static const DxBallDDrawVTable draw_methods = {
    .create_palette = create_palette, .create_surface = create_surface,
    .slots_7_to_21 = {[4] = (DxBallUnknownDDMethod)draw_caps,
        [13] = (DxBallUnknownDDMethod)draw_cooperative,
        [14] = (DxBallUnknownDDMethod)draw_mode},
    .wait_vertical_blank = vertical_blank
};
static DxBallInt create_draw(void *guid, DxBallDDraw **out, void *outer) {
    (void)guid; (void)outer; *out = (DxBallDDraw *)&draw_device; return 0;
}
static void present(void) {
    if (!renderer || !texture || !dxball_primary_surface || !current_palette) return;
    const char *title = cheat_notice_title &&
        (int32_t)(SDL_GetTicks() - cheat_notice_until) < 0 ? cheat_notice_title :
        (dxball_destroy_hard_tiles ? "DX-Ball | Pierce ON" : "DX-Ball");
    if (strcmp(SDL_GetWindowTitle(window), title) != 0) SDL_SetWindowTitle(window, title);
    NativeSurface *front = as_surface(dxball_primary_surface);
    for (int y = 0; y < 480; ++y) for (int x = 0; x < 640; ++x) {
        DxBallPaletteEntry color = current_palette->colors[front->pixels[y * front->pitch + x]];
        rgba[y * 640 + x] = 0xff000000u | ((uint32_t)color.red << 16) |
            ((uint32_t)color.green << 8) | color.blue;
    }
    SDL_UpdateTexture(texture, NULL, rgba, 640 * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
static DxBallMessage messages[64];
static int message_head, message_tail;
static Uint32 mouse_press_at, mouse_release_at;
static DxBallUInt mouse_release_kind;
static void push_message(DxBallUInt kind, DxBallHandle wparam, DxBallWindowResult lparam) {
    int next = (message_tail + 1) % 64;
    if (next == message_head) return;
    DxBallMessage *message = &messages[message_tail];
    memset(message, 0, sizeof(*message));
    message->window = (DxBallHandle)window;
    message->message = kind;
    message->wparam = wparam;
    message->lparam = lparam;
    message_tail = next;
}
static void toggle_mouse_capture(void) {
    mouse_confined = !mouse_confined;
    SDL_SetWindowGrab(window, mouse_confined ? SDL_TRUE : SDL_FALSE);
    SDL_ShowCursor(mouse_confined ? SDL_DISABLE : SDL_ENABLE);
}
static void activate_cheat(int slot) {
    static const char *const notices[] = {
        NULL, "DX-Ball | Cheat 1 applied", "DX-Ball | Cheat 2 applied",
        "DX-Ball | Cheat 3 applied", "DX-Ball | Cheat 4 applied"
    };
    if (dxball_display_mode != 1 || dxball_paused != 0) return;
    if (slot == 5) {
        dxball_destroy_hard_tiles = 1;
        cheat_notice_until = 0;
        return;
    }
    if (slot < 1 || slot > 4) return;
    DxBallInt previous_control = dxball_control_pressed;
    dxball_control_pressed = 1;
    dxball_game_key((char)(0x6f + slot));
    dxball_control_pressed = previous_control;
    cheat_notice_title = notices[slot];
    cheat_notice_until = SDL_GetTicks() + 2000;
}
static DxBallUInt virtual_key(SDL_Keycode key) {
    if (key >= SDLK_a && key <= SDLK_z) return (DxBallUInt)('A' + key - SDLK_a);
    if (key >= SDLK_0 && key <= SDLK_9) return (DxBallUInt)key;
    if (key >= SDLK_F1 && key <= SDLK_F12) return 0x70 + (DxBallUInt)(key - SDLK_F1);
    switch (key) {
    case SDLK_LCTRL: case SDLK_RCTRL: return 0x11;
    case SDLK_LSHIFT: case SDLK_RSHIFT: return 0x10;
    case SDLK_ESCAPE: return 0x1b;
    case SDLK_SPACE: return ' ';
    case SDLK_BACKSPACE: return 8;
    case SDLK_RETURN: return 0x0d;
    case SDLK_EQUALS: case SDLK_PLUS: case SDLK_KP_PLUS: return 0xbb;
    case SDLK_MINUS: case SDLK_KP_MINUS: return 0xbd;
    case SDLK_LEFT: return 0x25;
    case SDLK_UP: return 0x26;
    case SDLK_RIGHT: return 0x27;
    case SDLK_DOWN: return 0x28;
    default: return 0;
    }
}
static void collect_events(void) {
    SDL_Event event;
    if (mouse_release_kind && (int32_t)(SDL_GetTicks() - mouse_release_at) >= 0) {
        push_message(mouse_release_kind, 0, 0);
        mouse_release_kind = 0;
    }
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: push_message(0x10, 0, 0); break;
        case SDL_KEYDOWN:
            if (event.key.repeat) break;
            if (event.key.keysym.sym == SDLK_F12) {
                toggle_mouse_capture();
                break;
            }
            if ((event.key.keysym.mod & KMOD_CTRL) && (event.key.keysym.mod & KMOD_SHIFT) &&
                (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL ||
                 event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)) {
                toggle_mouse_capture();
            }
            if (event.key.keysym.mod & KMOD_CTRL) {
                if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_5) {
                    activate_cheat((int)(event.key.keysym.sym - SDLK_0));
                    break;
                }
                if (event.key.keysym.sym == SDLK_F5) {
                    activate_cheat(5);
                    break;
                }
            }
            if (virtual_key(event.key.keysym.sym))
                push_message(0x100, virtual_key(event.key.keysym.sym), 0);
            break;
        case SDL_KEYUP:
            if (virtual_key(event.key.keysym.sym))
                push_message(0x101, virtual_key(event.key.keysym.sym), 0);
            break;
        case SDL_MOUSEMOTION: push_message(0x200, 0, 0); break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_press_at = SDL_GetTicks();
            if (event.button.button == SDL_BUTTON_LEFT) push_message(0x201, 0, 0);
            if (event.button.button == SDL_BUTTON_RIGHT) push_message(0x204, 0, 0);
            break;
        case SDL_MOUSEBUTTONUP: {
            DxBallUInt kind = event.button.button == SDL_BUTTON_LEFT ? 0x202 :
                event.button.button == SDL_BUTTON_RIGHT ? 0x205 : 0;
            if (kind && SDL_GetTicks() - mouse_press_at < 30) {
                mouse_release_kind = kind;
                mouse_release_at = SDL_GetTicks() + 30;
            } else if (kind) push_message(kind, 0, 0);
            break;
        }
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) push_message(0x1c, 1, 0);
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) push_message(0x1c, 0, 0);
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) push_message(0x10, 0, 0);
            break;
        default: break;
        }
    }
}
static DxBallInt cursor_position(DxBallPoint *point) {
    int x, y;
    float logical_x, logical_y;
    SDL_GetMouseState(&x, &y);
    SDL_RenderWindowToLogical(renderer, x, y, &logical_x, &logical_y);
    point->x = (DxBallInt)logical_x;
    point->y = (DxBallInt)logical_y;
    return 1;
}
static DxBallInt set_cursor_position(DxBallInt x, DxBallInt y) {
    int window_x, window_y;
    if (!mouse_confined) return 1;
    SDL_RenderLogicalToWindow(renderer, x, y, &window_x, &window_y);
    SDL_WarpMouseInWindow(window, window_x, window_y);
    return 1;
}
static DxBallInt peek_message(DxBallMessage *message, DxBallHandle window_handle,
    DxBallUInt first, DxBallUInt last, DxBallUInt remove) {
    (void)message; (void)window_handle; (void)first; (void)last; (void)remove;
    present();
    collect_events();
    return message_head != message_tail;
}
static DxBallInt get_message(DxBallMessage *message, DxBallHandle window_handle,
    DxBallUInt first, DxBallUInt last) {
    (void)window_handle; (void)first; (void)last;
    if (message_head == message_tail) return 1;
    *message = messages[message_head];
    message_head = (message_head + 1) % 64;
    return message->message == 0x12 ? 0 : 1;
}
static DxBallInt wait_message(void) { SDL_Delay(10); collect_events(); return 1; }
static DxBallInt translate_message(const DxBallMessage *message) { (void)message; return 1; }
static DxBallWindowResult dispatch_message(const DxBallMessage *message) {
    return game_proc(message->window, message->message, message->wparam, message->lparam);
}
static DxBallWindowResult default_proc(DxBallHandle handle, DxBallUInt kind,
    DxBallHandle wparam, DxBallWindowResult lparam) {
    (void)handle; (void)wparam; (void)lparam;
    if (kind == 0x10) push_message(2, 0, 0);
    return 0;
}
static DxBallInt post_message(DxBallHandle handle, DxBallUInt kind,
    DxBallHandle wparam, DxBallWindowResult lparam) {
    (void)handle; push_message(kind, wparam, lparam); return 1;
}
static void post_quit(DxBallInt result) { push_message(0x12, (DxBallHandle)result, 0); running = 0; }
static DxBallHandle load_icon(DxBallHandle instance, DxBallHandle name) { (void)instance; (void)name; return 1; }
static DxBallHandle stock_object(DxBallInt number) { (void)number; return 1; }
static DxBallUInt register_class(const DxBallWindowClass *klass) { game_proc = klass->procedure; return 1; }
static DxBallHandle create_window(DxBallUInt ex, const char *klass, const char *title,
    DxBallUInt style, DxBallInt x, DxBallInt y, DxBallInt width, DxBallInt height,
    DxBallHandle parent, DxBallHandle menu, DxBallHandle instance, void *param) {
    (void)ex; (void)klass; (void)style; (void)x; (void)y; (void)width; (void)height;
    (void)parent; (void)menu; (void)instance; (void)param;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 960, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if (!window) return 0;
    SDL_SetWindowGrab(window, SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) return 0;
    SDL_RenderSetLogicalSize(renderer, 640, 480);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, 640, 480);
    return texture ? (DxBallHandle)window : 0;
}
static DxBallInt show_window(DxBallHandle handle, DxBallInt show) {
    (void)handle; if (show) SDL_ShowWindow(window); else SDL_HideWindow(window); return 1;
}
static DxBallInt update_window(DxBallHandle handle) { (void)handle; present(); return 1; }
static DxBallHandle set_focus(DxBallHandle handle) { SDL_RaiseWindow(window); return handle; }
static DxBallInt destroy_window(DxBallHandle handle) { (void)handle; push_message(2, 0, 0); return 1; }
static DxBallInt message_box(DxBallHandle handle, const char *message, const char *title, DxBallUInt flags) {
    (void)handle; (void)flags;
    fprintf(stderr, "%s: %s\n", title, message);
    return 6;
}
static DxBallHandle set_cursor(DxBallHandle handle) { (void)handle; return 0; }
static DxBallHandle set_capture(DxBallHandle handle) { (void)handle; return 0; }
static DxBallInt release_capture(void) { return 1; }
static DxBallHandle open_semaphore(DxBallUInt access, DxBallInt inherit, const char *name) {
    (void)access; (void)inherit; (void)name; return 0;
}
static DxBallHandle create_semaphore(const DxBallSecurityAttributes *attr,
    DxBallInt initial, DxBallInt maximum, const char *name) {
    (void)attr; (void)initial; (void)maximum; (void)name; return 1;
}
static DxBallInt version_info(DxBallVersionInfo *version) {
    version->major = 6; version->minor = 1; version->platform = 2; return 1;
}
static DxBallUInt time_ms(void) { return SDL_GetTicks(); }
static DxBallInt counter_frequency(DxBallCounter *counter) {
    uint64_t value = SDL_GetPerformanceFrequency();
    counter->low = (DxBallUInt)value; counter->high = (DxBallInt)(value >> 32); return 1;
}
static DxBallInt counter_now(DxBallCounter *counter) {
    uint64_t value = SDL_GetPerformanceCounter();
    counter->low = (DxBallUInt)value; counter->high = (DxBallInt)(value >> 32); return 1;
}
static DxBallInt muldiv(DxBallInt value, DxBallInt factor, DxBallInt divisor) {
    return divisor ? (DxBallInt)((int64_t)value * factor / divisor) : 0;
}
static DxBallHandle file_create(const char *path, DxBallUInt access, DxBallUInt share,
    void *security, DxBallUInt creation, DxBallUInt flags, DxBallHandle template_handle) {
    (void)access; (void)share; (void)security; (void)creation; (void)flags; (void)template_handle;
    FILE *file = fopen(path, "rb");
    return file ? (DxBallHandle)file : (DxBallHandle)-1;
}
static DxBallUInt file_size(DxBallHandle handle, DxBallUInt *high) {
    FILE *file = (FILE *)handle;
    long position = ftell(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, position, SEEK_SET);
    if (high) *high = 0;
    return size >= 0 ? (DxBallUInt)size : (DxBallUInt)-1;
}
static DxBallInt file_read(DxBallHandle handle, void *buffer, DxBallUInt bytes,
    DxBallUInt *read_count, void *overlap) {
    (void)overlap;
    size_t count = fread(buffer, 1, bytes, (FILE *)handle);
    if (read_count) *read_count = (DxBallUInt)count;
    return 1;
}
static DxBallInt file_close(DxBallHandle handle) {
    if (handle != 1 && handle != 0 && handle != (DxBallHandle)-1) fclose((FILE *)handle);
    return 1;
}
static void *local_alloc(DxBallUInt flags, size_t size) { (void)flags; return calloc(1, size); }
static void *local_free(void *pointer) { free(pointer); return NULL; }
static DxBallMidiHandle mapping_unavailable(DxBallMidiHandle file, void *security,
    DxBallUInt protection, DxBallUInt high, DxBallUInt low, const char *name) {
    (void)file; (void)security; (void)protection; (void)high; (void)low; (void)name; return 0;
}
static void bind_linux(void) {
    draw_device.vtable = &draw_methods;
    dxball_draw_factory_backend = create_draw;
    dxball_window_get_cursor_pos = cursor_position;
    dxball_window_peek_message = peek_message;
    dxball_window_wait_message = wait_message;
    dxball_window_get_message = get_message;
    dxball_window_translate_message = translate_message;
    dxball_window_dispatch_message = dispatch_message;
    dxball_window_default_window_proc = default_proc;
    dxball_window_post_message = post_message;
    dxball_window_post_quit_message = post_quit;
    dxball_window_set_cursor = set_cursor;
    dxball_window_set_capture = set_capture;
    dxball_window_release_capture = release_capture;
    dxball_window_get_version_ex = version_info;
    dxball_window_load_icon = load_icon;
    dxball_window_load_cursor = load_icon;
    dxball_window_stock_object = stock_object;
    dxball_window_register_class = register_class;
    dxball_window_create_window_ex = create_window;
    dxball_window_show_window = show_window;
    dxball_window_update_window = update_window;
    dxball_window_set_focus = set_focus;
    dxball_window_destroy_window = destroy_window;
    dxball_window_message_box = message_box;
    dxball_window_open_semaphore = open_semaphore;
    dxball_window_create_semaphore = create_semaphore;
    dxball_clock_ops.time_ms = time_ms;
    dxball_clock_ops.frequency = counter_frequency;
    dxball_clock_ops.counter = counter_now;
    dxball_time_get_time = time_ms;
    dxball_query_performance_frequency = counter_frequency;
    dxball_query_performance_counter = counter_now;
    dxball_set_cursor_position = set_cursor_position;
    dxball_raster_ops.muldiv = muldiv;
    dxball_file_create = file_create;
    dxball_file_size = file_size;
    dxball_file_read = file_read;
    dxball_file_close = file_close;
    dxball_local_alloc = local_alloc;
    dxball_local_free = local_free;
    dxball_midi_create_mapping = mapping_unavailable;
    dxball_sound_api.create_device = dxball_sdl_sound_create;
    dxball_display_buffer_count = 1;
    dxball_clip_regions = 0;
    dxball_wait_vertical_blank = 0;
    dxball_application_active = 1;
}
int main(int argc, char **argv) {
    int verify_music = argc > 1 && strcmp(argv[1], "--verify-music") == 0;
    const char *assets = verify_music ? (argc > 2 ? argv[2] : "build/native/game-data") :
        (argc > 1 ? argv[1] : "build/native/game-data");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    if (chdir(assets) != 0) {
        perror(assets);
        dxball_sdl_sound_close();
        SDL_Quit();
        return 1;
    }
    if (access("intro.pcx", R_OK) != 0 || access("default.bds", R_OK) != 0) {
        fprintf(stderr, "Missing lowercase DX-Ball assets in %s\n", assets);
        dxball_sdl_sound_close();
        SDL_Quit();
        return 1;
    }
    bind_linux();
    if (verify_music) {
        const char *tracks[] = {"12flight.mds", "acker-gs.mds", "brain.mds",
            "ethno_pa.mds", "freebee.mds", "gmfigaro.mds"};
        for (size_t i = 0; i < sizeof(tracks) / sizeof(tracks[0]); ++i) {
            if (!dxball_load_music(tracks[i], 0)) {
                fprintf(stderr, "Cannot decode %s\n", tracks[i]);
                dxball_sdl_sound_close();
                SDL_Quit();
                return 1;
            }
            dxball_close_music();
        }
        puts("Decoded all 6 MDS tracks");
        dxball_sdl_sound_close();
        SDL_Quit();
        return 0;
    }
    int result = (int)dxball_win_main(1, 0, 0, 5);
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    dxball_sdl_sound_close();
    SDL_Quit();
    return result;
}
