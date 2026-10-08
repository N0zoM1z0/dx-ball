#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "windows_adapter.h"
#include "platform.h"
#include "allocator.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    dxball_bind_windows();
    /* Original CRT startup creates the private heap before entering the game.
       Its return is not tested. The reconstructed host CRT remains separate. */
    dxball_initialize_runtime_heap();
    return (int)dxball_win_main((DxBallHandle)instance, (DxBallHandle)previous,
        (DxBallHandle)command_line, show);
}
