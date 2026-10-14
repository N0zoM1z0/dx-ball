#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "mac_adapter.h"
#include "platform.h"
#include "sound.h"
#include "file.h"
#include "memory.h"
#include "midi.h"
#include "paddle.h"
#include "raster.h"
#include "bitmap.h"
#include "allocator.h"
#include "clock_api.h"
#include "resources.h"
#include "runtime.h"
#include "boards.h"
#include "core.h"

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Texture *g_texture = NULL;
static DxBallWindowProc g_registered_proc = NULL;
static int g_quit_flag = 0;

/* --- Message Queue FIFO Ring Buffer --- */
#define MSG_QUEUE_SIZE 128
static DxBallMessage s_msg_queue[MSG_QUEUE_SIZE];
static int s_msg_head = 0;
static int s_msg_tail = 0;

static void queue_push(const DxBallMessage *m) {
    int next = (s_msg_tail + 1) % MSG_QUEUE_SIZE;
    if (next != s_msg_head) {
        s_msg_queue[s_msg_tail] = *m;
        s_msg_tail = next;
    }
}

static int queue_peek(DxBallMessage *m, int remove) {
    if (s_msg_head == s_msg_tail) return 0;
    *m = s_msg_queue[s_msg_head];
    if (remove) {
        s_msg_head = (s_msg_head + 1) % MSG_QUEUE_SIZE;
    }
    return 1;
}

static void queue_push_event(const DxBallMessage *m) {
    if (m->message == 0x200) { // WM_MOUSEMOVE
        int idx = s_msg_head;
        while (idx != s_msg_tail) {
            if (s_msg_queue[idx].message == 0x200) {
                s_msg_queue[idx] = *m;
                return;
            }
            idx = (idx + 1) % MSG_QUEUE_SIZE;
        }
    }
    queue_push(m);
}

/* --- Surface Structure --- */
typedef struct MacSurface {
    const DxBallDDSurfaceVTable *vtable;
    DxBallUInt width;
    DxBallUInt height;
    DxBallInt pitch;
    DxBallByte *pixels;
    DxBallUInt color_key;
    int has_color_key;
    struct MacSurface *attached;
} MacSurface;

/* Forward declarations */
static DxBallUInt DXBALL_DDCALL mac_surface_release(DxBallDDSurface *self);
static DxBallInt DXBALL_DDCALL mac_surface_blt(DxBallDDSurface *self, DxBallRect *dst_rect,
                                                 DxBallDDSurface *src, DxBallRect *src_rect,
                                                 DxBallUInt flags, void *fx);
static DxBallInt DXBALL_DDCALL mac_surface_blt_fast(DxBallDDSurface *self, DxBallUInt dx, DxBallUInt dy,
                                                      DxBallDDSurface *src, DxBallRect *src_rect,
                                                      DxBallUInt flags);
static DxBallInt DXBALL_DDCALL mac_surface_flip(DxBallDDSurface *self, DxBallDDSurface *target, DxBallUInt flags);
static DxBallInt DXBALL_DDCALL mac_surface_get_desc(DxBallDDSurface *self, DxBallSurfaceDesc *desc);
static DxBallInt DXBALL_DDCALL mac_surface_lock(DxBallDDSurface *self, DxBallRect *rect,
                                                  DxBallSurfaceDesc *desc, DxBallUInt flags, void *handle);
static DxBallInt DXBALL_DDCALL mac_surface_unlock(DxBallDDSurface *self, void *handle);
static DxBallInt DXBALL_DDCALL mac_surface_set_color_key(DxBallDDSurface *self, DxBallUInt flags, DxBallColorKey *key);
static DxBallInt DXBALL_DDCALL mac_surface_set_palette(DxBallDDSurface *self, DxBallDDPalette *pal);
static DxBallInt DXBALL_DDCALL mac_surface_restore(DxBallDDSurface *self);
static DxBallInt DXBALL_DDCALL mac_surface_get_blt_status(DxBallDDSurface *self, DxBallUInt flags);
static DxBallInt DXBALL_DDCALL mac_surface_get_attached_surface(DxBallDDSurface *self,
                                                               const DxBallUInt *caps,
                                                               DxBallDDSurface **out_surface);
static DxBallInt DXBALL_DDCALL mac_surface_set_clipper(DxBallDDSurface *self, DxBallDDClipper *clipper);

static const DxBallDDSurfaceVTable g_surface_vtable = {
    NULL, NULL, // query_interface, add_ref
    mac_surface_release,
    NULL, NULL, // add_attached_surface, add_overlay_dirty_rect
    mac_surface_blt,
    NULL, // blt_batch
    mac_surface_blt_fast,
    {NULL, NULL, NULL},
    mac_surface_flip,
    (DxBallUnknownDDMethod)mac_surface_get_attached_surface, // slot_12
    mac_surface_get_blt_status,
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    mac_surface_get_desc,
    NULL, NULL, // initialize, is_lost
    mac_surface_lock,
    NULL, // release_dc
    mac_surface_restore,
    (DxBallUnknownDDMethod)mac_surface_set_clipper,
    mac_surface_set_color_key,
    NULL, // set_overlay_position
    mac_surface_set_palette,
    mac_surface_unlock
};

static int s_presented_in_current_frame = 0;

static void mac_pace_60fps(void) {
    static uint64_t s_freq = 0;
    static uint64_t s_last_time = 0;
    if (s_freq == 0) {
        s_freq = SDL_GetPerformanceFrequency();
    }
    if (s_last_time == 0) {
        s_last_time = SDL_GetPerformanceCounter();
        return;
    }

    // Exact 60.0 FPS pacing (16.666667 ms per frame)
    uint64_t target_ticks = (s_freq + 30) / 60;
    uint64_t now = SDL_GetPerformanceCounter();
    if (now > s_last_time) {
        uint64_t elapsed = now - s_last_time;
        if (elapsed < target_ticks) {
            uint64_t remaining = target_ticks - elapsed;
            uint32_t ms = (uint32_t)((remaining * 1000) / s_freq);
            if (ms > 1) {
                SDL_Delay(ms - 1);
            }
            while ((SDL_GetPerformanceCounter() - s_last_time) < target_ticks) {
                // Precision microsecond spin
            }
        }
    }
    s_last_time = SDL_GetPerformanceCounter();
}

