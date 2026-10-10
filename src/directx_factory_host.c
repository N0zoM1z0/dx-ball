#include "directx_factory.h"

/* Native analysis transports. Windows resolves the genuine SDK imports. */
DxBallInt DXBALL_DDCALL DirectSoundCreate(void *guid,
    DxBallSoundDevice **device, void *outer)
{
    return dxball_sound_api.create_device(guid, device, outer);
}

DxBallInt DXBALL_DDCALL DirectDrawCreate(void *guid,
    DxBallDDraw **device, void *outer)
{
    return dxball_direct_draw_create(guid, device, outer);
}
