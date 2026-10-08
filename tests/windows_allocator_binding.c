/* SDK fixture: use the actual Windows adapter table and maintained owner
   defaults. Observer callbacks forward to the saved physical adapter callbacks. */
#include <windows.h>
#include <stdio.h>
#include "allocator.h"
#include "windows_adapter.h"
#include "gameplay.h"
#include "effects.h"
#include "sound.h"
#include "core.h"

typedef char PointerMustBe32Bits[(sizeof(void *) == 4) ? 1 : -1];
static DxBallHeapApi physical;
static unsigned int creates, allocations, releases;
static DxBallUInt last_flags;
static size_t last_initial, last_maximum, last_bytes;
static void *last_heap, *last_memory;
static DxBallInt last_release_result;
static void *DXBALL_HEAP_CALL observe_create(DxBallUInt flags, size_t initial, size_t maximum)
{
    ++creates; last_flags = flags; last_initial = initial; last_maximum = maximum;
    return physical.create(flags, initial, maximum);
}
static void *DXBALL_HEAP_CALL observe_allocate(void *heap, DxBallUInt flags, size_t bytes)
{
    ++allocations; last_heap = heap; last_flags = flags; last_bytes = bytes;
    return physical.allocate(heap, flags, bytes);
}
static DxBallInt DXBALL_HEAP_CALL observe_release(void *heap, DxBallUInt flags, void *memory)
{
    ++releases; last_heap = heap; last_flags = flags; last_memory = memory;
    last_release_result = physical.release(heap, flags, memory);
    return last_release_result;
}
#define CHECK(x) do { if (!(x)) { printf("failed line %d: %s\n", __LINE__, #x); return 2; } } while (0)
int main(void)
{
    DxBallHeapApi observed;
    void *heap, *memory;
    size_t bytes, byte;
    unsigned int kind;
    CHECK(dxball_runtime_heap == NULL && dxball_new_handler == NULL && dxball_malloc_mode == 0);
    dxball_bind_windows();
    CHECK(dxball_runtime_heap == NULL && dxball_new_handler == NULL && dxball_malloc_mode == 0);
    physical = dxball_heap_api;
    CHECK(physical.create != NULL && physical.allocate != NULL && physical.release != NULL);
    observed.create = observe_create; observed.allocate = observe_allocate; observed.release = observe_release;
    dxball_bind_heap_api(&observed);
    heap = dxball_initialize_runtime_heap();
    CHECK(heap != NULL && dxball_runtime_heap == heap && HeapValidate(heap, 0, NULL));
    CHECK(creates == 1 && last_flags == 1 && last_initial == 0x1000 && last_maximum == 0);
    for (kind = 0; kind < 4; ++kind) {
        bytes = kind == 0 ? 1 : kind == 1 ? 17 : kind == 2 ? sizeof(DxBallProjectileNode) : 37;
        if (kind == 0) memory = dxball_malloc_bytes(0);
        else if (kind == 1) memory = dxball_new_bytes(bytes);
        else if (kind == 2) memory = dxball_allocate_node(bytes);
        else memory = dxball_sound_api.allocate(bytes);
        CHECK(memory != NULL && allocations == kind + 1 && last_heap == heap && last_flags == 0 && last_bytes == bytes);
        CHECK(HeapValidate(heap, 0, memory));
        for (byte = 0; byte < bytes; ++byte) ((unsigned char *)memory)[byte] = (unsigned char)(byte ^ kind);
        for (byte = 0; byte < bytes; ++byte) CHECK(((unsigned char *)memory)[byte] == (unsigned char)(byte ^ kind));
        if (kind == 0) dxball_heap_release(memory);
        else if (kind == 1) dxball_runtime_delete(memory);
        else if (kind == 2) dxball_deallocate_node(memory);
        else dxball_sound_api.deallocate(memory);
        CHECK(releases == kind + 1 && last_heap == heap && last_flags == 0 && last_memory == memory && last_release_result != 0);
    }
    CHECK(dxball_runtime_malloc(0xffffffe1U) == NULL && dxball_runtime_new(0xffffffffU) == NULL && allocations == 4);
    dxball_runtime_delete(NULL); dxball_heap_release(NULL); CHECK(releases == 4);
    CHECK(HeapValidate(heap, 0, NULL));
    /* Destroy is fixture cleanup only; it is absent from game startup/shutdown. */
    CHECK(HeapDestroy(heap));
    printf("{\"status\":\"windows-allocator-binding-pass\",\"pointer_bytes\":%u,\"heap_api_bytes\":%u,\"creates\":%u,\"allocations\":%u,\"successful_releases\":%u}\n",
        (unsigned int)sizeof(void *), (unsigned int)sizeof(DxBallHeapApi), creates, allocations, releases);
    return 0;
}