static void mac_present_screen_impl(int is_flip) {
    MacSurface *s = (MacSurface *)dxball_primary_surface;
    if (!s || !s->pixels || !g_renderer || !g_texture) return;

    // Convert 8-bit paletted pixels to 32-bit ARGB
    static uint32_t s_argb_buf[640 * 480];
    for (int i = 0; i < 640 * 480; ++i) {
        DxBallByte idx = s->pixels[i];
        DxBallPaletteEntry e = dxball_live_palette[idx];
        s_argb_buf[i] = (0xFFu << 24) | ((uint32_t)e.red << 16) | ((uint32_t)e.green << 8) | (uint32_t)e.blue;
    }

    SDL_UpdateTexture(g_texture, NULL, s_argb_buf, 640 * sizeof(uint32_t));
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);

    if (is_flip) {
        s_presented_in_current_frame = 1;
    }

    const char *autotest = getenv("DXBALL_AUTOTEST");
    if (autotest && atoi(autotest) > 0) {
        static int s_frame_count = 0;
        ++s_frame_count;
        if (s_frame_count == 60) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_KEYDOWN;
            ev.key.keysym.sym = SDLK_SPACE;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 65) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_KEYUP;
            ev.key.keysym.sym = SDLK_SPACE;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 240) {
            SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(s_argb_buf, 640, 480, 32, 640 * 4, SDL_PIXELFORMAT_ARGB8888);
            if (surf) {
                SDL_SaveBMP(surf, "/tmp/dxball_mainmenu.bmp");
                SDL_FreeSurface(surf);
            }
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEBUTTONDOWN;
            ev.button.button = SDL_BUTTON_LEFT;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 245) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEBUTTONUP;
            ev.button.button = SDL_BUTTON_LEFT;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 360) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEBUTTONDOWN;
            ev.button.button = SDL_BUTTON_LEFT;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 365) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEBUTTONUP;
            ev.button.button = SDL_BUTTON_LEFT;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 380) {
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEMOTION;
            ev.motion.x = 0;
            ev.motion.y = 700;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 400) {
            printf("AUTOTEST frame 400 (far left): mouse_x=%d, paddle_x=%d, paddle_width=%d\n",
                   dxball_mouse_x, dxball_paddle_x, dxball_paddle_width);
            fflush(stdout);
            SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(s_argb_buf, 640, 480, 32, 640 * 4, SDL_PIXELFORMAT_ARGB8888);
            if (surf) {
                SDL_SaveBMP(surf, "/tmp/dxball_paddle_left.bmp");
                SDL_FreeSurface(surf);
            }
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_MOUSEMOTION;
            ev.motion.x = 640;
            ev.motion.y = 450;
            SDL_PushEvent(&ev);
        } else if (s_frame_count == 420) {
            printf("AUTOTEST frame 420 (far right): mouse_x=%d, paddle_x=%d, paddle_width=%d\n",
                   dxball_mouse_x, dxball_paddle_x, dxball_paddle_width);
            fflush(stdout);
            SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(s_argb_buf, 640, 480, 32, 640 * 4, SDL_PIXELFORMAT_ARGB8888);
            if (surf) {
                SDL_SaveBMP(surf, "/tmp/dxball_paddle_right.bmp");
                SDL_FreeSurface(surf);
            }
        } else if (s_frame_count == 480) {
            SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(s_argb_buf, 640, 480, 32, 640 * 4, SDL_PIXELFORMAT_ARGB8888);
            if (surf) {
                SDL_SaveBMP(surf, "/tmp/dxball_gameplay_active.bmp");
                SDL_FreeSurface(surf);
            }
        } else if (s_frame_count == 500) {
            SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(s_argb_buf, 640, 480, 32, 640 * 4, SDL_PIXELFORMAT_ARGB8888);
            if (surf) {
                SDL_SaveBMP(surf, "/tmp/dxball_gameplay.bmp");
                SDL_FreeSurface(surf);
            }
            SDL_Event ev;
            memset(&ev, 0, sizeof(ev));
            ev.type = SDL_QUIT;
            SDL_PushEvent(&ev);
        }
    }
}

void mac_present_screen(void) {
    if (s_presented_in_current_frame) {
        s_presented_in_current_frame = 0;
        return;
    }
    mac_present_screen_impl(0);
    mac_pace_60fps();
}

