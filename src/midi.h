#ifndef DXBALL_MIDI_H
#define DXBALL_MIDI_H
#include "resources.h"
#include <stddef.h>

typedef size_t DxBallMidiHandle;
typedef struct DxBallMidiHeader DxBallMidiHeader;
typedef struct DxBallMdsContext DxBallMdsContext;
struct DxBallMidiHeader {
    DxBallByte *data;
    DxBallUInt buffer_length, bytes_recorded;
    size_t user;
    DxBallUInt flags;
    DxBallMidiHeader *next;
    size_t reserved;
    DxBallUInt offset;
    size_t reserved_array[8];
};
struct DxBallMdsContext {
    DxBallUInt magic, time_division, buffer_capacity, format_flags;
    DxBallMidiHeader *buffers;
    DxBallMidiHandle stream;
    DxBallUInt state;
    DxBallInt buffer_count, pending_buffers;
};
typedef struct DxBallMdsInput {
    const DxBallByte *data;
    DxBallUInt length, remaining;
} DxBallMdsInput;
typedef struct DxBallMusic {
    DxBallMdsContext *context;
    DxBallInt playing;
} DxBallMusic;
typedef struct DxBallMidiProperty { DxBallUInt size, value; } DxBallMidiProperty;
typedef void (DXBALL_DDCALL *DxBallMidiCallback)(DxBallMidiHandle, DxBallUInt,
    size_t, DxBallMidiHeader *, size_t);

/* Kernel32/WinMM boundaries retain x86 stdcall. Typed host records grow with
   pointers; the real Windows adapter must use the i686 SDK layouts. */
typedef struct DxBallMidiApi {
    void *(DXBALL_DDCALL *local_alloc)(DxBallUInt, size_t);
    void *(DXBALL_DDCALL *local_free)(void *);
    DxBallMidiHandle (DXBALL_DDCALL *create_file)(const char *, DxBallUInt,
        DxBallUInt, void *, DxBallUInt, DxBallUInt, DxBallMidiHandle);
    DxBallUInt (DXBALL_DDCALL *file_size)(DxBallMidiHandle, DxBallUInt *);
    DxBallMidiHandle (DXBALL_DDCALL *create_mapping)(DxBallMidiHandle,
        void *, DxBallUInt, DxBallUInt, DxBallUInt, const char *);
    void *(DXBALL_DDCALL *map_view)(DxBallMidiHandle, DxBallUInt,
        DxBallUInt, DxBallUInt, size_t);
    DxBallInt (DXBALL_DDCALL *unmap_view)(const void *);
    DxBallInt (DXBALL_DDCALL *close_handle)(DxBallMidiHandle);
    DxBallMidiHandle (DXBALL_DDCALL *global_alloc)(DxBallUInt, size_t);
    void *(DXBALL_DDCALL *global_lock)(DxBallMidiHandle);
    DxBallMidiHandle (DXBALL_DDCALL *global_handle)(const void *);
    DxBallInt (DXBALL_DDCALL *global_unlock)(DxBallMidiHandle);
    DxBallMidiHandle (DXBALL_DDCALL *global_free)(DxBallMidiHandle);
    DxBallUInt (DXBALL_DDCALL *stream_open)(DxBallMidiHandle *, DxBallUInt *,
        DxBallUInt, DxBallMidiCallback, size_t, DxBallUInt);
    DxBallUInt (DXBALL_DDCALL *stream_property)(DxBallMidiHandle,
        DxBallMidiProperty *, DxBallUInt);
    DxBallUInt (DXBALL_DDCALL *prepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
    DxBallUInt (DXBALL_DDCALL *stream_out)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
    DxBallUInt (DXBALL_DDCALL *stream_restart)(DxBallMidiHandle);
    DxBallUInt (DXBALL_DDCALL *stream_pause)(DxBallMidiHandle);
    DxBallUInt (DXBALL_DDCALL *out_reset)(DxBallMidiHandle);
    DxBallUInt (DXBALL_DDCALL *unprepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
    DxBallUInt (DXBALL_DDCALL *stream_close)(DxBallMidiHandle);
} DxBallMidiApi;

extern DxBallMidiApi dxball_midi_api;
extern DxBallMusic *dxball_music;
DxBallInt dxball_open_mds(DxBallMdsContext **, const void *, DxBallUInt, DxBallByte);
DxBallInt dxball_parse_mds(DxBallMdsContext *, const void *, DxBallUInt);
DxBallInt dxball_expand_mds_events(const DxBallMdsInput *, DxBallMidiHeader *);
DxBallInt dxball_release_mds(DxBallMdsContext *);
DxBallInt dxball_play_mds(DxBallMdsContext *, DxBallByte);
DxBallInt dxball_pause_mds(DxBallMdsContext *);
DxBallInt dxball_stop_mds(DxBallMdsContext *);
void DXBALL_DDCALL dxball_midi_callback(DxBallMidiHandle, DxBallUInt,
    size_t, DxBallMidiHeader *, size_t);
DxBallInt dxball_load_music(const char *, DxBallInt);
void dxball_resume_music(void);
void dxball_pause_music(void);
void dxball_restart_music(void);
void dxball_close_music(void);
#endif
