#ifndef DXBALL_RUNTIME_H
#define DXBALL_RUNTIME_H

#include "core.h"

/* Win32 LARGE_INTEGER fields used by the original clock. HighPart is written
   by the API but deliberately ignored by the recovered clock arithmetic. */
typedef struct DxBallCounter { DxBallUInt low; DxBallInt high; } DxBallCounter;
typedef struct DxBallClockOps {
    DxBallUInt (DXBALL_DDCALL *time_ms)(void);
    DxBallInt (DXBALL_DDCALL *frequency)(DxBallCounter *value);
    DxBallInt (DXBALL_DDCALL *counter)(DxBallCounter *value);
} DxBallClockOps;

/* Resource parsing/capture defaults to maintained source. Other operations
   require a platform/UI implementation; an operation trace is not its body. */
typedef struct DxBallRuntimeOps {
    void (*load_saved_palette)(const char *path);
    void (*palette_transition)(DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt);
    void (*clear_surface)(DxBallSurface surface, DxBallInt color);
    void (*reset_regions)(void);
    void (*load_pcx)(DxBallDDSurface *, const char *, DxBallInt, DxBallInt, DxBallInt);
    void (*load_sprite_bank)(DxBallInt, DxBallInt, const char *);
    void (*capture_sprite)(DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt);
    void (*load_sound)(DxBallInt slot, const char *path);
    void (*bind_board_surface)(DxBallSurface surface);
    void (*bind_display_surface)(DxBallSurface surface);
    void (*draw_text)(DxBallInt x, DxBallInt y, DxBallInt count, const char *text);
    void (*draw_centered_text)(DxBallInt x, DxBallInt y, DxBallInt count, const char *text);
    void (*release_sounds)(void);
    void (*release_sprite_banks)(void);
    void (*finalize_game_resources)(void);
} DxBallRuntimeOps;

/* Modes 0 (menu), 1 (game) and 4 (splash) default to maintained source.
   Pending valid modes require configured callbacks. The original switch does
   nothing for out-of-range integers. */
typedef struct DxBallModeOps {
    void (*initialize[5])(void);
    void (*redraw[5])(void);
    void (*frame[5])(void);
    void (*cleanup[5])(DxBallInt fade);
    void (*reinitialize_device)(void);
    void (*synchronize_surface)(void);
} DxBallModeOps;

extern DxBallClockOps dxball_clock_ops;
extern DxBallRuntimeOps dxball_runtime_ops;
extern DxBallModeOps dxball_mode_ops;
extern DxBallInt dxball_high_resolution_clock;
extern DxBallUInt dxball_clock_divisor;
extern DxBallInt dxball_paddle_frame, dxball_paddle_overlay_sprite, dxball_paddle_overlay_width;
extern DxBallUInt dxball_paddle_tick, dxball_paddle_overlay_deadline;
extern DxBallInt dxball_lightning_x, dxball_lightning_y, dxball_lightning_frames;
extern DxBallInt dxball_device_reset_requested, dxball_surface_restore_requested;
extern DxBallInt dxball_display_buffer_count;
extern DxBallSurface dxball_primary_surface, dxball_secondary_surface;

DxBallUInt dxball_current_time(void);
DxBallInt dxball_elapsed(DxBallUInt start, DxBallUInt interval);
void dxball_draw_paddle(void);
void dxball_refresh_score(void);
void dxball_draw_score(void);
void dxball_clear_all_entities(void);
void dxball_finish_game(void);
void dxball_reset_round(void);
void dxball_restart_round(void);
void dxball_initialize_game(void);
void dxball_redraw_game(void);
void dxball_dispose_game(DxBallInt fade);
void dxball_initialize_mode(void);
void dxball_redraw_mode(void);
void dxball_cleanup_mode(DxBallInt fade);
DxBallInt dxball_dispatch_frame(void);

#endif
