#include "allocator.h"
#include "sound.h"
#include "directx_factory.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>

DxBallSoundApi dxball_sound_api = { NULL, dxball_malloc_bytes, dxball_heap_release };
DxBallSoundDevice *dxball_sound_device;
DxBallSoundBuffer *dxball_primary_sound;
DxBallSound *dxball_sounds[DXBALL_SOUND_COUNT];

static const char occupied_message[] =
    "Another Windows application has control of the sound system. \n"
    "ABORT will exit.  RETRY will attempt to get sound system after other application releases it.  "
    "IGNORE will continue without sound effects.";
static const char no_card_message[] =
    "Direct X can not find your sound card.  \nDo you wish to continue this application without sound?";
static const char create_message[] =
    "Direct X failed to start the sound system.  \nDo you wish to continue this application without sound?";
static const char cooperate_message[] =
    "Direct X sound system failed to get the proper cooperation level with another application.  \n"
    "Do you wish to continue this program without sound?";
static const char primary_create_message[] =
    "Direct X sound system failed to initialize. \n (lpPrimaryBuffer create) \n"
    "Do you wish to continue this program without sound?";
static const char primary_play_message[] =
    "Direct X sound system failed to initialize. \n (lpPrimaryBuffer playLooping) \n"
    "Do you wish to continue this program without sound?";

/* FUNCTION: DXBALL 0x00405120 */
void dxball_initialize_sound(DxBallHandle window)
{
    struct {
        DxBallSoundBufferDesc descriptor;
        DxBallInt slot, retry, result;
    } initialization;

    if (dxball_sound_device != NULL) return;
    {
        DxBallInt response;
        initialization.retry = 1;
        while (initialization.retry != 0) {
            initialization.result = DirectSoundCreate(NULL, &dxball_sound_device, NULL);
            if (dxball_direct_draw != NULL) {
                if (initialization.result != 0) {
                    dxball_sound_device = NULL;
                    return;
                } else {
                    initialization.retry = 0;
                }
            } else {
                switch (initialization.result) {
                case 0:
                    initialization.retry = 0;
                    break;
                case (DxBallInt)0x8878000aUL:
                    response = dxball_window_message_box(window,
                        occupied_message, "DX-Ball", 0x42);
                    switch (response) {
                    case 3:
                        exit(10);
                        break;
                    case 4:
                        break;
                    case 5:
                        dxball_sound_device = NULL;
                        return;
                        break;
                    }
                    break;
                case (DxBallInt)0x88780078UL:
                    response = dxball_window_message_box(window,
                        no_card_message, "DX-Ball", 0x24);
                    switch (response) {
                    case 6:
                        dxball_sound_device = NULL;
                        return;
                        break;
                    case 7:
                        exit(11);
                        break;
                    default:
                        dxball_sound_device = NULL;
                        return;
                    }
                    break;
                default:
                    response = dxball_window_message_box(window,
                        create_message, "DX-Ball", 0x24);
                    switch (response) {
                    case 6:
                        dxball_sound_device = NULL;
                        return;
                        break;
                    case 7:
                        exit(12);
                        break;
                    default:
                        dxball_sound_device = NULL;
                        return;
                    }
                }
            }
        }
        initialization.result = dxball_sound_device->vtable->set_cooperative_level(
            dxball_sound_device, window, 1);
        if (dxball_direct_draw != NULL) {
            if (initialization.result != 0) {
                dxball_sound_device->vtable->release(dxball_sound_device);
                dxball_sound_device = NULL;
                return;
            }
        } else {
            if (initialization.result != 0) {
                switch (initialization.result) {
                default:
                    response = dxball_window_message_box(window,
                        cooperate_message, "DX-Ball", 0x24);
                    switch (response) {
                    case 6:
                        dxball_sound_device->vtable->release(dxball_sound_device);
                        dxball_sound_device = NULL;
                        return;
                        break;
                    case 7:
                        exit(13);
                        break;
                    default:
                        dxball_sound_device->vtable->release(dxball_sound_device);
                        dxball_sound_device = NULL;
                        return;
                    }
                }
            }
        }
        memset(&initialization.descriptor, 0, sizeof(initialization.descriptor));
        initialization.descriptor.size = 20;
        initialization.descriptor.flags = 1;
        initialization.result = dxball_sound_device->vtable->create_buffer(dxball_sound_device,
            &initialization.descriptor, &dxball_primary_sound, NULL);
        if (dxball_direct_draw != NULL) {
            if (initialization.result != 0) {
                if (dxball_primary_sound != NULL) {
                    dxball_primary_sound->vtable->release(dxball_primary_sound);
                    dxball_primary_sound = NULL;
                }
                dxball_sound_device->vtable->release(dxball_sound_device);
                dxball_sound_device = NULL;
                return;
            }
        } else {
            if (initialization.result != 0) {
                response = dxball_window_message_box(window,
                    primary_create_message, "DX-Ball", 0x24);
                switch (response) {
                case 6:
                    if (dxball_primary_sound != NULL) {
                        dxball_primary_sound->vtable->release(dxball_primary_sound);
                        dxball_primary_sound = NULL;
                    }
                    dxball_sound_device->vtable->release(dxball_sound_device);
                    dxball_sound_device = NULL;
                    return;
                    break;
                case 7:
                    exit(13);
                    break;
                default:
                    if (dxball_primary_sound != NULL) {
                        dxball_primary_sound->vtable->release(dxball_primary_sound);
                        dxball_primary_sound = NULL;
                    }
                    dxball_sound_device->vtable->release(dxball_sound_device);
                    dxball_sound_device = NULL;
                    return;
                }
            }
        }
        initialization.result = dxball_primary_sound->vtable->play(dxball_primary_sound, 0, 0, 1);
        if (dxball_direct_draw != NULL) {
            if (initialization.result != 0) {
                dxball_primary_sound->vtable->release(dxball_primary_sound);
                dxball_primary_sound = NULL;
                dxball_sound_device->vtable->release(dxball_sound_device);
                dxball_sound_device = NULL;
                return;
            }
        } else {
            if (initialization.result != 0) {
                response = dxball_window_message_box(window,
                    primary_play_message, "DX-Ball", 0x24);
                switch (response) {
                case 6:
                    dxball_primary_sound->vtable->release(dxball_primary_sound);
                    dxball_primary_sound = NULL;
                    dxball_sound_device->vtable->release(dxball_sound_device);
                    dxball_sound_device = NULL;
                    return;
                    break;
                case 7:
                    exit(13);
                    break;
                default:
                    dxball_primary_sound->vtable->release(dxball_primary_sound);
                    dxball_primary_sound = NULL;
                    dxball_sound_device->vtable->release(dxball_sound_device);
                    dxball_sound_device = NULL;
                    return;
                }
            }
        }
        for (initialization.slot = 0; initialization.slot < DXBALL_SOUND_COUNT; ++initialization.slot) {
            if (dxball_sounds[initialization.slot] != NULL) {
                char filename[256];
                strcpy(filename, dxball_sounds[initialization.slot]->filename);
                dxball_load_sound(initialization.slot, filename);
            }
        }
        return;
    }
}

