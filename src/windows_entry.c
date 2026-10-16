#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "windows_adapter.h"
#include "platform.h"
#include "allocator.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    dxball_bind_windows();
    /* Keep the heap and allocations supplied by restored CRT startup.
       The compiler-CRT build still needs its first private-heap initialization. */
    if (dxball_runtime_heap == NULL)
        dxball_initialize_runtime_heap();
    return (int)dxball_win_main((DxBallHandle)instance, (DxBallHandle)previous,
        (DxBallHandle)command_line, show);
}
