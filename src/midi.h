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
typedef struct DxBallMdsFormat {
    DxBallUInt time_division, buffer_capacity, flags;
} DxBallMdsFormat;
struct DxBallMdsContext {
    DxBallUInt magic;
    DxBallMdsFormat format;
    DxBallMidiHeader *buffers;
    DxBallMidiHandle stream;
    DxBallUInt state;
    DxBallInt buffer_count, pending_buffers;
};
typedef struct DxBallMusic {
    DxBallMdsContext *context;
    DxBallInt playing;
#ifdef __cplusplus
    static void *operator new(size_t bytes);
    static void operator delete(void *memory);
#endif
} DxBallMusic;
typedef struct DxBallMidiProperty { DxBallUInt size, value; } DxBallMidiProperty;
typedef void (DXBALL_DDCALL *DxBallMidiCallback)(DxBallMidiHandle, DxBallUInt,
    size_t, DxBallMidiHeader *, size_t);

/* Kernel32/WinMM boundaries retain x86 stdcall. Typed host records grow with
   pointers; the real Windows adapter must use the i686 SDK layouts. */
extern void *(DXBALL_DDCALL *dxball_midi_local_alloc)(DxBallUInt, size_t);
extern void *(DXBALL_DDCALL *dxball_midi_local_free)(void *);
extern DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_create_mapping)(DxBallMidiHandle,
        void *, DxBallUInt, DxBallUInt, DxBallUInt, const char *);
extern void *(DXBALL_DDCALL *dxball_midi_map_view)(DxBallMidiHandle, DxBallUInt,
        DxBallUInt, DxBallUInt, size_t);
extern DxBallInt (DXBALL_DDCALL *dxball_midi_unmap_view)(const void *);
extern DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_alloc)(DxBallUInt, size_t);
extern void *(DXBALL_DDCALL *dxball_midi_global_lock)(DxBallMidiHandle);
extern DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_handle)(const void *);
extern DxBallInt (DXBALL_DDCALL *dxball_midi_global_unlock)(DxBallMidiHandle);
extern DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_free)(DxBallMidiHandle);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_open)(DxBallMidiHandle *, DxBallUInt *,
        DxBallUInt, DxBallMidiCallback, size_t, DxBallUInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_property)(DxBallMidiHandle,
        DxBallMidiProperty *, DxBallUInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_prepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_out)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_restart)(DxBallMidiHandle);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_pause)(DxBallMidiHandle);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_out_reset)(DxBallMidiHandle);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_unprepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
extern DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_close)(DxBallMidiHandle);

extern DxBallMusic *dxball_music;
DxBallInt dxball_open_mds(DxBallMdsContext **, const void *, DxBallUInt, DxBallByte);
DxBallInt dxball_parse_mds(DxBallMdsContext *, const void *, DxBallUInt);
DxBallInt dxball_expand_mds_events(const DxBallMidiHeader *, DxBallMidiHeader *);
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
