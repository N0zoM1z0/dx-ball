/* Native-test boundaries for real production sound/RNG symbol references. */
#include "gameplay.h"
#include "sound.h"
#include "startup.h"
#include <stdio.h>
#include <stdlib.h>

static DxBallGameplayOps *bound_ops;
static unsigned stop_active, play_active, random_active;

static void binding_failure(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    abort();
}

int dxball_test_bind_gameplay_ops(DxBallGameplayOps *ops)
{
    if (ops == NULL) return -1;
    if (ops->stop_sound == NULL || ops->play_sound == NULL || ops->random_range == NULL)
        return -2;
    if (ops->stop_sound == dxball_stop_sound || ops->play_sound == dxball_play_sound ||
        ops->random_range == dxball_random_range) return -3;
    bound_ops = ops;
    return 0;
}

void dxball_stop_sound(DxBallInt sound)
{
    if (bound_ops == NULL || bound_ops->stop_sound == NULL)
        binding_failure("CoreNative stop_sound: fixture table is unbound or callback is null");
    if (stop_active || bound_ops->stop_sound == dxball_stop_sound)
        binding_failure("CoreNative stop_sound: recursive interposer callback");
    stop_active = 1;
    bound_ops->stop_sound(sound);
    stop_active = 0;
}

void dxball_play_sound(DxBallInt sound, DxBallInt frequency, DxBallInt pan, DxBallInt volume)
{
    if (bound_ops == NULL || bound_ops->play_sound == NULL)
        binding_failure("CoreNative play_sound: fixture table is unbound or callback is null");
    if (play_active || bound_ops->play_sound == dxball_play_sound)
        binding_failure("CoreNative play_sound: recursive interposer callback");
    play_active = 1;
    bound_ops->play_sound(sound, frequency, pan, volume);
    play_active = 0;
}

DxBallInt dxball_random_range(DxBallInt limit)
{
    DxBallInt result;
    if (bound_ops == NULL || bound_ops->random_range == NULL)
        binding_failure("CoreNative random_range: fixture table is unbound or callback is null");
    if (random_active || bound_ops->random_range == dxball_random_range)
        binding_failure("CoreNative random_range: recursive interposer callback");
    random_active = 1;
    result = bound_ops->random_range(limit);
    random_active = 0;
    return result;
}
