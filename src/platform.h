#ifndef DXBALL_PLATFORM_H
#define DXBALL_PLATFORM_H

#include "device.h"
#include <stddef.h>

/* Startup methods occupy opaque slots in the resource owner's interfaces.
   Cast each slot to its observed signature before invoking it. The resource
   owner never calls these methods; both builds use these same declarations. */
typedef struct DxBallDDClipper DxBallDDClipper;
typedef struct DxBallDDClipperVTable {
    DxBallUnknownDDMethod slots_0_to_7[8];
    DxBallInt (DXBALL_DDCALL *set_window)(DxBallDDClipper *, DxBallUInt, size_t);
} DxBallDDClipperVTable;
struct DxBallDDClipper { const DxBallDDClipperVTable *vtable; };
typedef DxBallInt (DXBALL_DDCALL *DxBallCreateClipper)(DxBallDDraw *, DxBallUInt, DxBallDDClipper **, void *);
typedef DxBallInt (DXBALL_DDCALL *DxBallGetCaps)(DxBallDDraw *, void *, void *);
typedef DxBallInt (DXBALL_DDCALL *DxBallSetCooperativeLevel)(DxBallDDraw *, size_t, DxBallUInt);
typedef DxBallInt (DXBALL_DDCALL *DxBallSetDisplayMode)(DxBallDDraw *, DxBallUInt, DxBallUInt, DxBallUInt);
typedef DxBallInt (DXBALL_DDCALL *DxBallGetAttachedSurface)(DxBallDDSurface *, const DxBallUInt *, DxBallDDSurface **);
typedef DxBallInt (DXBALL_DDCALL *DxBallSetClipper)(DxBallDDSurface *, DxBallDDClipper *);
typedef DxBallUInt (DXBALL_DDCALL *DxBallReleasePalette)(DxBallDDPalette *);

typedef size_t DxBallHandle;
typedef ptrdiff_t DxBallWindowResult;
typedef struct DxBallPoint { DxBallInt x, y; } DxBallPoint;
typedef struct DxBallMessage {
    DxBallHandle window;
    DxBallUInt message;
    DxBallHandle wparam;
    DxBallWindowResult lparam;
    DxBallUInt time;
    DxBallPoint point;
} DxBallMessage;
typedef DxBallWindowResult (DXBALL_DDCALL *DxBallWindowProc)(DxBallHandle,
    DxBallUInt, DxBallHandle, DxBallWindowResult);
typedef struct DxBallWindowClass {
    DxBallUInt style;
    DxBallWindowProc procedure;
    DxBallInt class_extra, window_extra;
    DxBallHandle instance, icon, cursor, background;
    const char *menu, *name;
} DxBallWindowClass;
typedef struct DxBallSecurityAttributes {
    DxBallUInt length;
    void *descriptor;
    DxBallInt inherit;
} DxBallSecurityAttributes;
typedef struct DxBallVersionInfo {
    DxBallUInt size, major, minor, build, platform;
    char service_pack[128];
} DxBallVersionInfo;

/* The original DirectDraw 1 capability record is 316 bytes. The startup caller
   consumes the NOHARDWARE bit and dwVidMemFree, at offsets 4 and 64. */
typedef struct DxBallDrawCaps {
    DxBallUInt size, caps, before_free[14], free_video_memory, remaining[62];
} DxBallDrawCaps;

/* Import boundary. A Windows adapter must bind these APIs before WinMain.
   Native oracles supply the same API contracts with controlled results. */
extern DxBallInt (DXBALL_DDCALL *dxball_window_get_cursor_pos)(DxBallPoint *);
extern DxBallInt (DXBALL_DDCALL *dxball_window_peek_message)(DxBallMessage *, DxBallHandle, DxBallUInt, DxBallUInt, DxBallUInt);
extern DxBallInt (DXBALL_DDCALL *dxball_window_wait_message)(void);
extern DxBallInt (DXBALL_DDCALL *dxball_window_get_message)(DxBallMessage *, DxBallHandle, DxBallUInt, DxBallUInt);
extern DxBallInt (DXBALL_DDCALL *dxball_window_translate_message)(const DxBallMessage *);
extern DxBallWindowResult (DXBALL_DDCALL *dxball_window_dispatch_message)(const DxBallMessage *);
extern DxBallWindowResult (DXBALL_DDCALL *dxball_window_default_window_proc)(DxBallHandle, DxBallUInt, DxBallHandle, DxBallWindowResult);
extern DxBallInt (DXBALL_DDCALL *dxball_window_post_message)(DxBallHandle, DxBallUInt, DxBallHandle, DxBallWindowResult);
extern void (DXBALL_DDCALL *dxball_window_post_quit_message)(DxBallInt);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_set_cursor)(DxBallHandle);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_set_capture)(DxBallHandle);
extern DxBallInt (DXBALL_DDCALL *dxball_window_release_capture)(void);
extern DxBallInt (DXBALL_DDCALL *dxball_window_get_version_ex)(DxBallVersionInfo *);

