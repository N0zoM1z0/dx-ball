/* Win32 defaults are ready before game binding and CRT initialization.
   Other hosts retain the explicit malloc/free dependency bridge. */
#include "allocator_imports.h"
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static void *DXBALL_HEAP_CALL host_create(DxBallUInt flags, size_t initial, size_t maximum)
{ return (void *)HeapCreate((DWORD)flags, (DWORD)initial, (DWORD)maximum); }
static void *DXBALL_HEAP_CALL host_allocate(void *heap, DxBallUInt flags, size_t bytes)
{ return HeapAlloc((HANDLE)heap, (DWORD)flags, (DWORD)bytes); }
static DxBallInt DXBALL_HEAP_CALL host_release(void *heap, DxBallUInt flags, void *memory)
{ return (DxBallInt)HeapFree((HANDLE)heap, (DWORD)flags, memory); }
#else
#include <stdlib.h>

static unsigned char host_heap_identity;
static void *DXBALL_HEAP_CALL host_create(DxBallUInt flags, size_t initial, size_t maximum)
{
    (void)flags; (void)initial; (void)maximum;
    return &host_heap_identity;
}
static void *DXBALL_HEAP_CALL host_allocate(void *heap, DxBallUInt flags, size_t bytes)
{
    (void)heap; (void)flags;
    return malloc(bytes);
}
static DxBallInt DXBALL_HEAP_CALL host_release(void *heap, DxBallUInt flags, void *memory)
{
    (void)heap; (void)flags;
    free(memory);
    return 1;
}
#endif
/* Adapters may inspect the current binding record. Calls use the independent
   import cells; update both through dxball_bind_heap_api. */
DxBallHeapApi dxball_heap_api = { host_create, host_allocate, host_release };
void *(DXBALL_HEAP_CALL *dxball_heap_create)(DxBallUInt, size_t, size_t) = host_create;
void *(DXBALL_HEAP_CALL *dxball_heap_alloc)(void *, DxBallUInt, size_t) = host_allocate;
DxBallInt (DXBALL_HEAP_CALL *dxball_heap_free)(void *, DxBallUInt, void *) = host_release;

void dxball_bind_heap_api(const DxBallHeapApi *api)
{
    dxball_heap_api = *api;
    dxball_heap_create = api->create;
    dxball_heap_alloc = api->allocate;
    dxball_heap_free = api->release;
}

/* Owner callback APIs take size_t. Reject host counts outside the original
   unsigned domain before conversion, then let the recovered body apply its
   own size limit, zero normalization and handler policy. */
void *dxball_malloc_bytes(size_t bytes)
{
    if ((size_t)(DxBallUInt)bytes != bytes) return NULL;
    return dxball_runtime_malloc((DxBallUInt)bytes);
}
void *dxball_new_bytes(size_t bytes)
{
    if ((size_t)(DxBallUInt)bytes != bytes) return NULL;
    return dxball_runtime_new((DxBallUInt)bytes);
}
