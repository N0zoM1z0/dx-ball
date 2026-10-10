/* Shared transport for the DirectDrawCreate SDK boundary. Windows binds its
   loader adapter; native callers can bind a factory with the same contract. */
#include "platform.h"
#include <stdlib.h>

DxBallDrawFactory dxball_draw_factory_backend;

DxBallInt DXBALL_DDCALL dxball_direct_draw_create(void *guid,
    DxBallDDraw **device, void *outer)
{
    if (dxball_draw_factory_backend == NULL) return (DxBallInt)0x80004005UL;
    return dxball_draw_factory_backend(guid, device, outer);
}

void (*dxball_process_exit_backend)(DxBallInt);

void dxball_process_exit(DxBallInt status)
{
    if (dxball_process_exit_backend != NULL)
        dxball_process_exit_backend(status);
    exit(status);
}
