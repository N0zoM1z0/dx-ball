#include "windows_adapter.h"
#include "runtime_entry.h"

/* Install host transports before the unchanged recovered CRT creates its heap
   and initializes the game. This adapter owns no second heap or initializer walk. */
void dxball_windows_crt_startup(void)
{
    dxball_bind_windows();
    dxball_crt_startup();
}
