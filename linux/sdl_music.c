#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "midi.h"

void dxball_sdl_audio_lock(void);
void dxball_sdl_audio_unlock(void);

typedef struct MusicEvent {
    uint64_t sample;
    uint32_t word;
} MusicEvent;
typedef struct MusicVoice {
    double phase, frequency, gain;
    int note, channel, active, released, program;
} MusicVoice;

static MusicEvent *events;
static size_t event_count, event_index;
static uint64_t song_position, song_duration;
static int song_playing, song_looping;
static MusicVoice voices[24];
static uint8_t programs[16];
static uint32_t noise_state = 0x74a83d12;

static uint32_t read_word(const uint8_t *bytes) {
    uint32_t value;
    memcpy(&value, bytes, 4);
    return value;
}
static void clear_voices(void) {
    memset(voices, 0, sizeof(voices));
    memset(programs, 0, sizeof(programs));
}
static void end_music(void) {
    free(events);
    events = NULL;
    event_count = event_index = 0;
    song_position = song_duration = 0;
    song_playing = song_looping = 0;
    clear_voices();
}
static void note_off(int channel, int note) {
    for (size_t i = 0; i < sizeof(voices) / sizeof(voices[0]); ++i)
        if (voices[i].active && voices[i].channel == channel && voices[i].note == note)
            voices[i].released = 1;
}
static void apply_event(uint32_t word) {
    int kind = (word >> 24) & 0xff;
    if (kind != 0) return;
    int status = word & 0xff;
    int note = (word >> 8) & 0xff;
    int velocity = (word >> 16) & 0xff;
    int channel = status & 15;
    switch (status & 0xf0) {
    case 0x80: note_off(channel, note); break;
    case 0x90:
        if (!velocity) { note_off(channel, note); break; }
        {
            MusicVoice *voice = NULL;
            for (size_t i = 0; i < sizeof(voices) / sizeof(voices[0]); ++i)
                if (!voices[i].active) { voice = &voices[i]; break; }
            if (!voice) voice = &voices[0];
            voice->active = 1;
            voice->released = 0;
            voice->note = note;
            voice->channel = channel;
            voice->program = programs[channel];
            voice->phase = 0.0;
            voice->frequency = 440.0 * pow(2.0, (note - 69) / 12.0);
            voice->gain = velocity / 127.0;
        }
        break;
    case 0xb0:
        if (note == 123 || note == 120)
            for (size_t i = 0; i < sizeof(voices) / sizeof(voices[0]); ++i)
                if (voices[i].channel == channel) voices[i].released = 1;
        break;
    case 0xc0: programs[channel] = note; break;
    default: break;
    }
}
void dxball_sdl_music_mix(float *output, int frames) {
    if (!song_playing || !events || !event_count) return;
    for (int frame = 0; frame < frames; ++frame) {
        while (event_index < event_count && events[event_index].sample <= song_position)
            apply_event(events[event_index++].word);
        if (event_index == event_count && song_position > song_duration) {
            if (!song_looping) { song_playing = 0; break; }
            event_index = 0;
            song_position = 0;
            clear_voices();
        }
        double sample = 0.0;
        for (size_t voice_index = 0; voice_index < sizeof(voices) / sizeof(voices[0]); ++voice_index) {
            MusicVoice *voice = &voices[voice_index];
            if (!voice->active) continue;
            double value;
            if (voice->channel == 9) {
                noise_state = noise_state * 1664525u + 1013904223u;
                value = ((noise_state >> 16) / 32768.0) - 1.0;
                voice->gain *= 0.998;
                if (voice->gain < 0.002) voice->active = 0;
            } else {
                value = sin(voice->phase);
                if (voice->program >= 80 && voice->program < 96)
                    value = 0.7 * value + 0.3 * sin(voice->phase * 2.0);
                voice->phase += 6.283185307179586 * voice->frequency / 44100.0;
                if (voice->phase > 6.283185307179586) voice->phase -= 6.283185307179586;
                if (voice->released) {
                    voice->gain *= 0.9992;
                    if (voice->gain < 0.002) voice->active = 0;
                }
            }
            sample += value * voice->gain;
        }
        output[frame * 2] += (float)(sample * 0.08);
        output[frame * 2 + 1] += (float)(sample * 0.08);
        ++song_position;
    }
}
static int parse_mds(const uint8_t *bytes, size_t length) {
    if (length < 32 || memcmp(bytes, "RIFF", 4) || memcmp(bytes + 8, "MIDS", 4))
        return 0;
    uint32_t division = 96, capacity = 0, flags = 0;
    const uint8_t *data = NULL;
    size_t data_length = 0;
    for (size_t offset = 12; offset + 8 <= length;) {
        uint32_t chunk = read_word(bytes + offset + 4);
        offset += 8;
        if (chunk > length - offset) return 0;
        if (!memcmp(bytes + offset - 8, "fmt ", 4) && chunk >= 12) {
            division = read_word(bytes + offset);
            capacity = read_word(bytes + offset + 4);
            flags = read_word(bytes + offset + 8);
        }
        if (!memcmp(bytes + offset - 8, "data", 4)) {
            data = bytes + offset;
            data_length = chunk;
        }
        offset += (chunk + 1u) & ~1u;
    }
    if (!data || data_length < 4 || !division || !capacity) return 0;
    uint32_t blocks = read_word(data);
    size_t offset = 4;
    uint32_t tempo = 500000;
    double sample_time = 0.0;
    size_t allocated = data_length / 8 + 1;
    MusicEvent *parsed = calloc(allocated, sizeof(*parsed));
    if (!parsed) return 0;
    size_t count = 0;
    for (uint32_t block = 0; block < blocks; ++block) {
        if (offset + 8 > data_length) { free(parsed); return 0; }
        uint32_t block_bytes = read_word(data + offset + 4);
        offset += 8;
        if (block_bytes > data_length - offset) { free(parsed); return 0; }
        size_t end = offset + block_bytes;
        while (offset + (flags & 1 ? 8u : 12u) <= end) {
            uint32_t delta = read_word(data + offset);
            offset += 4;
            if (!(flags & 1)) offset += 4;
            uint32_t word = read_word(data + offset);
            offset += 4;
            uint32_t payload = (word & 0x80000000u) ? ((word & 0xffffffu) + 3u) & ~3u : 0;
            if (payload > end - offset) { free(parsed); return 0; }
            offset += payload;
            sample_time += (double)delta * tempo * 44100.0 / (division * 1000000.0);
            if ((word >> 24) == 1) tempo = word & 0xffffffu;
            else if (count < allocated) {
                parsed[count].sample = (uint64_t)sample_time;
                parsed[count++].word = word;
            }
        }
        offset = end;
    }
    if (!count) { free(parsed); return 0; }
    events = parsed;
    event_count = count;
    song_duration = (uint64_t)sample_time + 44100;
    return 1;
}
DxBallInt dxball_load_music(const char *path, DxBallInt play) {
    FILE *file = fopen(path, "rb");
    if (!file) return 0;
    if (fseek(file, 0, SEEK_END) != 0) { fclose(file); return 0; }
    long length = ftell(file);
    if (length <= 0 || length > 1000000 || fseek(file, 0, SEEK_SET) != 0) {
        fclose(file); return 0;
    }
    uint8_t *bytes = malloc((size_t)length);
    if (!bytes) { fclose(file); return 0; }
    int read_ok = fread(bytes, 1, (size_t)length, file) == (size_t)length;
    fclose(file);
    dxball_sdl_audio_lock();
    end_music();
    int parsed = read_ok && parse_mds(bytes, (size_t)length);
    song_playing = parsed && play;
    song_looping = 1;
    dxball_sdl_audio_unlock();
    free(bytes);
    return parsed;
}
void dxball_resume_music(void) {
    dxball_sdl_audio_lock(); if (events) song_playing = 1; dxball_sdl_audio_unlock();
}
void dxball_pause_music(void) {
    dxball_sdl_audio_lock(); song_playing = 0; dxball_sdl_audio_unlock();
}
void dxball_restart_music(void) {
    dxball_sdl_audio_lock();
    if (events) { song_position = 0; event_index = 0; clear_voices(); song_playing = 1; }
    dxball_sdl_audio_unlock();
}
void dxball_close_music(void) {
    dxball_sdl_audio_lock(); end_music(); dxball_sdl_audio_unlock();
}
