#ifndef DXBALL_MEMORY_H
#define DXBALL_MEMORY_H

#include "resources.h"

/* Shared Kernel32 local-memory imports used by Bitmap and MDS. */
extern void *(DXBALL_DDCALL *dxball_local_alloc)(DxBallUInt, size_t);
extern void *(DXBALL_DDCALL *dxball_local_free)(void *);

#endif
