#include "runtime_resize.h"

/* FUNCTION: DXBALL 0x0041F590 */
void *DXBALL_NEW_CALL dxball_runtime_calloc(DxBallUInt count, DxBallUInt bytes)
{
    void *value;
    bytes *= count;
    bytes = bytes ? bytes : 1;
    for (;;) {
        if (bytes > 0xffffffe0U) value = NULL;
        else value = HeapAlloc(dxball_runtime_heap, 8, bytes);
        if (value != NULL || dxball_malloc_mode == 0) return value;
        if (!dxball_call_new_handler(bytes)) return NULL;
    }
}

/* FUNCTION: DXBALL 0x0041FD70 */
void *DXBALL_NEW_CALL dxball_runtime_realloc(void *memory, DxBallUInt bytes)
{
    void *value;
    if (memory == NULL) return dxball_runtime_malloc(bytes);
    if (bytes == 0) {
        dxball_heap_release(memory);
        return NULL;
    }
    for (;;) {
        if (bytes > 0xffffffe0U) value = NULL;
        else value = HeapReAlloc(dxball_runtime_heap, 0, memory, bytes);
        if (value != NULL || dxball_malloc_mode == 0) return value;
        if (!dxball_call_new_handler(bytes)) return NULL;
    }
}

/* FUNCTION: DXBALL 0x0041FDE0 */
size_t DXBALL_NEW_CALL dxball_runtime_msize(void *memory)
{
    return HeapSize(dxball_runtime_heap, 0, memory);
}
