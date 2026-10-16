#include <stddef.h>

extern "C" {
#include "allocator.h"
}

/* The recovered runtime owns allocation and release together. These C++ API
   adapters keep typed new/delete on that same heap and fixture boundary.
   Game object requests remain within the original unsigned32 size domain.
   The ELF link map keeps these adapters local to this library. */
void *operator new(size_t bytes)
{
    return dxball_allocate_with_handler((DxBallUInt)bytes, 1);
}

void operator delete(void *memory) throw()
{
    dxball_heap_release(memory);
}
