#ifndef DXBALL_RUNTIME_CPP_FILTER_H
#define DXBALL_RUNTIME_CPP_FILTER_H
#include "runtime_cpp_transfer.h"
#include "runtime_error_control.h"

typedef DxBallCrtLong (DXBALL_CRT_OS_CALL *DxBallCppUnhandledFilter)(DxBallCppExceptionPointers *);
#ifdef __cplusplus
extern "C" {
extern DxBallCppUnhandledFilter dxball_cpp_previous_filter;
DXBALL_CRT_IMPORT DxBallCppUnhandledFilter DXBALL_CRT_OS_CALL SetUnhandledExceptionFilter(
    DxBallCppUnhandledFilter filter);
DxBallCrtLong DXBALL_CRT_OS_CALL dxball_cpp_unhandled_filter(DxBallCppExceptionPointers *);
void dxball_cpp_restore_unhandled_filter(void);
}
#endif
#endif