void dxball_prepare_sound(DxBallHandle window)
{
    dxball_release_sounds();
    dxball_initialize_sound(window);
    return;
}

void dxball_release_audio(void)
{
    dxball_release_sounds();
    dxball_pause_sound();
    return;
}

/* FUNCTION: DXBALL 0x004057D0 */
void dxball_pause_sound(void)
{
    DxBallInt slot;
    dxball_stop_all_sounds();
    for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) {
        if (dxball_sounds[slot] != NULL && dxball_sounds[slot]->buffer != NULL) {
            dxball_sounds[slot]->buffer->vtable->release(dxball_sounds[slot]->buffer);
            dxball_sounds[slot]->buffer = NULL;
        }
    }
    if (dxball_primary_sound != NULL) {
        dxball_primary_sound->vtable->release(dxball_primary_sound);
        dxball_primary_sound = NULL;
    }
    if (dxball_sound_device != NULL) {
        dxball_sound_device->vtable->release(dxball_sound_device);
        dxball_sound_device = NULL;
    }
    return;
}

void dxball_release_sounds(void)
{
    DxBallInt slot;
    for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) dxball_release_sound(slot);
    return;
}

void dxball_stop_all_sounds(void)
{
    DxBallInt slot;
    for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) dxball_stop_sound(slot);
    return;
}

/* FUNCTION: DXBALL 0x004058F0 */
void dxball_release_sound(DxBallInt slot)
{
    if (dxball_sounds[slot] == NULL) return;
    if (dxball_sound_device != NULL && dxball_sounds[slot]->buffer != NULL) {
        dxball_sounds[slot]->buffer->vtable->release(dxball_sounds[slot]->buffer);
        dxball_sounds[slot]->buffer = NULL;
    }
    dxball_heap_release(dxball_sounds[slot]);
    dxball_sounds[slot] = NULL;
    return;
}

