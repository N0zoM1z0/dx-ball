#include <SDL.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sound.h"
void dxball_sdl_music_mix(float *, int);

typedef struct NativeSoundBuffer {
    const DxBallSoundBufferVTable *vtable;
    struct NativeSoundBuffer *next;
    uint8_t *samples;
    uint32_t bytes, frequency;
    uint16_t channels, bits;
    int volume, pan, playing, looping;
    double frame_position;
} NativeSoundBuffer;
typedef struct NativeSoundDevice {
    const DxBallSoundDeviceVTable *vtable;
} NativeSoundDevice;

static SDL_AudioDeviceID audio_device;
static NativeSoundBuffer *buffers;
static NativeSoundDevice sound_device;

static void audio_mix(void *userdata, Uint8 *stream, int length) {
    (void)userdata;
    float *output = (float *)stream;
    int frames = length / (int)(2 * sizeof(float));
    memset(stream, 0, (size_t)length);
    for (NativeSoundBuffer *buffer = buffers; buffer; buffer = buffer->next) {
        if (!buffer->playing || !buffer->samples || !buffer->channels || !buffer->bits) continue;
        int bytes_per_frame = buffer->channels * buffer->bits / 8;
        if (!bytes_per_frame) continue;
        int total_frames = (int)(buffer->bytes / bytes_per_frame);
        if (!total_frames) continue;
        double gain = pow(10.0, buffer->volume / 2000.0);
        double left_gain = gain * (buffer->pan > 0 ? 1.0 - buffer->pan / 10000.0 : 1.0);
        double right_gain = gain * (buffer->pan < 0 ? 1.0 + buffer->pan / 10000.0 : 1.0);
        double step = (double)buffer->frequency / 44100.0;
        if (step <= 0.0) step = 1.0;
        for (int frame = 0; frame < frames; ++frame) {
            int index = (int)buffer->frame_position;
            if (index >= total_frames) {
                if (!buffer->looping) { buffer->playing = 0; break; }
                buffer->frame_position = 0.0;
                index = 0;
            }
            float left, right;
            if (buffer->bits == 8) {
                const uint8_t *sample = buffer->samples + index * bytes_per_frame;
                left = ((int)sample[0] - 128) / 128.0f;
                right = buffer->channels > 1 ? ((int)sample[1] - 128) / 128.0f : left;
            } else if (buffer->bits == 16) {
                const uint8_t *sample = buffer->samples + index * bytes_per_frame;
                int16_t l, r;
                memcpy(&l, sample, 2);
                if (buffer->channels > 1) memcpy(&r, sample + 2, 2);
                else r = l;
                left = l / 32768.0f;
                right = r / 32768.0f;
            } else { buffer->playing = 0; break; }
            output[frame * 2] += (float)(left * left_gain);
            output[frame * 2 + 1] += (float)(right * right_gain);
            buffer->frame_position += step;
        }
    }
    dxball_sdl_music_mix(output, frames);
    for (int sample = 0; sample < frames * 2; ++sample) {
        if (output[sample] > 1.0f) output[sample] = 1.0f;
        if (output[sample] < -1.0f) output[sample] = -1.0f;
    }
}
static void audio_lock(void) { if (audio_device) SDL_LockAudioDevice(audio_device); }
static void audio_unlock(void) { if (audio_device) SDL_UnlockAudioDevice(audio_device); }
static NativeSoundBuffer *as_buffer(DxBallSoundBuffer *buffer) { return (NativeSoundBuffer *)buffer; }
static DxBallUInt buffer_release(DxBallSoundBuffer *buffer) {
    NativeSoundBuffer *item = as_buffer(buffer);
    audio_lock();
    NativeSoundBuffer **link = &buffers;
    while (*link && *link != item) link = &(*link)->next;
    if (*link) *link = item->next;
    audio_unlock();
    free(item->samples);
    free(item);
    return 0;
}
static DxBallInt buffer_get_volume(DxBallSoundBuffer *buffer, DxBallInt *value) {
    *value = as_buffer(buffer)->volume; return 0;
}
static DxBallInt buffer_get_pan(DxBallSoundBuffer *buffer, DxBallInt *value) {
    *value = as_buffer(buffer)->pan; return 0;
}
static DxBallInt buffer_get_frequency(DxBallSoundBuffer *buffer, DxBallUInt *value) {
    *value = as_buffer(buffer)->frequency; return 0;
}
static DxBallInt buffer_get_status(DxBallSoundBuffer *buffer, DxBallUInt *value) {
    *value = as_buffer(buffer)->playing ? 1 : 0; return 0;
}
static DxBallInt buffer_lock(DxBallSoundBuffer *buffer, DxBallUInt offset, DxBallUInt bytes,
    void **first, DxBallUInt *first_bytes, void **second, DxBallUInt *second_bytes, DxBallUInt flags) {
    (void)flags;
    NativeSoundBuffer *item = as_buffer(buffer);
    if (offset > item->bytes || bytes > item->bytes - offset) return -1;
    *first = item->samples + offset;
    *first_bytes = bytes;
    *second = NULL;
    *second_bytes = 0;
    return 0;
}
static DxBallInt buffer_play(DxBallSoundBuffer *buffer, DxBallUInt reserved,
    DxBallUInt priority, DxBallUInt flags) {
    (void)reserved; (void)priority;
    NativeSoundBuffer *item = as_buffer(buffer);
    audio_lock();
    item->playing = item->bytes > 0;
    item->looping = (flags & 1) != 0;
    item->frame_position = 0.0;
    audio_unlock();
    return 0;
}
static DxBallInt buffer_position(DxBallSoundBuffer *buffer, DxBallUInt position) {
    NativeSoundBuffer *item = as_buffer(buffer);
    audio_lock();
    item->frame_position = item->channels && item->bits ?
        (double)position / (item->channels * item->bits / 8) : 0.0;
    audio_unlock();
    return 0;
}
static DxBallInt buffer_set_volume(DxBallSoundBuffer *buffer, DxBallInt value) {
    audio_lock(); as_buffer(buffer)->volume = value; audio_unlock(); return 0;
}
static DxBallInt buffer_set_pan(DxBallSoundBuffer *buffer, DxBallInt value) {
    audio_lock(); as_buffer(buffer)->pan = value; audio_unlock(); return 0;
}
static DxBallInt buffer_set_frequency(DxBallSoundBuffer *buffer, DxBallUInt value) {
    audio_lock(); as_buffer(buffer)->frequency = value; audio_unlock(); return 0;
}
static DxBallInt buffer_stop(DxBallSoundBuffer *buffer) {
    audio_lock(); as_buffer(buffer)->playing = 0; audio_unlock(); return 0;
}
static DxBallInt buffer_unlock(DxBallSoundBuffer *buffer, void *first, DxBallUInt first_bytes,
    void *second, DxBallUInt second_bytes) {
    (void)buffer; (void)first; (void)first_bytes; (void)second; (void)second_bytes; return 0;
}
static DxBallInt buffer_restore(DxBallSoundBuffer *buffer) { (void)buffer; return 0; }
static const DxBallSoundBufferVTable buffer_methods = {
    .release = buffer_release,
    .get_volume = buffer_get_volume, .get_pan = buffer_get_pan,
    .get_frequency = buffer_get_frequency, .get_status = buffer_get_status,
    .lock = buffer_lock, .play = buffer_play, .set_current_position = buffer_position,
    .set_volume = buffer_set_volume, .set_pan = buffer_set_pan,
    .set_frequency = buffer_set_frequency, .stop = buffer_stop,
    .unlock = buffer_unlock, .restore = buffer_restore
};
static DxBallUInt device_release(DxBallSoundDevice *device) {
    (void)device; return 0;
}
static DxBallInt device_create_buffer(DxBallSoundDevice *device,
    const DxBallSoundBufferDesc *desc, DxBallSoundBuffer **out, void *outer) {
    (void)device; (void)outer;
    NativeSoundBuffer *buffer = calloc(1, sizeof(*buffer));
    if (!buffer) return -1;
    buffer->vtable = &buffer_methods;
    buffer->bytes = desc->bytes;
    if (desc->bytes) {
        buffer->samples = malloc(desc->bytes);
        if (!buffer->samples) { free(buffer); return -1; }
        memset(buffer->samples, 128, desc->bytes);
    }
    if (desc->format) {
        const uint8_t *format = (const uint8_t *)desc->format;
        uint16_t kind;
        memcpy(&kind, format, 2);
        if (kind != 1) { free(buffer->samples); free(buffer); return -1; }
        memcpy(&buffer->channels, format + 2, 2);
        memcpy(&buffer->frequency, format + 4, 4);
        memcpy(&buffer->bits, format + 14, 2);
    }
    audio_lock();
    buffer->next = buffers;
    buffers = buffer;
    audio_unlock();
    *out = (DxBallSoundBuffer *)buffer;
    return 0;
}
static DxBallInt device_cooperative(DxBallSoundDevice *device,
    DxBallHandle window, DxBallUInt flags) {
    (void)device; (void)window; (void)flags; return 0;
}
static const DxBallSoundDeviceVTable device_methods = {
    .release = device_release, .create_buffer = device_create_buffer,
    .set_cooperative_level = device_cooperative
};
DxBallInt dxball_sdl_sound_create(void *guid, DxBallSoundDevice **out, void *outer) {
    (void)guid; (void)outer;
    if (!audio_device) {
        SDL_AudioSpec wanted, obtained;
        SDL_zero(wanted);
        wanted.freq = 44100;
        wanted.format = AUDIO_F32SYS;
        wanted.channels = 2;
        wanted.samples = 512;
        wanted.callback = audio_mix;
        audio_device = SDL_OpenAudioDevice(NULL, 0, &wanted, &obtained, 0);
        if (!audio_device || obtained.freq != 44100 || obtained.format != AUDIO_F32SYS ||
            obtained.channels != 2) return (DxBallInt)0x88780078u;
        SDL_PauseAudioDevice(audio_device, 0);
    }
    sound_device.vtable = &device_methods;
    *out = (DxBallSoundDevice *)&sound_device;
    return 0;
}
void dxball_sdl_sound_close(void) {
    if (audio_device) SDL_CloseAudioDevice(audio_device);
    audio_device = 0;
}

void dxball_sdl_audio_lock(void) { audio_lock(); }
void dxball_sdl_audio_unlock(void) { audio_unlock(); }
