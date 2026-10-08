/* Explicit portable dependency bridge. These callbacks use the host CRT and
   do not implement a Windows private heap. Game startup replaces the table. */
#include "allocator.h"
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
DxBallHeapApi dxball_heap_api = { host_create, host_allocate, host_release };

void dxball_bind_heap_api(const DxBallHeapApi *api)
{
    dxball_heap_api = *api;
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
