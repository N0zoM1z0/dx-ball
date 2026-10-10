#include "allocator.h"
#include "sound.h"
#include <stdlib.h>
#include <string.h>

DxBallSoundApi dxball_sound_api = { NULL, NULL, NULL, NULL, NULL, dxball_malloc_bytes, dxball_heap_release };
DxBallSoundDevice *dxball_sound_device;
DxBallSoundBuffer *dxball_primary_sound;
DxBallSound *dxball_sounds[DXBALL_SOUND_COUNT];
const char dxball_file_fallback_prefix[] = "..\\";

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

static void initialization_failed(DxBallHandle window, const char *message, DxBallInt release_primary)
{
    if (dxball_direct_draw == NULL &&
        dxball_window_api.message_box(window, message, "DX-Ball", 0x24) == 7)
        dxball_platform_ops.exit_process(13);
    if (release_primary && dxball_primary_sound != NULL) {
        dxball_primary_sound->vtable->release(dxball_primary_sound);
        dxball_primary_sound = NULL;
    }
    dxball_sound_device->vtable->release(dxball_sound_device);
    dxball_sound_device = NULL;
}

void dxball_initialize_sound(DxBallHandle window)
{
    DxBallInt result, response, slot;
    DxBallSoundBufferDesc descriptor;
    char filename[256];
    if (dxball_sound_device != NULL) return;
    for (;;) {
        result = dxball_sound_api.create_device(NULL, &dxball_sound_device, NULL);
        if (result == 0) break;
        if (dxball_direct_draw != NULL) {
            dxball_sound_device = NULL;
            return;
        }
        if ((DxBallUInt)result == 0x8878000aUL) {
            response = dxball_window_api.message_box(window, occupied_message, "DX-Ball", 0x42);
            if (response == 3) dxball_platform_ops.exit_process(10);
            if (response == 5) {
                dxball_sound_device = NULL;
                return;
            }
        } else {
            response = dxball_window_api.message_box(window,
                (DxBallUInt)result == 0x88780078UL ? no_card_message : create_message,
                "DX-Ball", 0x24);
            if (response == 7)
                dxball_platform_ops.exit_process((DxBallUInt)result == 0x88780078UL ? 11 : 12);
            dxball_sound_device = NULL;
            return;
        }
    }
    result = dxball_sound_device->vtable->set_cooperative_level(dxball_sound_device, window, 1);
    if (result != 0) {
        initialization_failed(window, cooperate_message, 0);
        return;
    }
    memset(&descriptor, 0, sizeof(descriptor));
    descriptor.size = 20;
    descriptor.flags = 1;
    result = dxball_sound_device->vtable->create_buffer(dxball_sound_device,
        &descriptor, &dxball_primary_sound, NULL);
    if (result != 0) {
        initialization_failed(window, primary_create_message, 1);
        return;
    }
    result = dxball_primary_sound->vtable->play(dxball_primary_sound, 0, 0, 1);
    if (result != 0) {
        initialization_failed(window, primary_play_message, 1);
        return;
    }
    for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) {
        if (dxball_sounds[slot] != NULL) {
            strcpy(filename, dxball_sounds[slot]->filename);
            dxball_load_sound(slot, filename);
        }
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

void dxball_release_sound(DxBallInt slot)
{
    if (dxball_sounds[slot] != NULL) {
        if (dxball_sound_device != NULL && dxball_sounds[slot]->buffer != NULL) {
            dxball_sounds[slot]->buffer->vtable->release(dxball_sounds[slot]->buffer);
            dxball_sounds[slot]->buffer = NULL;
        }
        dxball_sound_api.deallocate(dxball_sounds[slot]);
        dxball_sounds[slot] = NULL;
    }
}

void dxball_load_sound(DxBallInt slot, const char *path)
{
    void *file, *first, *second;
    const void *format, *data;
    DxBallUInt bytes, first_bytes, second_bytes;
    DxBallSound *sound;
    dxball_release_sound(slot);
    /* Preserve the original request's one extra byte without inventing a field. */
    sound = (DxBallSound *)dxball_sound_api.allocate(sizeof(*sound) + 1);
    if (sound == NULL) dxball_platform_ops.exit_process(1);
    dxball_sounds[slot] = sound;
    file = dxball_load_binary_file(path, NULL, 1);
    if (file == NULL) {
        dxball_sound_api.deallocate(sound);
        return;
    }
    if (!dxball_parse_wave(file, &format, &data, &bytes)) {
        dxball_sound_api.deallocate(file);
        dxball_sound_api.deallocate(sound);
        return;
    }
    if (dxball_sound_device == NULL) sound->buffer = NULL;
    else {
        if (dxball_create_sound_buffer(dxball_sound_device, &sound->buffer, format, bytes) != 0) {
            dxball_sound_api.deallocate(file);
            dxball_sound_api.deallocate(sound);
            return;
        }
        if (sound->buffer->vtable->lock(sound->buffer, 0, bytes,
            &first, &first_bytes, &second, &second_bytes, 0) != 0) {
            dxball_sound_api.deallocate(file);
            dxball_sound_api.deallocate(sound);
            return;
        }
        memcpy(first, data, first_bytes);
        if (second_bytes != 0)
            memcpy(second, (const DxBallByte *)data + first_bytes, second_bytes);
        sound->buffer->vtable->unlock(sound->buffer, first, first_bytes, second, second_bytes);
        sound->buffer->vtable->get_frequency(sound->buffer, &sound->frequency);
        sound->buffer->vtable->get_pan(sound->buffer, &sound->pan);
        sound->buffer->vtable->get_volume(sound->buffer, &sound->volume);
    }
    dxball_sound_api.deallocate(file);
    strcpy(sound->filename, path);
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
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    result = dxball_sounds[slot]->buffer->vtable->get_status(
        dxball_sounds[slot]->buffer, &status);
    if (status & 2) dxball_restore_sounds();
    result = dxball_sounds[slot]->buffer->vtable->stop(dxball_sounds[slot]->buffer);
    result = dxball_sounds[slot]->buffer->vtable->set_current_position(
        dxball_sounds[slot]->buffer, 0);
    (void)result;
    return;
}

/* FUNCTION: DXBALL 0x00405FA0 */
void dxball_set_sound_frequency(DxBallInt slot, DxBallUInt frequency)
{
    DxBallUInt status;
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    result = dxball_sounds[slot]->buffer->vtable->get_status(
        dxball_sounds[slot]->buffer, &status);
    if (status & 2) dxball_restore_sounds();
    result = dxball_sounds[slot]->buffer->vtable->set_frequency(
        dxball_sounds[slot]->buffer, frequency);
    dxball_sounds[slot]->frequency = frequency;
    (void)result;
    return;
}

/* FUNCTION: DXBALL 0x00406040 */
void dxball_set_sound_pan(DxBallInt slot, DxBallInt pan)
{
    DxBallUInt status;
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    result = dxball_sounds[slot]->buffer->vtable->get_status(
        dxball_sounds[slot]->buffer, &status);
    if (status & 2) dxball_restore_sounds();
    result = dxball_sounds[slot]->buffer->vtable->set_pan(
        dxball_sounds[slot]->buffer, pan);
    dxball_sounds[slot]->pan = pan;
    (void)result;
    return;
}

/* FUNCTION: DXBALL 0x004060E0 */
void dxball_set_sound_volume(DxBallInt slot, DxBallInt volume)
{
    DxBallUInt status;
    DxBallInt result;
    if (dxball_sound_device == NULL || dxball_sounds[slot] == NULL) return;
    result = dxball_sounds[slot]->buffer->vtable->get_status(
        dxball_sounds[slot]->buffer, &status);
    if (status & 2) dxball_restore_sounds();
    result = dxball_sounds[slot]->buffer->vtable->set_volume(
        dxball_sounds[slot]->buffer, volume);
    dxball_sounds[slot]->volume = volume;
    (void)result;
    return;
}

/* FUNCTION: DXBALL 0x00406180 */
void dxball_restore_sounds(void)
{
    DxBallInt result, slot;
    DxBallUInt status;
    char filename[256];
    if (dxball_sound_device == NULL) return;
    for (slot = 0; slot < DXBALL_SOUND_COUNT; ++slot) {
        if (dxball_sounds[slot] != NULL) {
            result = dxball_sounds[slot]->buffer->vtable->get_status(
                dxball_sounds[slot]->buffer, &status);
            if (status & 2) {
                result = dxball_sounds[slot]->buffer->vtable->restore(
                    dxball_sounds[slot]->buffer);
                if (result == 0) {
                    strcpy(filename, dxball_sounds[slot]->filename);
                    dxball_load_sound(slot, filename);
                }
            }
        }
    }
    return;
}

static DxBallUInt wave_word(const DxBallByte *data)
{
    return (DxBallUInt)data[0] | ((DxBallUInt)data[1] << 8) |
        ((DxBallUInt)data[2] << 16) | ((DxBallUInt)data[3] << 24);
}

DxBallInt dxball_parse_wave(const void *file, const void **format,
    const void **data, DxBallUInt *bytes)
{
    const DxBallByte *base = (const DxBallByte *)file, *cursor, *end;
    DxBallUInt tag, length;
    if (wave_word(base) != 0x46464952UL || wave_word(base + 8) != 0x45564157UL) return 0;
    cursor = base + 12;
    end = base + 8 + wave_word(base + 4);
    while (cursor < end) {
        tag = wave_word(cursor);
        length = wave_word(cursor + 4);
        cursor += 8;
        if (tag == 0x20746d66UL) {
            if (length < 14) return 0;
            *format = cursor;
        } else if (tag == 0x61746164UL) {
            *data = cursor;
            *bytes = length;
            return 1;
        }
        cursor += (length + 1) & 0xfffffffeUL;
    }
    return 0;
}

DxBallInt dxball_create_sound_buffer(DxBallSoundDevice *device,
    DxBallSoundBuffer **buffer, const void *format, DxBallUInt bytes)
{
    DxBallSoundBufferDesc descriptor;
    memset(&descriptor, 0, sizeof(descriptor));
    descriptor.size = 20;
    descriptor.flags = 0xe2;
    descriptor.bytes = bytes;
    descriptor.format = format;
    return device->vtable->create_buffer(device, &descriptor, buffer, NULL);
}

void *dxball_load_binary_file(const char *path, void *destination, DxBallInt allocate)
{
    DxBallHandle handle;
    DxBallUInt bytes, read;
    char fallback[260];
    handle = dxball_sound_api.create_file(path, 0x80000000UL, 1, NULL, 3, 0x80, 0);
    if (handle == (DxBallHandle)-1) {
        strcpy(fallback, dxball_file_fallback_prefix);
        strcat(fallback, path);
        handle = dxball_sound_api.create_file(fallback, 0x80000000UL, 1, NULL, 3, 0x80, 0);
        if (handle == (DxBallHandle)-1) return NULL;
    }
    bytes = dxball_sound_api.file_size(handle, NULL);
    if (allocate != 0) {
        destination = dxball_sound_api.allocate(bytes);
        if (destination == NULL) return NULL;
    }
    if (!dxball_sound_api.read_file(handle, destination, bytes, &read, NULL)) {
        dxball_sound_api.deallocate(destination);
        return NULL;
    }
    dxball_sound_api.close_handle(handle);
    return destination;
}
