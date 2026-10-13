#include "runtime_resize.h"

/* FUNCTION: DXBALL 0x0041FD70 */
void *DXBALL_NEW_CALL dxball_runtime_realloc(void *memory, DxBallUInt bytes)
{
    void *value;
    if (memory == NULL) return dxball_runtime_malloc(bytes);
    if (bytes == 0) {
        dxball_heap_release(memory);
        return NULL;
    }
    do {
        value = dxball_runtime_heap;
        if (bytes > 0xffffffe0U) value = NULL;
        else value = HeapReAlloc(value, 0, memory, bytes);
        if (value != NULL || dxball_malloc_mode == 0) return value;
    } while (dxball_call_new_handler(bytes));
    return NULL;
}

/* FUNCTION: DXBALL 0x0041FDE0 */
size_t DXBALL_NEW_CALL dxball_runtime_msize(void *memory)
{
    return HeapSize(dxball_runtime_heap, 0, memory);
}
