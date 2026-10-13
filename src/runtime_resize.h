#ifndef DXBALL_RUNTIME_RESIZE_H
#define DXBALL_RUNTIME_RESIZE_H

#include "allocator.h"

/* Heap identity and allocation mode retain the allocator's existing ownership. */
#if defined(_WIN32)
__declspec(dllimport)
#endif
void *DXBALL_HEAP_CALL HeapReAlloc(void *heap, DxBallUInt flags,
                                  void *memory, size_t bytes);
#if defined(_WIN32)
__declspec(dllimport)
#endif
size_t DXBALL_HEAP_CALL HeapSize(void *heap, DxBallUInt flags, const void *memory);
#if defined(_WIN32)
__declspec(dllimport)
#endif
void *DXBALL_HEAP_CALL HeapAlloc(void *heap, DxBallUInt flags, size_t bytes);
void *DXBALL_NEW_CALL dxball_runtime_calloc(DxBallUInt count, DxBallUInt bytes);
void *DXBALL_NEW_CALL dxball_runtime_realloc(void *memory, DxBallUInt bytes);
size_t DXBALL_NEW_CALL dxball_runtime_msize(void *memory);

#endif