static DxBallUInt DXBALL_DDCALL mac_surface_release(DxBallDDSurface *self) {
    if (!self) return 0;
    MacSurface *s = (MacSurface *)self;
    if (s->pixels) {
        free(s->pixels);
        s->pixels = NULL;
    }
    if (s->attached) {
        mac_surface_release((DxBallDDSurface *)s->attached);
        s->attached = NULL;
    }
    free(s);
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_blt(DxBallDDSurface *self, DxBallRect *dst_rect,
                                                 DxBallDDSurface *src, DxBallRect *src_rect,
                                                 DxBallUInt flags, void *fx)
{
    MacSurface *dst_surf = (MacSurface *)self;
    if (!dst_surf || !dst_surf->pixels) return 0;

    DxBallRect dr = { 0, 0, (DxBallInt)dst_surf->width, (DxBallInt)dst_surf->height };
    if (dst_rect) dr = *dst_rect;

    // Color fill
    if ((flags & 0x00000400) && fx) {
        DxBallColorFillFx *fill = (DxBallColorFillFx *)fx;
        DxBallByte c = (DxBallByte)fill->fill_color;
        int x1 = dr.left < 0 ? 0 : dr.left;
        int y1 = dr.top < 0 ? 0 : dr.top;
        int x2 = dr.right > (DxBallInt)dst_surf->width ? (DxBallInt)dst_surf->width : dr.right;
        int y2 = dr.bottom > (DxBallInt)dst_surf->height ? (DxBallInt)dst_surf->height : dr.bottom;
        if (x2 <= x1 || y2 <= y1) return 0;
        for (int y = y1; y < y2; ++y) {
            memset(dst_surf->pixels + y * dst_surf->pitch + x1, c, x2 - x1);
        }
        return 0;
    }

    if (!src) return 0;
    MacSurface *src_surf = (MacSurface *)src;
    if (!src_surf->pixels) return 0;

    DxBallRect sr = { 0, 0, (DxBallInt)src_surf->width, (DxBallInt)src_surf->height };
    if (src_rect) sr = *src_rect;

    int dw = dr.right - dr.left;
    int dh = dr.bottom - dr.top;
    int sw = sr.right - sr.left;
    int sh = sr.bottom - sr.top;
    if (dw <= 0 || dh <= 0 || sw <= 0 || sh <= 0) return 0;

    int use_key = (flags & 0x00008000) != 0;
    DxBallByte key = (DxBallByte)src_surf->color_key;

    // Direct 1:1 copy
    if (dw == sw && dh == sh) {
        int dst_x = dr.left;
        int dst_y = dr.top;
        int src_x = sr.left;
        int src_y = sr.top;
        int w = dw;
        int h = dh;

        if (dst_x < 0) {
            int clip = -dst_x;
            src_x += clip;
            w -= clip;
            dst_x = 0;
        }
        if (src_x < 0) {
            int clip = -src_x;
            dst_x += clip;
            w -= clip;
            src_x = 0;
        }
        if (dst_y < 0) {
            int clip = -dst_y;
            src_y += clip;
            h -= clip;
            dst_y = 0;
        }
        if (src_y < 0) {
            int clip = -src_y;
            dst_y += clip;
            h -= clip;
            src_y = 0;
        }
        if (dst_x + w > (int)dst_surf->width) {
            w = (int)dst_surf->width - dst_x;
        }
        if (src_x + w > (int)src_surf->width) {
            w = (int)src_surf->width - src_x;
        }
        if (dst_y + h > (int)dst_surf->height) {
            h = (int)dst_surf->height - dst_y;
        }
        if (src_y + h > (int)src_surf->height) {
            h = (int)src_surf->height - src_y;
        }

        if (w <= 0 || h <= 0) return 0;

        for (int y = 0; y < h; ++y) {
            DxBallByte *d = dst_surf->pixels + (dst_y + y) * dst_surf->pitch + dst_x;
            const DxBallByte *s = src_surf->pixels + (src_y + y) * src_surf->pitch + src_x;
            if (use_key) {
                for (int x = 0; x < w; ++x) {
                    if (s[x] != key) d[x] = s[x];
                }
            } else {
                memcpy(d, s, w);
            }
        }
    } else {
        // Stretched blit (used in some paddle / effects)
        for (int dy_i = 0; dy_i < dh; ++dy_i) {
            int y_dst = dr.top + dy_i;
            if (y_dst < 0 || y_dst >= (int)dst_surf->height) continue;
            int sy_i = (dy_i * sh) / dh;
            int y_src = sr.top + sy_i;
            if (y_src < 0 || y_src >= (int)src_surf->height) continue;

            DxBallByte *d = dst_surf->pixels + y_dst * dst_surf->pitch;
            const DxBallByte *s = src_surf->pixels + y_src * src_surf->pitch;

            for (int dx_i = 0; dx_i < dw; ++dx_i) {
                int x_dst = dr.left + dx_i;
                if (x_dst < 0 || x_dst >= (int)dst_surf->width) continue;
                int sx_i = (dx_i * sw) / dw;
                int x_src = sr.left + sx_i;
                if (x_src < 0 || x_src >= (int)src_surf->width) continue;

                DxBallByte pixel = s[x_src];
                if (!use_key || pixel != key) {
                    d[x_dst] = pixel;
                }
            }
        }
    }

    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_blt_fast(DxBallDDSurface *self, DxBallUInt dx, DxBallUInt dy,
                                                      DxBallDDSurface *src, DxBallRect *src_rect,
                                                      DxBallUInt flags)
{
    if (!self || !src) return 0;
    MacSurface *s = (MacSurface *)src;
    DxBallRect sr = { 0, 0, (DxBallInt)s->width, (DxBallInt)s->height };
    if (src_rect) sr = *src_rect;
    DxBallRect dr = { (DxBallInt)dx, (DxBallInt)dy, (DxBallInt)dx + (sr.right - sr.left), (DxBallInt)dy + (sr.bottom - sr.top) };
    return mac_surface_blt(self, &dr, src, &sr, (flags & 1) ? 0x01008000 : 0x01000000, NULL);
}

static DxBallInt DXBALL_DDCALL mac_surface_flip(DxBallDDSurface *self, DxBallDDSurface *target, DxBallUInt flags) {
    (void)self; (void)target; (void)flags;
    MacSurface *pri = (MacSurface *)dxball_primary_surface;
    MacSurface *sec = (MacSurface *)dxball_secondary_surface;
    if (pri && sec && pri->pixels && sec->pixels) {
        void *tmp = pri->pixels;
        pri->pixels = sec->pixels;
        sec->pixels = tmp;
    }
    mac_present_screen_impl(1 /* is_flip */);
    mac_pace_60fps();
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_get_desc(DxBallDDSurface *self, DxBallSurfaceDesc *desc) {
    if (!self || !desc) return 0;
    MacSurface *s = (MacSurface *)self;
    desc->width = s->width;
    desc->height = s->height;
    desc->pitch = s->pitch;
    desc->pixels = s->pixels;
    desc->caps = 0x40;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_lock(DxBallDDSurface *self, DxBallRect *rect,
                                                  DxBallSurfaceDesc *desc, DxBallUInt flags, void *handle)
{
    (void)flags; (void)handle;
    if (!self || !desc) return 0;
    MacSurface *s = (MacSurface *)self;
    desc->width = s->width;
    desc->height = s->height;
    desc->pitch = s->pitch;
    desc->pixels = s->pixels + (rect ? (rect->top * s->pitch + rect->left) : 0);
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_unlock(DxBallDDSurface *self, void *handle) {
    (void)self; (void)handle;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_set_color_key(DxBallDDSurface *self, DxBallUInt flags, DxBallColorKey *key) {
    (void)flags;
    if (!self) return 0;
    MacSurface *s = (MacSurface *)self;
    s->color_key = key ? key->low : 0;
    s->has_color_key = 1;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_set_palette(DxBallDDSurface *self, DxBallDDPalette *pal) {
    (void)self; (void)pal;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_restore(DxBallDDSurface *self) {
    (void)self;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_get_blt_status(DxBallDDSurface *self, DxBallUInt flags) {
    (void)self; (void)flags;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_surface_get_attached_surface(DxBallDDSurface *self,
                                                               const DxBallUInt *caps,
                                                               DxBallDDSurface **out_surface)
{
    (void)caps;
    if (!self) return -1;
    MacSurface *s = (MacSurface *)self;
    if (out_surface) *out_surface = (DxBallDDSurface *)s->attached;
    return s->attached ? 0 : -1;
}

static DxBallInt DXBALL_DDCALL mac_surface_set_clipper(DxBallDDSurface *self, DxBallDDClipper *clipper) {
    (void)self; (void)clipper;
    return 0;
}

/* --- Clipper --- */
static DxBallInt DXBALL_DDCALL mac_clipper_set_window(DxBallDDClipper *self, DxBallUInt flags, size_t hwnd) {
    (void)self; (void)flags; (void)hwnd;
    return 0;
}
static const DxBallDDClipperVTable g_clipper_vtable = {
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    mac_clipper_set_window
};
static DxBallDDClipper g_clipper_instance = { &g_clipper_vtable };

/* --- Palette --- */
typedef struct MacPalette {
    const DxBallDDPaletteVTable *vtable;
    DxBallPaletteEntry entries[256];
} MacPalette;

static DxBallUInt DXBALL_DDCALL mac_palette_release(DxBallDDPalette *self) {
    if (self) free(self);
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_palette_set_entries(DxBallDDPalette *self, DxBallUInt flags,
                                                         DxBallUInt start, DxBallUInt count,
                                                         DxBallPaletteEntry *entries)
{
    (void)flags;
    MacPalette *p = (MacPalette *)self;
    if (entries && start + count <= 256) {
        for (DxBallUInt i = 0; i < count; ++i) {
            dxball_live_palette[start + i] = entries[i];
            if (p) p->entries[start + i] = entries[i];
        }
    }
    return 0;
}

static const DxBallDDPaletteVTable g_palette_vtable = {
    {NULL, NULL, (DxBallUnknownDDMethod)mac_palette_release, NULL, NULL, NULL},
    mac_palette_set_entries
};

static DxBallInt DXBALL_DDCALL mac_ddraw_create_palette(DxBallDDraw *self, DxBallUInt flags,
                                                          DxBallPaletteEntry *entries,
                                                          DxBallDDPalette **out_palette, void *outer)
{
    (void)self; (void)flags; (void)outer;
    MacPalette *p = (MacPalette *)calloc(1, sizeof(MacPalette));
    p->vtable = &g_palette_vtable;
    if (entries) {
        memcpy(p->entries, entries, sizeof(p->entries));
    }
    if (out_palette) *out_palette = (DxBallDDPalette *)p;
    return 0;
}

/* --- DirectDraw Implementation --- */
static DxBallInt DXBALL_DDCALL mac_ddraw_create_surface(DxBallDDraw *self, DxBallSurfaceDesc *desc,
                                                          DxBallDDSurface **out_surface, void *outer)
{
    (void)self; (void)outer;
    if (!desc || !out_surface) return -1;

    DxBallUInt w = desc->width;
    DxBallUInt h = desc->height;
    if (w == 0 || h == 0 || w > 4096 || h > 4096) {
        w = 640;
        h = 480;
    }
    desc->width = w;
    desc->height = h;

    MacSurface *s = (MacSurface *)calloc(1, sizeof(MacSurface));
    s->vtable = &g_surface_vtable;
    s->width = w;
    s->height = h;
    s->pitch = (desc->pitch >= (DxBallInt)w && desc->pitch <= 4096) ? desc->pitch : (DxBallInt)w;
    desc->pitch = s->pitch;
    s->pixels = (DxBallByte *)calloc(1, s->pitch * s->height);
    desc->pixels = s->pixels;

    // Check if backbuffer requested (flags & 0x20)
    if (desc->flags & 0x20) {
        MacSurface *sec = (MacSurface *)calloc(1, sizeof(MacSurface));
        sec->vtable = &g_surface_vtable;
        sec->width = w;
        sec->height = h;
        sec->pitch = s->pitch;
        sec->pixels = (DxBallByte *)calloc(1, sec->pitch * sec->height);
        s->attached = sec;
    }

    *out_surface = (DxBallDDSurface *)s;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_ddraw_set_cooperative_level(DxBallDDraw *self, size_t hwnd, DxBallUInt flags) {
    (void)self; (void)hwnd; (void)flags;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_ddraw_set_display_mode(DxBallDDraw *self, DxBallUInt width, DxBallUInt height, DxBallUInt bpp) {
    (void)self; (void)width; (void)height; (void)bpp;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_ddraw_get_caps(DxBallDDraw *self, void *caps_ptr, void *outer) {
    (void)self; (void)outer;
    if (caps_ptr) {
        DxBallDrawCaps *caps = (DxBallDrawCaps *)caps_ptr;
        caps->caps = 0; // Hardware supported
        caps->free_video_memory = 64 * 1024 * 1024;
    }
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_ddraw_create_clipper(DxBallDDraw *self, DxBallUInt flags,
                                                       DxBallDDClipper **out_clipper, void *outer)
{
    (void)self; (void)flags; (void)outer;
    if (out_clipper) *out_clipper = &g_clipper_instance;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_ddraw_wait_vertical_blank(DxBallDDraw *self, DxBallUInt flags, void *handle) {
    (void)self; (void)flags; (void)handle;
    mac_present_screen_impl(0);
    mac_pace_60fps();
    return 0;
}

static const DxBallDDrawVTable g_ddraw_vtable = {
    {NULL, NULL, NULL, NULL, (DxBallUnknownDDMethod)mac_ddraw_create_clipper},
    mac_ddraw_create_palette,
    mac_ddraw_create_surface,
    {
        NULL, NULL, NULL, NULL,
        (DxBallUnknownDDMethod)mac_ddraw_get_caps,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        (DxBallUnknownDDMethod)mac_ddraw_set_cooperative_level,
        (DxBallUnknownDDMethod)mac_ddraw_set_display_mode
    },
    mac_ddraw_wait_vertical_blank
};
static DxBallDDraw g_ddraw_instance = { &g_ddraw_vtable };

static DxBallInt DXBALL_DDCALL mac_direct_draw_create(void *guid, DxBallDDraw **out_device, void *outer) {
    (void)guid; (void)outer;
    if (out_device) *out_device = &g_ddraw_instance;
    return 0;
}

/* --- DirectSound Implementation with SDL Audio --- */
typedef struct MacSoundBuffer {
    const DxBallSoundBufferVTable *vtable;
    uint8_t *pcm_data;
    uint32_t size;
    uint32_t sample_rate;
    uint16_t channels;
    uint16_t bits_per_sample;
    int volume;
    int pan;
    uint32_t frequency;
    int playing;
    float cursor; // Sample position in buffer
    struct MacSoundBuffer *next;
} MacSoundBuffer;

static MacSoundBuffer *g_active_buffers = NULL;
static SDL_AudioDeviceID g_audio_dev = 0;

static void SDLCALL sdl_audio_callback(void *userdata, Uint8 *stream, int len) {
    (void)userdata;
    memset(stream, 0, len);
    int16_t *out = (int16_t *)stream;
    int samples = len / (2 * sizeof(int16_t)); // 16-bit stereo

    MacSoundBuffer *cur = g_active_buffers;
    while (cur) {
        if (cur->playing && cur->pcm_data && cur->size > 0) {
            float vol = powf(10.0f, (float)cur->volume / 2000.0f);
            if (vol > 1.0f) vol = 1.0f;
            if (vol < 0.0f) vol = 0.0f;

            float pan_left = 1.0f, pan_right = 1.0f;
            if (cur->pan < 0) {
                pan_right = 1.0f + ((float)cur->pan / 10000.0f);
            } else if (cur->pan > 0) {
                pan_left = 1.0f - ((float)cur->pan / 10000.0f);
            }

            int bytes_per_sample = (cur->bits_per_sample / 8) * cur->channels;
            if (bytes_per_sample <= 0) bytes_per_sample = 1;
            uint32_t total_samples = cur->size / bytes_per_sample;

            float step = (cur->frequency > 0) ? ((float)cur->frequency / 44100.0f) : 1.0f;

            for (int i = 0; i < samples; ++i) {
                uint32_t s_idx = (uint32_t)cur->cursor;
                if (s_idx >= total_samples) {
                    cur->playing = 0;
                    cur->cursor = 0.0f;
                    break;
                }

                int32_t sample_l = 0, sample_r = 0;
                uint8_t *p = cur->pcm_data + s_idx * bytes_per_sample;

                if (cur->bits_per_sample == 8) {
                    int16_t s = (int16_t)(((int)p[0] - 128) << 8);
                    sample_l = s;
                    sample_r = (cur->channels > 1) ? (int16_t)(((int)p[1] - 128) << 8) : s;
                } else if (cur->bits_per_sample == 16) {
                    int16_t s = *(int16_t *)p;
                    sample_l = s;
                    sample_r = (cur->channels > 1) ? *((int16_t *)p + 1) : s;
                }

                int32_t mixed_l = out[i * 2] + (int32_t)(sample_l * vol * pan_left);
                int32_t mixed_r = out[i * 2 + 1] + (int32_t)(sample_r * vol * pan_right);

                // Clip
                if (mixed_l > 32767) mixed_l = 32767;
                if (mixed_l < -32768) mixed_l = -32768;
                if (mixed_r > 32767) mixed_r = 32767;
                if (mixed_r < -32768) mixed_r = -32768;

                out[i * 2] = (int16_t)mixed_l;
                out[i * 2 + 1] = (int16_t)mixed_r;

                cur->cursor += step;
            }
        }
        cur = cur->next;
    }
}

static DxBallUInt DXBALL_DDCALL mac_sound_buffer_release(DxBallSoundBuffer *self) {
    if (!self) return 0;
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (g_audio_dev) SDL_LockAudioDevice(g_audio_dev);
    // Remove from linked list
    if (g_active_buffers == b) {
        g_active_buffers = b->next;
    } else if (g_active_buffers) {
        MacSoundBuffer *p = g_active_buffers;
        while (p->next && p->next != b) p = p->next;
        if (p->next == b) p->next = b->next;
    }
    if (g_audio_dev) SDL_UnlockAudioDevice(g_audio_dev);

    if (b->pcm_data) free(b->pcm_data);
    free(b);
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_sound_buffer_get_volume(DxBallSoundBuffer *self, DxBallInt *vol) {
    if (self && vol) *vol = ((MacSoundBuffer *)self)->volume;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_get_pan(DxBallSoundBuffer *self, DxBallInt *pan) {
    if (self && pan) *pan = ((MacSoundBuffer *)self)->pan;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_get_frequency(DxBallSoundBuffer *self, DxBallUInt *freq) {
    if (self && freq) *freq = ((MacSoundBuffer *)self)->frequency;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_get_status(DxBallSoundBuffer *self, DxBallUInt *status) {
    if (self && status) *status = ((MacSoundBuffer *)self)->playing ? 1 : 0;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_lock(DxBallSoundBuffer *self, DxBallUInt offset, DxBallUInt bytes,
                                                    void **ptr1, DxBallUInt *bytes1, void **ptr2, DxBallUInt *bytes2, DxBallUInt flags)
{
    (void)offset; (void)flags;
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (!b) return -1;
    if (!b->pcm_data) {
        b->pcm_data = (uint8_t *)calloc(1, bytes);
        b->size = bytes;
    }
    if (ptr1) *ptr1 = b->pcm_data;
    if (bytes1) *bytes1 = bytes;
    if (ptr2) *ptr2 = NULL;
    if (bytes2) *bytes2 = 0;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_unlock(DxBallSoundBuffer *self, void *ptr1, DxBallUInt bytes1, void *ptr2, DxBallUInt bytes2) {
    (void)self; (void)ptr1; (void)bytes1; (void)ptr2; (void)bytes2;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_play(DxBallSoundBuffer *self, DxBallUInt r1, DxBallUInt r2, DxBallUInt flags) {
    (void)r1; (void)r2; (void)flags;
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) {
        if (g_audio_dev) SDL_LockAudioDevice(g_audio_dev);
        b->cursor = 0.0f;
        b->playing = 1;
        if (g_audio_dev) SDL_UnlockAudioDevice(g_audio_dev);
    }
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_set_current_position(DxBallSoundBuffer *self, DxBallUInt pos) {
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) b->cursor = (float)pos;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_set_volume(DxBallSoundBuffer *self, DxBallInt vol) {
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) b->volume = vol;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_set_pan(DxBallSoundBuffer *self, DxBallInt pan) {
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) b->pan = pan;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_set_frequency(DxBallSoundBuffer *self, DxBallUInt freq) {
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) b->frequency = freq;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_stop(DxBallSoundBuffer *self) {
    MacSoundBuffer *b = (MacSoundBuffer *)self;
    if (b) b->playing = 0;
    return 0;
}
static DxBallInt DXBALL_DDCALL mac_sound_buffer_restore(DxBallSoundBuffer *self) {
    (void)self;
    return 0;
}

static const DxBallSoundBufferVTable g_sound_buffer_vtable = {
    NULL, NULL, // query_interface, add_ref
    mac_sound_buffer_release,
    NULL, NULL, NULL, // get_caps, get_current_position, get_format
    mac_sound_buffer_get_volume,
    mac_sound_buffer_get_pan,
    mac_sound_buffer_get_frequency,
    mac_sound_buffer_get_status,
    NULL, // initialize
    mac_sound_buffer_lock,
    mac_sound_buffer_play,
    mac_sound_buffer_set_current_position,
    NULL, // set_format
    mac_sound_buffer_set_volume,
    mac_sound_buffer_set_pan,
    mac_sound_buffer_set_frequency,
    mac_sound_buffer_stop,
    mac_sound_buffer_unlock,
    mac_sound_buffer_restore
};

/* WAVE header chunk parser */
#pragma pack(push, 1)
typedef struct WaveHeader {
    uint16_t format_tag;
    uint16_t channels;
    uint32_t samples_per_sec;
    uint32_t avg_bytes_per_sec;
    uint16_t block_align;
    uint16_t bits_per_sample;
} WaveHeader;
#pragma pack(pop)

static DxBallInt DXBALL_DDCALL mac_sound_device_create_buffer(DxBallSoundDevice *self,
                                                              const DxBallSoundBufferDesc *desc,
                                                              DxBallSoundBuffer **out_buffer, void *outer)
{
    (void)self; (void)outer;
    if (!desc || !out_buffer) return -1;
    MacSoundBuffer *b = (MacSoundBuffer *)calloc(1, sizeof(MacSoundBuffer));
    b->vtable = &g_sound_buffer_vtable;
    b->size = desc->bytes;
    b->volume = 0;
    b->pan = 0;

    if (desc->format) {
        const WaveHeader *w = (const WaveHeader *)desc->format;
        b->sample_rate = w->samples_per_sec;
        b->channels = w->channels;
        b->bits_per_sample = w->bits_per_sample;
        b->frequency = w->samples_per_sec;
    } else {
        b->sample_rate = 22050;
        b->channels = 1;
        b->bits_per_sample = 8;
        b->frequency = 22050;
    }

    if (g_audio_dev) SDL_LockAudioDevice(g_audio_dev);
    b->next = g_active_buffers;
    g_active_buffers = b;
    if (g_audio_dev) SDL_UnlockAudioDevice(g_audio_dev);

    *out_buffer = (DxBallSoundBuffer *)b;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_sound_device_set_cooperative_level(DxBallSoundDevice *self, DxBallHandle hwnd, DxBallUInt flags) {
    (void)self; (void)hwnd; (void)flags;
    return 0;
}

static DxBallUInt DXBALL_DDCALL mac_sound_device_release(DxBallSoundDevice *self) {
    (void)self;
    return 0;
}

static const DxBallSoundDeviceVTable g_sound_device_vtable = {
    NULL, NULL,
    mac_sound_device_release,
    mac_sound_device_create_buffer,
    NULL, NULL,
    mac_sound_device_set_cooperative_level
};
static DxBallSoundDevice g_sound_device_instance = { &g_sound_device_vtable };

static DxBallInt DXBALL_DDCALL mac_direct_sound_create(void *guid, DxBallSoundDevice **out_dev, void *outer) {
    (void)guid; (void)outer;
    if (out_dev) *out_dev = &g_sound_device_instance;
    return 0;
}

/* --- Window & Platform APIs --- */
static DxBallHandle DXBALL_DDCALL mac_load_icon(DxBallHandle instance, DxBallHandle name) { (void)instance; (void)name; return (DxBallHandle)1; }
static DxBallHandle DXBALL_DDCALL mac_load_cursor(DxBallHandle instance, DxBallHandle name) { (void)instance; (void)name; return (DxBallHandle)1; }
static DxBallHandle DXBALL_DDCALL mac_stock_object(DxBallInt obj) { (void)obj; return (DxBallHandle)1; }

static DxBallUInt DXBALL_DDCALL mac_register_class(const DxBallWindowClass *input) {
    if (input) g_registered_proc = input->procedure;
    return 1;
}

static int s_is_fullscreen = 0;

static void mac_update_grab_and_cursor(void) {
    if (!g_window) return;
    Uint32 win_flags = SDL_GetWindowFlags(g_window);
    int has_focus = (win_flags & SDL_WINDOW_INPUT_FOCUS) != 0;
    int is_fullscreen = (win_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;

    int in_game = (dxball_display_mode == 1);
    int is_paused = (dxball_paused != 0);

    int need_grab = has_focus && in_game && !is_paused;
    if (has_focus && is_fullscreen) {
        need_grab = 1;
    }

    SDL_SetWindowGrab(g_window, need_grab ? SDL_TRUE : SDL_FALSE);

    if (!has_focus || (in_game && is_paused)) {
        SDL_ShowCursor(SDL_ENABLE);
    } else {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

static void mac_toggle_fullscreen(void) {
    if (!g_window) return;
    s_is_fullscreen = !s_is_fullscreen;
    SDL_SetWindowFullscreen(g_window, s_is_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    mac_update_grab_and_cursor();
}

static void mac_logical_to_window(int lx, int ly, int *wx, int *wy) {
    if (!g_window) {
        if (wx) *wx = lx;
        if (wy) *wy = ly;
        return;
    }
    int win_w = 960, win_h = 720;
    SDL_GetWindowSize(g_window, &win_w, &win_h);
    float scale_x = (float)win_w / 640.0f;
    float scale_y = (float)win_h / 480.0f;
    float scale = scale_x < scale_y ? scale_x : scale_y;
    float offset_x = ((float)win_w - 640.0f * scale) * 0.5f;
    float offset_y = ((float)win_h - 480.0f * scale) * 0.5f;

    if (wx) *wx = (int)roundf(offset_x + (float)lx * scale);
    if (wy) *wy = (int)roundf(offset_y + (float)ly * scale);
}

static void mac_window_to_logical(int wx, int wy, int *lx, int *ly) {
    if (!g_window) {
        if (lx) *lx = wx;
        if (ly) *ly = wy;
        return;
    }
    int win_w = 960, win_h = 720;
    SDL_GetWindowSize(g_window, &win_w, &win_h);
    float scale_x = (float)win_w / 640.0f;
    float scale_y = (float)win_h / 480.0f;
    float scale = scale_x < scale_y ? scale_x : scale_y;
    float offset_x = ((float)win_w - 640.0f * scale) * 0.5f;
    float offset_y = ((float)win_h - 480.0f * scale) * 0.5f;

    int out_x = (int)roundf(((float)wx - offset_x) / scale);
    int out_y = (int)roundf(((float)wy - offset_y) / scale);
    if (out_x < 0) out_x = 0;
    if (out_x > 640) out_x = 640;
    if (out_y < 0) out_y = 0;
    if (out_y > 480) out_y = 480;

    if (lx) *lx = out_x;
    if (ly) *ly = out_y;
}

static int s_last_warp_logical_x = -1;
static int s_last_warp_logical_y = -1;

static DxBallHandle DXBALL_DDCALL mac_create_window(DxBallUInt extended, const char *class_name,
    const char *title, DxBallUInt style, DxBallInt x, DxBallInt y, DxBallInt width,
    DxBallInt height, DxBallHandle parent, DxBallHandle menu, DxBallHandle instance, void *param)
{
    (void)extended; (void)class_name; (void)style; (void)x; (void)y; (void)parent; (void)menu; (void)instance; (void)param;

    if (!g_window) {
        int win_w = 960;
        int win_h = 720;
        g_window = SDL_CreateWindow(title ? title : "DX-Ball",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    win_w, win_h,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        if (!g_window) {
            fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
            return 0;
        }

        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (!g_renderer) {
            g_renderer = SDL_CreateRenderer(g_window, -1, 0);
        }
        SDL_RenderSetLogicalSize(g_renderer, 640, 480);

        g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888,
                                      SDL_TEXTUREACCESS_STREAMING, 640, 480);

        mac_update_grab_and_cursor();
    }
    return (DxBallHandle)g_window;
}

static DxBallInt DXBALL_DDCALL mac_show_window(DxBallHandle win, DxBallInt show) {
    (void)win; (void)show;
    dxball_application_active = 1;
    mac_update_grab_and_cursor();
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_update_window(DxBallHandle win) { (void)win; return 1; }
static DxBallHandle DXBALL_DDCALL mac_set_focus(DxBallHandle win) { return win; }
static DxBallInt DXBALL_DDCALL mac_destroy_window(DxBallHandle win) { (void)win; return 1; }

static DxBallInt DXBALL_DDCALL mac_message_box(DxBallHandle win, const char *msg, const char *title, DxBallUInt type) {
    (void)win; (void)type;
    fprintf(stderr, "DX-Ball [%s]: %s\n", title ? title : "", msg ? msg : "");
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_get_cursor_pos(DxBallPoint *pt) {
    if (!pt) return 0;
    static int s_initialized = 0;
    if (!s_initialized && g_window) {
        int win_x = 0, win_y = 0;
        SDL_GetMouseState(&win_x, &win_y);
        int mx = 0, my = 0;
        mac_window_to_logical(win_x, win_y, &mx, &my);
        dxball_cursor_point.x = mx;
        dxball_cursor_point.y = my;
        s_initialized = 1;
    }
    pt->x = dxball_cursor_point.x;
    pt->y = dxball_cursor_point.y;
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_peek_message(DxBallMessage *msg, DxBallHandle win,
                                               DxBallUInt first, DxBallUInt last, DxBallUInt remove)
{
    (void)win; (void)first; (void)last;
    if (g_quit_flag) {
        msg->message = 0x12; // WM_QUIT
        msg->wparam = 0;
        return 1;
    }

    mac_update_grab_and_cursor();

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        DxBallMessage m;
        memset(&m, 0, sizeof(m));
        m.window = (DxBallHandle)g_window;

        if (ev.type == SDL_QUIT) {
            g_quit_flag = 1;
            m.message = 0x10; // WM_CLOSE
            queue_push_event(&m);
        } else if (ev.type == SDL_WINDOWEVENT) {
            if (ev.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                dxball_application_active = 1;
                mac_update_grab_and_cursor();
                m.message = 0x1C; // WM_ACTIVATEAPP
                m.wparam = 1;
                queue_push_event(&m);

                m.message = 0x07; // WM_SETFOCUS
                m.wparam = 0;
                queue_push_event(&m);
            } else if (ev.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                mac_update_grab_and_cursor();
                m.message = 0x08; // WM_KILLFOCUS
                queue_push_event(&m);
            } else if (ev.window.event == SDL_WINDOWEVENT_EXPOSED) {
                mac_present_screen_impl(0);
            }
        } else if (ev.type == SDL_MOUSEMOTION) {
            if (ev.motion.x == s_last_warp_logical_x && ev.motion.y == s_last_warp_logical_y) {
                s_last_warp_logical_x = -1;
                s_last_warp_logical_y = -1;
                continue;
            }
            int mx = ev.motion.x;
            int my = ev.motion.y;
            if (mx < 0) mx = 0;
            if (mx > 640) mx = 640;
            if (my < 0) my = 0;
            if (my > 480) my = 480;

            dxball_cursor_point.x = mx;
            dxball_cursor_point.y = my;
            dxball_mouse_x = mx;
            dxball_mouse_y = my;

            m.message = 0x200; // WM_MOUSEMOVE
            m.wparam = 0;
            m.lparam = (my << 16) | (mx & 0xFFFF);
            queue_push_event(&m);
        } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
            int mx = ev.button.x;
            int my = ev.button.y;
            if (mx < 0) mx = 0;
            if (mx > 640) mx = 640;
            if (my < 0) my = 0;
            if (my > 480) my = 480;
            dxball_cursor_point.x = mx;
            dxball_cursor_point.y = my;
            dxball_mouse_x = mx;
            dxball_mouse_y = my;

            if (ev.button.button == SDL_BUTTON_LEFT) {
                dxball_mouse_action = 1;
                m.message = 0x201; // WM_LBUTTONDOWN
            } else {
                dxball_mouse_action = 2;
                m.message = 0x204; // WM_RBUTTONDOWN
            }
            m.lparam = (my << 16) | (mx & 0xFFFF);
            queue_push_event(&m);
        } else if (ev.type == SDL_MOUSEBUTTONUP) {
            int mx = ev.button.x;
            int my = ev.button.y;
            if (mx < 0) mx = 0;
            if (mx > 640) mx = 640;
            if (my < 0) my = 0;
            if (my > 480) my = 480;
            dxball_cursor_point.x = mx;
            dxball_cursor_point.y = my;
            dxball_mouse_x = mx;
            dxball_mouse_y = my;

            dxball_mouse_action = 0;
            if (ev.button.button == SDL_BUTTON_LEFT) {
                m.message = 0x202; // WM_LBUTTONUP
            } else {
                m.message = 0x205; // WM_RBUTTONUP
            }
            m.lparam = (my << 16) | (mx & 0xFFFF);
            queue_push_event(&m);
        } else if (ev.type == SDL_KEYDOWN) {
            if ((ev.key.keysym.sym == SDLK_RETURN && (ev.key.keysym.mod & KMOD_ALT)) ||
                (ev.key.keysym.sym == SDLK_f && (ev.key.keysym.mod & KMOD_GUI)) ||
                ev.key.keysym.sym == SDLK_F4) {
                mac_toggle_fullscreen();
                continue;
            }
            if ((ev.key.keysym.sym == SDLK_g && (ev.key.keysym.mod & KMOD_GUI)) ||
                ev.key.keysym.sym == SDLK_F11) {
                static int s_manual_ungrab = 0;
                s_manual_ungrab = !s_manual_ungrab;
                if (s_manual_ungrab) {
                    SDL_SetWindowGrab(g_window, SDL_FALSE);
                    SDL_ShowCursor(SDL_ENABLE);
                } else {
                    mac_update_grab_and_cursor();
                }
                continue;
            }

            m.message = 0x100; // WM_KEYDOWN
            DxBallHandle vk = 0;
            switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE: vk = 0x1B; break;
                case SDLK_RETURN: vk = 0x0D; break;
                case SDLK_SPACE: vk = ' '; break;
                case SDLK_LCTRL: case SDLK_RCTRL: vk = 0x11; dxball_control_pressed = 1; break;
                case SDLK_LSHIFT: case SDLK_RSHIFT: vk = 0x10; dxball_shift_pressed = 1; break;
                case SDLK_F1: vk = 0x70; break;
                case SDLK_F2: vk = 0x71; break;
                case SDLK_F3: vk = 0x72; break;
                case SDLK_F4: vk = 0x73; break;
                case SDLK_F5: vk = 0x74; break;
                case SDLK_F6: vk = 0x75; break;
                case SDLK_F7: vk = 0x76; break;
                case SDLK_F8: vk = 0x77; break;
                case SDLK_F9: vk = 0x78; break;
                case SDLK_F10: vk = 0x79; break;
                case SDLK_F11: vk = 0x7A; break;
                case SDLK_F12: vk = 0x7B; break;
                case SDLK_LEFT: vk = 0x25; break;
                case SDLK_UP: vk = 0x26; break;
                case SDLK_RIGHT: vk = 0x27; break;
                case SDLK_DOWN: vk = 0x28; break;
                default:
                    if (ev.key.keysym.sym >= 'a' && ev.key.keysym.sym <= 'z')
                        vk = ev.key.keysym.sym - 'a' + 'A';
                    else if (ev.key.keysym.sym < 128)
                        vk = ev.key.keysym.sym;
                    break;
            }
            m.wparam = vk;
            queue_push_event(&m);
        } else if (ev.type == SDL_KEYUP) {
            m.message = 0x101; // WM_KEYUP
            if (ev.key.keysym.sym == SDLK_LCTRL || ev.key.keysym.sym == SDLK_RCTRL) {
                m.wparam = 0x11;
                dxball_control_pressed = 0;
            } else if (ev.key.keysym.sym == SDLK_LSHIFT || ev.key.keysym.sym == SDLK_RSHIFT) {
                m.wparam = 0x10;
                dxball_shift_pressed = 0;
            }
            queue_push_event(&m);
        }
    }

    return queue_peek(msg, remove != 0);
}

static DxBallInt DXBALL_DDCALL mac_wait_message(void) {
    SDL_WaitEventTimeout(NULL, 1);
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_get_message(DxBallMessage *msg, DxBallHandle win, DxBallUInt first, DxBallUInt last) {
    while (!mac_peek_message(msg, win, first, last, 1 /* remove */)) {
        SDL_Delay(1);
    }
    return (msg->message != 0x12);
}

static DxBallInt DXBALL_DDCALL mac_translate_message(const DxBallMessage *msg) {
    (void)msg;
    return 1;
}

static DxBallWindowResult DXBALL_DDCALL mac_dispatch_message(const DxBallMessage *msg) {
    if (g_registered_proc) {
        return g_registered_proc(msg->window, msg->message, msg->wparam, msg->lparam);
    }
    return 0;
}

static DxBallWindowResult DXBALL_DDCALL mac_default_proc(DxBallHandle win, DxBallUInt msg,
                                                       DxBallHandle wp, DxBallWindowResult lp)
{
    (void)win; (void)msg; (void)wp; (void)lp;
    return 0;
}

static DxBallInt DXBALL_DDCALL mac_post_message(DxBallHandle win, DxBallUInt msg,
                                               DxBallHandle wp, DxBallWindowResult lp)
{
    (void)win; (void)wp; (void)lp;
    if (msg == 0x10 || msg == 0x12) g_quit_flag = 1;
    return 1;
}

static void DXBALL_DDCALL mac_post_quit(DxBallInt code) {
    (void)code;
    g_quit_flag = 1;
}

static DxBallHandle DXBALL_DDCALL mac_set_cursor(DxBallHandle cur) { return cur; }
static DxBallHandle DXBALL_DDCALL mac_set_capture(DxBallHandle win) { return win; }
static DxBallInt DXBALL_DDCALL mac_release_capture(void) { return 1; }

static DxBallHandle DXBALL_DDCALL mac_open_semaphore(DxBallUInt access, DxBallInt inherit, const char *name) {
    (void)access; (void)inherit; (void)name;
    return 0; // Allow first instance
}

#define MAC_HANDLE_FILE_MAGIC 0x46494C45 // 'FILE'
#define MAC_HANDLE_MAPP_MAGIC 0x4D415050 // 'MAPP'
#define MAC_HANDLE_SEMA_MAGIC 0x53454D41 // 'SEMA'

typedef struct MacFileHandle {
    uint32_t magic;
    FILE *file;
    void *map_buf;
    size_t map_size;
} MacFileHandle;

static DxBallHandle DXBALL_DDCALL mac_create_semaphore(const DxBallSecurityAttributes *attr,
                                                      DxBallInt initial, DxBallInt maximum, const char *name)
{
    (void)attr; (void)initial; (void)maximum; (void)name;
    MacFileHandle *h = (MacFileHandle *)calloc(1, sizeof(MacFileHandle));
    h->magic = MAC_HANDLE_SEMA_MAGIC;
    return (DxBallHandle)h;
}

static DxBallInt DXBALL_DDCALL mac_version_info(DxBallVersionInfo *version) {
    if (version) {
        version->major = 4;
        version->minor = 0;
        version->platform = 1; // VER_PLATFORM_WIN32_WINDOWS (high_resolution_clock = 0, uses timeGetTime directly)
    }
    return 1;
}

static DxBallUInt DXBALL_DDCALL mac_time_ms(void) {
    return SDL_GetTicks();
}

static DxBallInt DXBALL_DDCALL mac_clock_freq(DxBallCounter *cnt) {
    if (cnt) {
        cnt->low = 1000;
        cnt->high = 0;
    }
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_clock_counter(DxBallCounter *cnt) {
    if (cnt) {
        cnt->low = SDL_GetTicks();
        cnt->high = 0;
    }
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_set_cursor_pos(DxBallInt x, DxBallInt y) {
    dxball_mouse_x = x;
    dxball_mouse_y = y;
    dxball_cursor_point.x = x;
    dxball_cursor_point.y = y;
    if (g_window) {
        int win_x = 0, win_y = 0;
        mac_logical_to_window(x, y, &win_x, &win_y);
        if (getenv("DXBALL_AUTOTEST")) {
            printf("SET_CURSOR: in=(%d,%d) -> win=(%d,%d)\n", x, y, win_x, win_y);
        }
        s_last_warp_logical_x = x;
        s_last_warp_logical_y = y;
        SDL_WarpMouseInWindow(g_window, win_x, win_y);
    }
    return 1;
}

/* File IO with case-insensitive and directory fallback */
static FILE *open_file_helper(const char *name, const char *mode) {
    FILE *f = fopen(name, mode);
    if (f) return f;

    // Try "original/" prefix
    char path[512];
    snprintf(path, sizeof(path), "original/%s", name);
    f = fopen(path, mode);
    if (f) return f;

    // Try lowercase
    char lower[256];
    size_t len = strlen(name);
    if (len < sizeof(lower)) {
        for (size_t i = 0; i <= len; ++i) lower[i] = tolower((unsigned char)name[i]);
        f = fopen(lower, mode);
        if (f) return f;
        snprintf(path, sizeof(path), "original/%s", lower);
        f = fopen(path, mode);
        if (f) return f;
    }

    // Try uppercase
    char upper[256];
    if (len < sizeof(upper)) {
        for (size_t i = 0; i <= len; ++i) upper[i] = toupper((unsigned char)name[i]);
        f = fopen(upper, mode);
        if (f) return f;
        snprintf(path, sizeof(path), "original/%s", upper);
        f = fopen(path, mode);
        if (f) return f;
    }

    return NULL;
}

static DxBallHandle DXBALL_DDCALL mac_file_create(const char *name, DxBallUInt access,
    DxBallUInt share, void *sec, DxBallUInt creation, DxBallUInt flags, DxBallHandle tmpl)
{
    (void)share; (void)sec; (void)creation; (void)flags; (void)tmpl;
    const char *mode = (access & 0x40000000) ? "wb" : "rb";
    FILE *f = open_file_helper(name, mode);
    if (!f) return (DxBallHandle)-1;

    MacFileHandle *h = (MacFileHandle *)calloc(1, sizeof(MacFileHandle));
    h->magic = MAC_HANDLE_FILE_MAGIC;
    h->file = f;
    return (DxBallHandle)h;
}

static DxBallUInt DXBALL_DDCALL mac_file_size(DxBallHandle file, DxBallUInt *high) {
    if (!file || file == (DxBallHandle)-1 || (uintptr_t)file < 0x1000) return 0;
    MacFileHandle *h = (MacFileHandle *)file;
    if (h->magic != MAC_HANDLE_FILE_MAGIC || !h->file) return 0;
    long cur = ftell(h->file);
    fseek(h->file, 0, SEEK_END);
    long sz = ftell(h->file);
    fseek(h->file, cur, SEEK_SET);
    if (high) *high = 0;
    return (DxBallUInt)sz;
}

static DxBallInt DXBALL_DDCALL mac_file_read(DxBallHandle file, void *dest,
    DxBallUInt bytes, DxBallUInt *read_bytes, void *overlapped)
{
    (void)overlapped;
    if (!file || file == (DxBallHandle)-1 || (uintptr_t)file < 0x1000) return 0;
    MacFileHandle *h = (MacFileHandle *)file;
    if (h->magic != MAC_HANDLE_FILE_MAGIC || !h->file) return 0;
    size_t r = fread(dest, 1, bytes, h->file);
    if (read_bytes) *read_bytes = (DxBallUInt)r;
    return (r > 0 || bytes == 0);
}

static DxBallInt DXBALL_DDCALL mac_file_close(DxBallHandle file) {
    if (!file || file == (DxBallHandle)-1 || (uintptr_t)file < 0x1000) return 1;
    MacFileHandle *h = (MacFileHandle *)file;
    if (h->magic == MAC_HANDLE_FILE_MAGIC) {
        if (h->file) fclose(h->file);
        h->magic = 0;
        free(h);
    } else if (h->magic == MAC_HANDLE_MAPP_MAGIC) {
        if (h->map_buf) free(h->map_buf);
        h->magic = 0;
        free(h);
    } else if (h->magic == MAC_HANDLE_SEMA_MAGIC) {
        h->magic = 0;
        free(h);
    }
    return 1;
}

static void *DXBALL_DDCALL mac_local_alloc(DxBallUInt flags, size_t bytes) {
    (void)flags;
    return malloc(bytes);
}
static void *DXBALL_DDCALL mac_local_free(void *mem) {
    free(mem);
    return NULL;
}

/* MIDI Stream Support */
static DxBallMidiHandle DXBALL_DDCALL mac_midi_create_mapping(DxBallMidiHandle h, void *s, DxBallUInt p, DxBallUInt hi, DxBallUInt lo, const char *n) {
    (void)s; (void)p; (void)hi; (void)lo; (void)n;
    if (!h || h == (DxBallMidiHandle)-1 || (uintptr_t)h < 0x1000) return 0;
    MacFileHandle *src = (MacFileHandle *)h;
    if (src->magic != MAC_HANDLE_FILE_MAGIC || !src->file) return 0;

    MacFileHandle *mh = (MacFileHandle *)calloc(1, sizeof(MacFileHandle));
    mh->magic = MAC_HANDLE_MAPP_MAGIC;
    mh->file = src->file;
    return (DxBallMidiHandle)mh;
}

static void *DXBALL_DDCALL mac_midi_map_view(DxBallMidiHandle m, DxBallUInt a, DxBallUInt hi, DxBallUInt lo, size_t b) {
    (void)a; (void)hi; (void)lo; (void)b;
    if (!m || m == (DxBallMidiHandle)-1 || (uintptr_t)m < 0x1000) return NULL;
    MacFileHandle *mh = (MacFileHandle *)m;
    if (mh->magic != MAC_HANDLE_MAPP_MAGIC || !mh->file) return NULL;

    long cur = ftell(mh->file);
    fseek(mh->file, 0, SEEK_END);
    mh->map_size = (size_t)ftell(mh->file);
    fseek(mh->file, 0, SEEK_SET);

    mh->map_buf = malloc(mh->map_size);
    if (!mh->map_buf) {
        fseek(mh->file, cur, SEEK_SET);
        return NULL;
    }
    size_t rd = fread(mh->map_buf, 1, mh->map_size, mh->file);
    (void)rd;
    fseek(mh->file, cur, SEEK_SET);
    return mh->map_buf;
}

static DxBallInt DXBALL_DDCALL mac_midi_unmap_view(const void *p) {
    (void)p;
    return 1;
}

static DxBallInt DXBALL_DDCALL mac_midi_close_handle(DxBallMidiHandle h) {
    return mac_file_close((DxBallHandle)h);
}

static DxBallMidiHandle DXBALL_DDCALL mac_midi_global_alloc(DxBallUInt flags, size_t bytes) {
    (void)flags; return (DxBallMidiHandle)malloc(bytes);
}
static void *DXBALL_DDCALL mac_midi_global_lock(DxBallMidiHandle h) { return (void *)h; }
static DxBallMidiHandle DXBALL_DDCALL mac_midi_global_handle(const void *p) { return (DxBallMidiHandle)p; }
static DxBallInt DXBALL_DDCALL mac_midi_global_unlock(DxBallMidiHandle h) { (void)h; return 1; }
static DxBallMidiHandle DXBALL_DDCALL mac_midi_global_free(DxBallMidiHandle h) { free((void *)h); return 0; }

static DxBallUInt DXBALL_DDCALL mac_midi_stream_open(DxBallMidiHandle *s, DxBallUInt *d, DxBallUInt c, DxBallMidiCallback cb, size_t in, DxBallUInt f) {
    (void)s; (void)d; (void)c; (void)cb; (void)in; (void)f; return 0;
}
static DxBallUInt DXBALL_DDCALL mac_midi_stream_property(DxBallMidiHandle s, DxBallMidiProperty *p, DxBallUInt f) {
    (void)s; (void)p; (void)f; return 0;
}
static DxBallUInt DXBALL_DDCALL mac_midi_prepare_header(DxBallMidiHandle s, DxBallMidiHeader *h, DxBallUInt sz) {
    (void)s; (void)h; (void)sz; return 0;
}
static DxBallUInt DXBALL_DDCALL mac_midi_stream_out(DxBallMidiHandle s, DxBallMidiHeader *h, DxBallUInt sz) {
    (void)s; (void)h; (void)sz; return 0;
}
static DxBallUInt DXBALL_DDCALL mac_midi_stream_restart(DxBallMidiHandle s) { (void)s; return 0; }
static DxBallUInt DXBALL_DDCALL mac_midi_stream_pause(DxBallMidiHandle s) { (void)s; return 0; }
static DxBallUInt DXBALL_DDCALL mac_midi_out_reset(DxBallMidiHandle s) { (void)s; return 0; }
static DxBallUInt DXBALL_DDCALL mac_midi_unprepare_header(DxBallMidiHandle s, DxBallMidiHeader *h, DxBallUInt sz) {
    (void)s; (void)h; (void)sz; return 0;
}
static DxBallUInt DXBALL_DDCALL mac_midi_stream_close(DxBallMidiHandle s) { (void)s; return 0; }

void dxball_bind_mac(void)
{
    dxball_window_load_icon = mac_load_icon;
    dxball_window_load_cursor = mac_load_cursor;
    dxball_window_stock_object = mac_stock_object;
    dxball_window_register_class = mac_register_class;
    dxball_window_create_window_ex = mac_create_window;
    dxball_window_show_window = mac_show_window;
    dxball_window_update_window = mac_update_window;
    dxball_window_set_focus = mac_set_focus;
    dxball_window_destroy_window = mac_destroy_window;
    dxball_window_message_box = mac_message_box;
    dxball_window_get_cursor_pos = mac_get_cursor_pos;
    dxball_window_peek_message = mac_peek_message;
    dxball_window_wait_message = mac_wait_message;
    dxball_window_get_message = mac_get_message;
    dxball_window_translate_message = mac_translate_message;
    dxball_window_dispatch_message = mac_dispatch_message;
    dxball_window_default_window_proc = mac_default_proc;
    dxball_window_post_message = mac_post_message;
    dxball_window_post_quit_message = mac_post_quit;
    dxball_window_set_cursor = mac_set_cursor;
    dxball_window_set_capture = mac_set_capture;
    dxball_window_release_capture = mac_release_capture;
    dxball_window_open_semaphore = mac_open_semaphore;
    dxball_window_create_semaphore = mac_create_semaphore;
    dxball_window_get_version_ex = mac_version_info;
    dxball_set_cursor_position = mac_set_cursor_pos;

    dxball_time_get_time = mac_time_ms;
    dxball_query_performance_frequency = mac_clock_freq;
    dxball_query_performance_counter = mac_clock_counter;

    dxball_file_create = mac_file_create;
    dxball_file_size = mac_file_size;
    dxball_file_read = mac_file_read;
    dxball_file_close = mac_file_close;

    dxball_local_alloc = mac_local_alloc;
    dxball_local_free = mac_local_free;

    dxball_midi_create_mapping = mac_midi_create_mapping;
    dxball_midi_map_view = mac_midi_map_view;
    dxball_midi_unmap_view = mac_midi_unmap_view;
    dxball_midi_global_alloc = mac_midi_global_alloc;
    dxball_midi_global_lock = mac_midi_global_lock;
    dxball_midi_global_handle = mac_midi_global_handle;
    dxball_midi_global_unlock = mac_midi_global_unlock;
    dxball_midi_global_free = mac_midi_global_free;
    dxball_midi_stream_open = mac_midi_stream_open;
    dxball_midi_stream_property = mac_midi_stream_property;
    dxball_midi_prepare_header = mac_midi_prepare_header;
    dxball_midi_stream_out = mac_midi_stream_out;
    dxball_midi_stream_restart = mac_midi_stream_restart;
    dxball_midi_stream_pause = mac_midi_stream_pause;
    dxball_midi_out_reset = mac_midi_out_reset;
    dxball_midi_unprepare_header = mac_midi_unprepare_header;
    dxball_midi_stream_close = mac_midi_stream_close;

    dxball_application_active = 1;
    dxball_draw_factory_backend = mac_direct_draw_create;
    dxball_present_screen_hook = mac_present_screen;
    dxball_sound_api.create_device = mac_direct_sound_create;
    dxball_sound_api.allocate = malloc;
    dxball_sound_api.deallocate = free;

    // Initialize audio device
    SDL_AudioSpec want, have;
    memset(&want, 0, sizeof(want));
    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = sdl_audio_callback;
    g_audio_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (g_audio_dev) {
        SDL_PauseAudioDevice(g_audio_dev, 0);
    }
}
