#include "allocator.h"

void *dxball_runtime_heap;
DxBallNewHandler dxball_new_handler;
DxBallInt dxball_malloc_mode;

/* 0x00419E80: startup does not test EAX; retain the observed full handle. */
void *DXBALL_NEW_CALL dxball_initialize_runtime_heap(void)
{
    dxball_runtime_heap = dxball_heap_api.create(1, 0x1000, 0);
    return dxball_runtime_heap;
}

/* 0x00417770: read mode once for this request, unlike operator new's one. */
void *DXBALL_NEW_CALL dxball_runtime_malloc(DxBallUInt bytes)
{
    return dxball_allocate_with_handler(bytes, dxball_malloc_mode);
}

/* 0x00416770: operator new enables the handler independently of malloc mode. */
void *DXBALL_NEW_CALL dxball_runtime_new(DxBallUInt bytes)
{
    return dxball_allocate_with_handler(bytes, 1);
}

/* 0x00416760: deletion has a void ABI, including its null-pointer path. */
void DXBALL_NEW_CALL dxball_runtime_delete(void *memory)
{
    dxball_heap_release(memory);
}

/* 0x00417750: a failed physical release is not converted to a game return. */
void DXBALL_NEW_CALL dxball_heap_release(void *memory)
{
    if (memory != NULL) dxball_heap_api.release(dxball_runtime_heap, 0, memory);
}

/* 0x00417790: callbacks can change the heap and handler before a retry. */
void *DXBALL_NEW_CALL dxball_allocate_with_handler(DxBallUInt bytes, DxBallInt enabled)
{
    void *memory;
    if (bytes > 0xffffffe0U) return NULL;
    if (bytes == 0) bytes = 1;
    for (;;) {
        memory = dxball_heap_allocate(bytes);
        if (memory != NULL || !enabled) return memory;
        if (!dxball_call_new_handler(bytes)) return NULL;
    }
}

/* 0x004177D0: fetch the current opaque heap for each physical request. */
void *DXBALL_NEW_CALL dxball_heap_allocate(DxBallUInt bytes)
{
    return dxball_heap_api.allocate(dxball_runtime_heap, 0, bytes);
}

/* 0x00419EA0: every nonzero callback result, including negatives, is true. */
DxBallInt DXBALL_NEW_CALL dxball_call_new_handler(DxBallUInt bytes)
{
    if (dxball_new_handler != NULL && dxball_new_handler(bytes) != 0) return 1;
    return 0;
}
