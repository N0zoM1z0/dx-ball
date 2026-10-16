#ifndef DXBALL_ALLOCATOR_IMPORTS_H
#define DXBALL_ALLOCATOR_IMPORTS_H

#include "allocator.h"

/* Separate original Heap import cells; the public table is a binding record. */
extern void *(DXBALL_HEAP_CALL *dxball_heap_create)(DxBallUInt flags, size_t initial, size_t maximum);
extern void *(DXBALL_HEAP_CALL *dxball_heap_alloc)(void *heap, DxBallUInt flags, size_t bytes);
extern DxBallInt (DXBALL_HEAP_CALL *dxball_heap_free)(void *heap, DxBallUInt flags, void *memory);

#endif
