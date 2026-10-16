#ifndef DXBALL_RUNTIME_U64_ARITHMETIC_H
#define DXBALL_RUNTIME_U64_ARITHMETIC_H

#include "state_types.h"
#if defined(_MSC_VER)
typedef unsigned __int64 DxBallCrtUInt64;
#else
#include <stdint.h>
typedef uint64_t DxBallCrtUInt64;
#endif
typedef char DxBallCrtUInt64MustBe64Bits[(sizeof(DxBallCrtUInt64) == 8) ? 1 : -1];

#if defined(_WIN32) && !defined(_WIN64)
#define DXBALL_U64_CALL __stdcall
#else
#define DXBALL_U64_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif
DxBallCrtUInt64 DXBALL_U64_CALL dxball_crt_u64_divide(
    DxBallCrtUInt64 dividend, DxBallCrtUInt64 divisor);
DxBallCrtUInt64 DXBALL_U64_CALL dxball_crt_u64_remainder(
    DxBallCrtUInt64 dividend, DxBallCrtUInt64 divisor);
#ifdef __cplusplus
}
#endif
#endif
