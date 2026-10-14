#ifndef DXBALL_RUNTIME_STREAM_OPERATIONS_H
#define DXBALL_RUNTIME_STREAM_OPERATIONS_H
#include "runtime_stream_transfer.h"
#include "runtime_stream_position.h"

#ifdef __cplusplus
extern "C" {
#endif
int dxball_crt_fseek(DxBallCrtStream *stream, DxBallCrtLong offset, int origin);
unsigned int dxball_crt_fwrite(const void *buffer, unsigned int element_size,
                             unsigned int elements, DxBallCrtStream *stream);
#ifdef __cplusplus
}
#endif
#endif
