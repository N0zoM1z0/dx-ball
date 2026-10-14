#ifndef DXBALL_RUNTIME_MEMORY_FILL_H
#define DXBALL_RUNTIME_MEMORY_FILL_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
void *dxball_crt_fill_memory(void *destination, int value, size_t count);
#ifdef __cplusplus
}
#endif
#endif
