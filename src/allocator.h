#ifndef DXBALL_ALLOCATOR_H
#define DXBALL_ALLOCATOR_H

#include "state_types.h"

#if defined(_WIN32)
#define DXBALL_HEAP_CALL __stdcall
#define DXBALL_NEW_CALL __cdecl
#else
#define DXBALL_HEAP_CALL
#define DXBALL_NEW_CALL
#endif

typedef DxBallInt (DXBALL_NEW_CALL *DxBallNewHandler)(DxBallUInt bytes);
typedef struct DxBallHeapApi {
    void *(DXBALL_HEAP_CALL *create)(DxBallUInt flags, size_t initial, size_t maximum);
    void *(DXBALL_HEAP_CALL *allocate)(void *heap, DxBallUInt flags, size_t bytes);
    DxBallInt (DXBALL_HEAP_CALL *release)(void *heap, DxBallUInt flags, void *memory);
} DxBallHeapApi;

/* Heap handles and pointers grow with the native host; request sizes retain
   the original unsigned 32-bit domain. The explicit host backend is replaced
   by typed Windows heap imports before game startup. */
extern void *dxball_runtime_heap;
extern DxBallNewHandler dxball_new_handler;
extern DxBallHeapApi dxball_heap_api;
extern DxBallInt dxball_malloc_mode;

void *DXBALL_NEW_CALL dxball_initialize_runtime_heap(void);
void *DXBALL_NEW_CALL dxball_runtime_malloc(DxBallUInt bytes);
void *DXBALL_NEW_CALL dxball_runtime_new(DxBallUInt bytes);
void DXBALL_NEW_CALL dxball_runtime_delete(void *memory);
void DXBALL_NEW_CALL dxball_heap_release(void *memory);
void *DXBALL_NEW_CALL dxball_allocate_with_handler(DxBallUInt bytes, DxBallInt enabled);
void *DXBALL_NEW_CALL dxball_heap_allocate(DxBallUInt bytes);
DxBallInt DXBALL_NEW_CALL dxball_call_new_handler(DxBallUInt bytes);

/* Dependency boundary helpers, not additional recovered original functions. */
void dxball_bind_heap_api(const DxBallHeapApi *api);
void *dxball_malloc_bytes(size_t bytes);
void *dxball_new_bytes(size_t bytes);

#endif
