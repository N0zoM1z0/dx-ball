#ifndef DXBALL_RUNTIME_STREAM_POSITION_H
#define DXBALL_RUNTIME_STREAM_POSITION_H
#include "runtime_lowio.h"
#include "runtime_stream.h"

#ifdef __cplusplus
extern "C" {
#endif
DxBallCrtLong dxball_crt_ftell(DxBallCrtStream *stream);
#ifdef __cplusplus
}
#endif
#endif
