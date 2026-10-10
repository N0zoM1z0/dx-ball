#include "memory.h"

void *(DXBALL_DDCALL *dxball_local_alloc)(DxBallUInt, size_t);
void *(DXBALL_DDCALL *dxball_local_free)(void *);