/* FUNCTION: DXBALL 0x00405990 */
void dxball_load_sound(DxBallInt slot, const char *path)
{
    void *file, *first, *second;
    const void *format, *data;
    DxBallUInt bytes, first_bytes, second_bytes;
    DxBallSound *sound;
    DxBallInt result;

    file = NULL;
    dxball_release_sound(slot);
    sound = (DxBallSound *)dxball_runtime_malloc(sizeof(*sound) + 1);
    if (sound == NULL) exit(1);
    dxball_sounds[slot] = sound;
    file = dxball_load_binary_file(path, file, 1);
    if (file == NULL) {
        dxball_heap_release(dxball_sounds[slot]);
        return;
    }
    if (!dxball_parse_wave(file, &format, &data, &bytes)) {
        dxball_heap_release(file);
        dxball_heap_release(dxball_sounds[slot]);
        return;
    }
    if (dxball_sound_device != NULL) {
        result = dxball_create_sound_buffer(dxball_sound_device,
            &dxball_sounds[slot]->buffer, format, bytes);
        if (result != 0) {
            dxball_heap_release(file);
            dxball_heap_release(dxball_sounds[slot]);
            return;
        }
        result = dxball_sounds[slot]->buffer->vtable->lock(
            dxball_sounds[slot]->buffer, 0, bytes,
            &first, &first_bytes, &second, &second_bytes, 0);
        if (result != 0) {
            dxball_heap_release(file);
            dxball_heap_release(dxball_sounds[slot]);
            return;
        }
        memcpy(first, data, first_bytes);
        if (second_bytes != 0)
            memcpy(second, (const DxBallByte *)data + first_bytes, second_bytes);
        dxball_sounds[slot]->buffer->vtable->unlock(
            dxball_sounds[slot]->buffer, first, first_bytes, second, second_bytes);
        dxball_sounds[slot]->buffer->vtable->get_frequency(
            dxball_sounds[slot]->buffer, &dxball_sounds[slot]->frequency);
        dxball_sounds[slot]->buffer->vtable->get_pan(
            dxball_sounds[slot]->buffer, &dxball_sounds[slot]->pan);
        dxball_sounds[slot]->buffer->vtable->get_volume(
            dxball_sounds[slot]->buffer, &dxball_sounds[slot]->volume);
    } else {
        dxball_sounds[slot]->buffer = NULL;
    }
    dxball_heap_release(file);
    strcpy(dxball_sounds[slot]->filename, path);
    return;
}

/* FUNCTION: DXBALL 0x00405C50 */
void dxball_play_sound(DxBallInt slot, DxBallInt frequency, DxBallInt pan, DxBallInt volume)
{
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    if (frequency != 0)
        dxball_sounds[slot]->buffer->vtable->set_frequency(
            dxball_sounds[slot]->buffer, (DxBallUInt)frequency);
    if (pan != 0)
        dxball_sounds[slot]->buffer->vtable->set_pan(dxball_sounds[slot]->buffer, pan);
    if (volume != 0)
        dxball_sounds[slot]->buffer->vtable->set_volume(dxball_sounds[slot]->buffer, volume);
    result = dxball_sounds[slot]->buffer->vtable->play(dxball_sounds[slot]->buffer, 0, 0, 0);
    if (result == 2 || (DxBallUInt)result == 0x88780096UL) {
        dxball_restore_sounds();
        dxball_sounds[slot]->buffer->vtable->play(dxball_sounds[slot]->buffer, 0, 0, 0);
    }
    return;
}

/* FUNCTION: DXBALL 0x00405D80 */
void dxball_update_sound(DxBallInt slot, DxBallInt frequency, DxBallInt pan, DxBallInt volume)
{
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    if (frequency != 0)
        dxball_sounds[slot]->buffer->vtable->set_frequency(
            dxball_sounds[slot]->buffer, (DxBallUInt)frequency);
    if (pan != 0)
        dxball_sounds[slot]->buffer->vtable->set_pan(dxball_sounds[slot]->buffer, pan);
    if (volume != 0)
        dxball_sounds[slot]->buffer->vtable->set_volume(dxball_sounds[slot]->buffer, volume);
    result = dxball_sounds[slot]->buffer->vtable->play(dxball_sounds[slot]->buffer, 0, 0, 1);
    if (result == 2 || (DxBallUInt)result == 0x88780096UL) {
        dxball_restore_sounds();
        dxball_sounds[slot]->buffer->vtable->play(dxball_sounds[slot]->buffer, 0, 0, 1);
    }
    return;
}

/* FUNCTION: DXBALL 0x00405EF0 */
void dxball_stop_sound(DxBallInt slot)
{
    DxBallUInt status;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    {
        DxBallInt result;
        result = dxball_sounds[slot]->buffer->vtable->get_status(
            dxball_sounds[slot]->buffer, &status);
        if (status & 2) dxball_restore_sounds();
        result = dxball_sounds[slot]->buffer->vtable->stop(dxball_sounds[slot]->buffer);
        result = dxball_sounds[slot]->buffer->vtable->set_current_position(
            dxball_sounds[slot]->buffer, 0);
        (void)result;
    }
    return;
}

