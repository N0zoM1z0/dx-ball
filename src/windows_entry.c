#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "windows_adapter.h"
#include "platform.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    dxball_bind_windows();
    return (int)dxball_win_main((DxBallHandle)instance, (DxBallHandle)previous,
        (DxBallHandle)command_line, show);
}
