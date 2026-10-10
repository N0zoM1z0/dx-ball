#ifndef DXBALL_DIRECTX_FACTORY_H
#define DXBALL_DIRECTX_FACTORY_H

#include "sound.h"

#ifdef __cplusplus
extern "C" {
#endif
/* The original SDK factory import uses three stdcall arguments. The game
   requests the default device with NULL GUID and aggregation pointers. */
DxBallInt DXBALL_DDCALL DirectSoundCreate(void *guid,
    DxBallSoundDevice **device, void *outer);
DxBallInt DXBALL_DDCALL DirectDrawCreate(void *guid,
    DxBallDDraw **device, void *outer);
#ifdef __cplusplus
}
#endif

#endif
