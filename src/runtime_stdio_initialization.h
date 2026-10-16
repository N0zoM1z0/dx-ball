#ifndef DXBALL_RUNTIME_STDIO_INITIALIZATION_H
#define DXBALL_RUNTIME_STDIO_INITIALIZATION_H

#include "runtime_stream_transfer.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char dxball_crt_standard_input_buffer[4096];
void dxball_crt_initialize_stdio(void);

#ifdef __cplusplus
}
#endif
#endif