/* FUNCTION: DXBALL 0x00405FA0 */
void dxball_set_sound_frequency(DxBallInt slot, DxBallUInt frequency)
{
    DxBallUInt status;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    {
        DxBallInt result;
        result = dxball_sounds[slot]->buffer->vtable->get_status(
            dxball_sounds[slot]->buffer, &status);
        if (status & 2) dxball_restore_sounds();
        result = dxball_sounds[slot]->buffer->vtable->set_frequency(
            dxball_sounds[slot]->buffer, frequency);
        dxball_sounds[slot]->frequency = frequency;
        (void)result;
    }
    return;
}

/* FUNCTION: DXBALL 0x00406040 */
void dxball_set_sound_pan(DxBallInt slot, DxBallInt pan)
{
    DxBallUInt status;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    {
        DxBallInt result;
        result = dxball_sounds[slot]->buffer->vtable->get_status(
            dxball_sounds[slot]->buffer, &status);
        if (status & 2) dxball_restore_sounds();
        result = dxball_sounds[slot]->buffer->vtable->set_pan(
            dxball_sounds[slot]->buffer, pan);
        dxball_sounds[slot]->pan = pan;
        (void)result;
    }
    return;
}

/* FUNCTION: DXBALL 0x004060E0 */
void dxball_set_sound_volume(DxBallInt slot, DxBallInt volume)
{
    DxBallUInt status;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    {
        DxBallInt result;
        result = dxball_sounds[slot]->buffer->vtable->get_status(
            dxball_sounds[slot]->buffer, &status);
        if (status & 2) dxball_restore_sounds();
        result = dxball_sounds[slot]->buffer->vtable->set_volume(
            dxball_sounds[slot]->buffer, volume);
        dxball_sounds[slot]->volume = volume;
        (void)result;
    }
    return;
}

/* FUNCTION: DXBALL 0x00406180 */
void dxball_restore_sounds(void)
{
    DxBallInt result;
    if (dxball_sound_device == NULL) return;
    {
        DxBallInt slot;
        for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) {
            if (dxball_sounds[slot] != NULL) {
                DxBallUInt status;
                result = dxball_sounds[slot]->buffer->vtable->get_status(
                    dxball_sounds[slot]->buffer, &status);
                if (status & 2) {
                    result = dxball_sounds[slot]->buffer->vtable->restore(
                        dxball_sounds[slot]->buffer);
                    if (result == 0) {
                        char filename[256];
                        strcpy(filename, dxball_sounds[slot]->filename);
                        dxball_load_sound(slot, filename);
                    }
                }
            }
        }
    }
    return;
}

/* FUNCTION: DXBALL 0x00406290 */
DxBallInt dxball_parse_wave(const void *file, const void **format,
    const void **data, DxBallUInt *bytes)
{
    struct { const DxBallByte *end; DxBallUInt signature; } container;
    {
        struct { const DxBallByte *cursor; DxBallUInt length, tag; } chunk;
        chunk.cursor = (const DxBallByte *)file;
        container.signature = *(const DxBallUInt *)chunk.cursor;
        chunk.cursor += 4;
        chunk.length = *(const DxBallUInt *)chunk.cursor;
        chunk.cursor += 4;
        chunk.tag = *(const DxBallUInt *)chunk.cursor;
        chunk.cursor += 4;
        if (container.signature != 0x46464952UL) return 0;
        if (chunk.tag != 0x45564157UL) return 0;
        container.end = chunk.cursor + chunk.length - 4;
        while (chunk.cursor < container.end) {
            chunk.tag = *(const DxBallUInt *)chunk.cursor;
            chunk.cursor += 4;
            chunk.length = *(const DxBallUInt *)chunk.cursor;
            chunk.cursor += 4;
            switch (chunk.tag) {
                case 0x20746d66UL:
                    if (chunk.length < 14) return 0;
                    *format = chunk.cursor;
                    break;
                case 0x61746164UL:
                    *data = chunk.cursor;
                    *bytes = chunk.length;
                    return 1;
            }
            chunk.cursor += (chunk.length + 1) & 0xfffffffeUL;
        }
        return 0;
    }
}

/* FUNCTION: DXBALL 0x004063A0 */
DxBallInt dxball_create_sound_buffer(DxBallSoundDevice *device,
    DxBallSoundBuffer **buffer, const void *format, DxBallUInt bytes)
{
    DxBallInt result;
    {
        DxBallSoundBufferDesc descriptor;
        memset(&descriptor, 0, sizeof(descriptor));
        descriptor.size = 20;
        descriptor.flags = 0xe2;
        descriptor.bytes = bytes;
        descriptor.format = format;
        result = device->vtable->create_buffer(device, &descriptor, buffer, NULL);
    }
    return result;
}
