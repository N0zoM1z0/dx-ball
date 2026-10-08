#ifndef DXBALL_SOUND_H
#define DXBALL_SOUND_H

#include "platform.h"

#define DXBALL_SOUND_COUNT 50

typedef struct DxBallSoundDevice DxBallSoundDevice;
typedef struct DxBallSoundBuffer DxBallSoundBuffer;
typedef void (DXBALL_DDCALL *DxBallUnknownSoundMethod)(void);

/* DirectSound 1 descriptor: five fields, 20 bytes on the original i686 ABI.
   The format points into the WAV's fmt chunk; it is not a copied SDK struct. */
typedef struct DxBallSoundBufferDesc {
    DxBallUInt size, flags, bytes, reserved;
    const void *format;
} DxBallSoundBufferDesc;
typedef struct DxBallSoundDeviceVTable {
    DxBallUnknownSoundMethod query_interface, add_ref;
    DxBallUInt (DXBALL_DDCALL *release)(DxBallSoundDevice *);
    DxBallInt (DXBALL_DDCALL *create_buffer)(DxBallSoundDevice *,
        const DxBallSoundBufferDesc *, DxBallSoundBuffer **, void *);
    DxBallUnknownSoundMethod get_caps, duplicate_buffer;
    DxBallInt (DXBALL_DDCALL *set_cooperative_level)(DxBallSoundDevice *, DxBallHandle, DxBallUInt);
} DxBallSoundDeviceVTable;
struct DxBallSoundDevice { const DxBallSoundDeviceVTable *vtable; };
typedef struct DxBallSoundBufferVTable {
    DxBallUnknownSoundMethod query_interface, add_ref;
    DxBallUInt (DXBALL_DDCALL *release)(DxBallSoundBuffer *);
    DxBallUnknownSoundMethod get_caps, get_current_position, get_format;
    DxBallInt (DXBALL_DDCALL *get_volume)(DxBallSoundBuffer *, DxBallInt *);
    DxBallInt (DXBALL_DDCALL *get_pan)(DxBallSoundBuffer *, DxBallInt *);
    DxBallInt (DXBALL_DDCALL *get_frequency)(DxBallSoundBuffer *, DxBallUInt *);
    DxBallInt (DXBALL_DDCALL *get_status)(DxBallSoundBuffer *, DxBallUInt *);
    DxBallUnknownSoundMethod initialize;
    DxBallInt (DXBALL_DDCALL *lock)(DxBallSoundBuffer *, DxBallUInt, DxBallUInt,
        void **, DxBallUInt *, void **, DxBallUInt *, DxBallUInt);
    DxBallInt (DXBALL_DDCALL *play)(DxBallSoundBuffer *, DxBallUInt, DxBallUInt, DxBallUInt);
    DxBallInt (DXBALL_DDCALL *set_current_position)(DxBallSoundBuffer *, DxBallUInt);
    DxBallUnknownSoundMethod set_format;
    DxBallInt (DXBALL_DDCALL *set_volume)(DxBallSoundBuffer *, DxBallInt);
    DxBallInt (DXBALL_DDCALL *set_pan)(DxBallSoundBuffer *, DxBallInt);
    DxBallInt (DXBALL_DDCALL *set_frequency)(DxBallSoundBuffer *, DxBallUInt);
    DxBallInt (DXBALL_DDCALL *stop)(DxBallSoundBuffer *);
    DxBallInt (DXBALL_DDCALL *unlock)(DxBallSoundBuffer *, void *, DxBallUInt, void *, DxBallUInt);
    DxBallInt (DXBALL_DDCALL *restore)(DxBallSoundBuffer *);
} DxBallSoundBufferVTable;
struct DxBallSoundBuffer { const DxBallSoundBufferVTable *vtable; };

/* Observed fields occupy 36 bytes on x86. The original requests 37 bytes;
   the purpose of the extra allocated byte remains unknown. */
typedef struct DxBallSound {
    DxBallSoundBuffer *buffer;
    char filename[20];
    DxBallUInt frequency;
    DxBallInt pan, volume;
} DxBallSound;

/* Actual imports and the CRT allocation boundary. Allocation callbacks do not
   reconstruct the original heap/new-handler implementation. */
typedef struct DxBallSoundApi {
    DxBallInt (DXBALL_DDCALL *create_device)(void *, DxBallSoundDevice **, void *);
    DxBallHandle (DXBALL_DDCALL *create_file)(const char *, DxBallUInt, DxBallUInt,
        void *, DxBallUInt, DxBallUInt, DxBallHandle);
    DxBallUInt (DXBALL_DDCALL *file_size)(DxBallHandle, DxBallUInt *);
    DxBallInt (DXBALL_DDCALL *read_file)(DxBallHandle, void *, DxBallUInt, DxBallUInt *, void *);
    DxBallInt (DXBALL_DDCALL *close_handle)(DxBallHandle);
    void *(*allocate)(size_t);
    void (*deallocate)(void *);
} DxBallSoundApi;

extern DxBallSoundApi dxball_sound_api;
extern DxBallSoundDevice *dxball_sound_device;
extern DxBallSoundBuffer *dxball_primary_sound;
extern DxBallSound *dxball_sounds[DXBALL_SOUND_COUNT];
extern const char dxball_file_fallback_prefix[];

void dxball_prepare_sound(DxBallHandle window);
void dxball_initialize_sound(DxBallHandle window);
void dxball_pause_sound(void);
void dxball_release_audio(void);
void dxball_release_sounds(void);
void dxball_stop_all_sounds(void);
void dxball_release_sound(DxBallInt slot);
void dxball_load_sound(DxBallInt slot, const char *path);
void dxball_play_sound(DxBallInt slot, DxBallInt frequency, DxBallInt pan, DxBallInt volume);
void dxball_update_sound(DxBallInt slot, DxBallInt frequency, DxBallInt pan, DxBallInt volume);
void dxball_stop_sound(DxBallInt slot);
void dxball_set_sound_frequency(DxBallInt slot, DxBallUInt frequency);
void dxball_set_sound_pan(DxBallInt slot, DxBallInt pan);
void dxball_set_sound_volume(DxBallInt slot, DxBallInt volume);
void dxball_restore_sounds(void);
DxBallInt dxball_parse_wave(const void *file, const void **format,
    const void **data, DxBallUInt *bytes);
DxBallInt dxball_create_sound_buffer(DxBallSoundDevice *device,
    DxBallSoundBuffer **buffer, const void *format, DxBallUInt bytes);
void *dxball_load_binary_file(const char *path, void *destination, DxBallInt allocate);

#endif
