/* Shared transport for the DirectDrawCreate SDK boundary. Windows binds its
   loader adapter; native callers can bind a factory with the same contract. */
#include "platform.h"

DxBallDrawFactory dxball_draw_factory_backend;

DxBallInt DXBALL_DDCALL dxball_direct_draw_create(void *guid,
    DxBallDDraw **device, void *outer)
{
    if (dxball_draw_factory_backend == NULL) return (DxBallInt)0x80004005UL;
    return dxball_draw_factory_backend(guid, device, outer);
}
