/* The modern SDK also exposes the original DirectSound 1 descriptor/interface.
   The pinned VC4 SDK lacks DirectX headers; this probe uses MinGW's SDK only. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <dsound.h>
#include <stddef.h>
#include <stdio.h>
#include "../src/sound.h"

#define CHECK(expression, name) typedef char name[(expression) ? 1 : -1]
#define FIELD(ours, own_field, sdk, sdk_field, name) \
    CHECK(offsetof(ours, own_field) == offsetof(sdk, sdk_field), name)

CHECK(sizeof(void *) == 4, i686_pointers_required);
CHECK(sizeof(DxBallSurfaceDesc) == sizeof(DDSURFACEDESC), surface_desc_size);
FIELD(DxBallSurfaceDesc, pixels, DDSURFACEDESC, lpSurface, surface_pixels);
FIELD(DxBallSurfaceDesc, pitch, DDSURFACEDESC, lPitch, surface_pitch);
FIELD(DxBallSurfaceDesc, pixel_format, DDSURFACEDESC, ddpfPixelFormat, surface_format);
FIELD(DxBallSurfaceDesc, caps, DDSURFACEDESC, ddsCaps, surface_caps);
CHECK(sizeof(DxBallColorFillFx) == sizeof(DDBLTFX), color_fill_size);
FIELD(DxBallColorFillFx, fill_color, DDBLTFX, dwFillColor, color_fill_value);
CHECK(sizeof(DxBallSoundBufferDesc) == sizeof(DSBUFFERDESC1), sound_desc_size);
FIELD(DxBallSoundBufferDesc, format, DSBUFFERDESC1, lpwfxFormat, sound_desc_format);
FIELD(DxBallSoundDeviceVTable, release, IDirectSoundVtbl, Release, sound_device_release);
FIELD(DxBallSoundDeviceVTable, create_buffer, IDirectSoundVtbl, CreateSoundBuffer, sound_device_create);
FIELD(DxBallSoundDeviceVTable, set_cooperative_level, IDirectSoundVtbl, SetCooperativeLevel, sound_device_cooperate);
FIELD(DxBallSoundBufferVTable, get_volume, IDirectSoundBufferVtbl, GetVolume, buffer_volume);
FIELD(DxBallSoundBufferVTable, get_pan, IDirectSoundBufferVtbl, GetPan, buffer_pan);
FIELD(DxBallSoundBufferVTable, get_frequency, IDirectSoundBufferVtbl, GetFrequency, buffer_frequency);
FIELD(DxBallSoundBufferVTable, get_status, IDirectSoundBufferVtbl, GetStatus, buffer_status);
FIELD(DxBallSoundBufferVTable, lock, IDirectSoundBufferVtbl, Lock, buffer_lock);
FIELD(DxBallSoundBufferVTable, play, IDirectSoundBufferVtbl, Play, buffer_play);
FIELD(DxBallSoundBufferVTable, set_current_position, IDirectSoundBufferVtbl, SetCurrentPosition, buffer_position);
FIELD(DxBallSoundBufferVTable, set_volume, IDirectSoundBufferVtbl, SetVolume, buffer_set_volume);
FIELD(DxBallSoundBufferVTable, set_pan, IDirectSoundBufferVtbl, SetPan, buffer_set_pan);
FIELD(DxBallSoundBufferVTable, set_frequency, IDirectSoundBufferVtbl, SetFrequency, buffer_set_frequency);
FIELD(DxBallSoundBufferVTable, stop, IDirectSoundBufferVtbl, Stop, buffer_stop);
FIELD(DxBallSoundBufferVTable, unlock, IDirectSoundBufferVtbl, Unlock, buffer_unlock);
FIELD(DxBallSoundBufferVTable, restore, IDirectSoundBufferVtbl, Restore, buffer_restore);
FIELD(DxBallDDrawVTable, create_palette, IDirectDrawVtbl, CreatePalette, draw_palette);
FIELD(DxBallDDrawVTable, create_surface, IDirectDrawVtbl, CreateSurface, draw_surface);
FIELD(DxBallDDrawVTable, wait_vertical_blank, IDirectDrawVtbl, WaitForVerticalBlank, draw_wait);
FIELD(DxBallDDSurfaceVTable, blt, IDirectDrawSurfaceVtbl, Blt, surface_blt);
FIELD(DxBallDDSurfaceVTable, blt_fast, IDirectDrawSurfaceVtbl, BltFast, surface_blt_fast);
FIELD(DxBallDDSurfaceVTable, flip, IDirectDrawSurfaceVtbl, Flip, surface_flip);
FIELD(DxBallDDSurfaceVTable, get_blt_status, IDirectDrawSurfaceVtbl, GetBltStatus, surface_blt_status);
FIELD(DxBallDDSurfaceVTable, get_desc, IDirectDrawSurfaceVtbl, GetSurfaceDesc, surface_get_desc);
FIELD(DxBallDDSurfaceVTable, lock, IDirectDrawSurfaceVtbl, Lock, surface_lock);
FIELD(DxBallDDSurfaceVTable, restore, IDirectDrawSurfaceVtbl, Restore, surface_restore);
FIELD(DxBallDDSurfaceVTable, set_color_key, IDirectDrawSurfaceVtbl, SetColorKey, surface_color_key);
FIELD(DxBallDDSurfaceVTable, set_palette, IDirectDrawSurfaceVtbl, SetPalette, surface_palette);
FIELD(DxBallDDSurfaceVTable, unlock, IDirectDrawSurfaceVtbl, Unlock, surface_unlock);
CHECK(sizeof(DxBallSoundBufferVTable) == sizeof(IDirectSoundBufferVtbl), buffer_vtable_size);

int main(void)
{
    printf("{\"surface_desc\":%u,\"color_fill\":%u,"
           "\"sound_desc_v1\":%u,\"sound_desc_modern\":%u,"
           "\"sound_buffer_slots\":%u,\"sound_restore_slot\":%u}\n",
           (unsigned)sizeof(DDSURFACEDESC), (unsigned)sizeof(DDBLTFX),
           (unsigned)sizeof(DSBUFFERDESC1), (unsigned)sizeof(DSBUFFERDESC),
           (unsigned)(sizeof(IDirectSoundBufferVtbl) / sizeof(void *)),
           (unsigned)(offsetof(IDirectSoundBufferVtbl, Restore) / sizeof(void *)));
    return 0;
}
