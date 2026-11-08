#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void dxball_sdl_music_mix(float *output, int frames) {
    (void)output;
    (void)frames;
}

#include "../linux/sdl_audio.c"

static int repeated_play_keeps_position(void) {
    uint8_t samples[] = {0, 255, 0, 255};
    NativeSoundBuffer buffer = {0};
    buffer.samples = samples;
    buffer.bytes = sizeof(samples);
    buffer.frequency = 44100;
    buffer.channels = 1;
    buffer.bits = 8;
    buffers = &buffer;

    buffer_play((DxBallSoundBuffer *)&buffer, 0, 0, 1);
    float first[2] = {0};
    audio_mix(NULL, (Uint8 *)first, sizeof(first));

    buffer_play((DxBallSoundBuffer *)&buffer, 0, 0, 1);
    float second[2] = {0};
    audio_mix(NULL, (Uint8 *)second, sizeof(second));
    buffers = NULL;
    return first[0] < -0.9f && second[0] > 0.9f;
}

static int fractional_pitch_interpolates(void) {
    uint8_t samples[] = {128, 255, 128};
    NativeSoundBuffer buffer = {0};
    buffer.samples = samples;
    buffer.bytes = sizeof(samples);
    buffer.frequency = 22050;
    buffer.channels = 1;
    buffer.bits = 8;
    buffers = &buffer;

    buffer_play((DxBallSoundBuffer *)&buffer, 0, 0, 0);
    float output[4] = {0};
    audio_mix(NULL, (Uint8 *)output, sizeof(output));
    buffers = NULL;
    return fabsf(output[0]) < 0.01f && output[2] > 0.4f && output[2] < 0.6f;
}

static int looping_pitch_keeps_fractional_phase(void) {
    uint8_t samples[] = {0, 255};
    NativeSoundBuffer buffer = {0};
    buffer.samples = samples;
    buffer.bytes = sizeof(samples);
    buffer.frequency = 66150;
    buffer.channels = 1;
    buffer.bits = 8;
    buffers = &buffer;

    buffer_play((DxBallSoundBuffer *)&buffer, 0, 0, 1);
    float first[4] = {0};
    audio_mix(NULL, (Uint8 *)first, sizeof(first));
    float next[2] = {0};
    audio_mix(NULL, (Uint8 *)next, sizeof(next));
    buffers = NULL;
    return next[0] > 0.9f;
}

int main(void) {
    if (!repeated_play_keeps_position()) {
        fputs("repeated Play rewound a looping buffer\n", stderr);
        return 1;
    }
    if (!fractional_pitch_interpolates()) {
        fputs("fractional pitch did not interpolate samples\n", stderr);
        return 1;
    }
    if (!looping_pitch_keeps_fractional_phase()) {
        fputs("loop boundary discarded fractional playback position\n", stderr);
        return 1;
    }
    puts("native audio behavior passed");
    return 0;
}