extern DxBallHandle (DXBALL_DDCALL *dxball_window_load_icon)(DxBallHandle, DxBallHandle);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_load_cursor)(DxBallHandle, DxBallHandle);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_stock_object)(DxBallInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_window_register_class)(const DxBallWindowClass *);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_create_window_ex)(DxBallUInt, const char *, const char *,
        DxBallUInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt,
        DxBallHandle, DxBallHandle, DxBallHandle, void *);
extern DxBallInt (DXBALL_DDCALL *dxball_window_show_window)(DxBallHandle, DxBallInt);
extern DxBallInt (DXBALL_DDCALL *dxball_window_update_window)(DxBallHandle);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_set_focus)(DxBallHandle);
extern DxBallInt (DXBALL_DDCALL *dxball_window_destroy_window)(DxBallHandle);
extern DxBallInt (DXBALL_DDCALL *dxball_window_message_box)(DxBallHandle, const char *, const char *, DxBallUInt);

typedef DxBallInt (DXBALL_DDCALL *DxBallDrawFactory)(void *, DxBallDDraw **, void *);
extern DxBallDrawFactory dxball_draw_factory_backend;
DxBallInt DXBALL_DDCALL dxball_direct_draw_create(void *, DxBallDDraw **, void *);
extern void (*dxball_process_exit_backend)(DxBallInt);
void dxball_process_exit(DxBallInt);

extern DxBallHandle (DXBALL_DDCALL *dxball_window_open_semaphore)(DxBallUInt,
    DxBallInt, const char *);
extern DxBallHandle (DXBALL_DDCALL *dxball_window_create_semaphore)(
    const DxBallSecurityAttributes *, DxBallInt, DxBallInt, const char *);
extern const char dxball_semaphore_open_name[], dxball_semaphore_create_name[];

/* Audio/MIDI controllers default to maintained owners, while their device APIs
   remain boundaries. Process termination binds the host CRT's exit. */
typedef struct DxBallPlatformOps {
    void (*prepare_sound)(DxBallHandle);
    void (*initialize_sound)(DxBallHandle);
    void (*pause_sound)(void);
    void (*resume_music)(void);
    void (*pause_music)(void);
    void (*close_music)(void);
    void (*release_audio)(void);
    void (*load_music)(const char *, DxBallInt);
    void (*exit_process)(DxBallInt);
} DxBallPlatformOps;
typedef struct DxBallKeyModeOps {
    void (*mode[4])(char);
    void (*mode4)(void);
} DxBallKeyModeOps;

extern DxBallPlatformOps dxball_platform_ops;
extern DxBallKeyModeOps dxball_key_mode_ops;
extern DxBallHandle dxball_main_window, dxball_instance_semaphore;
extern DxBallInt dxball_application_active, dxball_shift_pressed, dxball_control_pressed;
extern DxBallInt dxball_sound_suspended, dxball_software_only, dxball_low_video_memory;
extern DxBallPoint dxball_cursor_point;
extern DxBallDDClipper *dxball_direct_clipper;

DxBallHandle DXBALL_DDCALL dxball_win_main(DxBallHandle instance,
    DxBallHandle previous, DxBallHandle command_line, DxBallInt show);
DxBallWindowResult DXBALL_DDCALL dxball_window_proc(DxBallHandle window,
    DxBallUInt message, DxBallHandle wparam, DxBallWindowResult lparam);
DxBallInt dxball_initialize_fullscreen(DxBallHandle instance, DxBallInt show);
DxBallInt dxball_initialize_compatible(DxBallHandle instance, DxBallInt show);
DxBallHandle dxball_claim_instance(void);
void dxball_close_instance(void);
void dxball_detect_clock(void);
void dxball_dispatch_key(char key);
void dxball_game_key(char key);
void dxball_dispose_working_surface(DxBallInt fade);
void dxball_initialize_sprite_banks(void);

#endif
