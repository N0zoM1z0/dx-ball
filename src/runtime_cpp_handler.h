#ifndef DXBALL_RUNTIME_CPP_HANDLER_H
#define DXBALL_RUNTIME_CPP_HANDLER_H
#include "runtime_cpp_transfer.h"
#include "runtime_error_control.h"

/* Only the properties/type prefix is consumed here. */
struct DxBallCppCatchableType {
    unsigned int properties;
    const DxBallCppTypePrefix *type;
};
/* Compiler metadata stores count followed by a naturally aligned pointer
   sequence. first_type identifies its offset, not a one-element array bound. */
typedef struct DxBallCppCatchableArrayPrefix {
    int count;
    const DxBallCppCatchableType *first_type;
} DxBallCppCatchableArrayPrefix;
typedef struct DxBallCppThrowDetail {
    DxBallCppThrowPrefix prefix;
    const DxBallCppCatchableArrayPrefix *catchables;
} DxBallCppThrowDetail;

#ifdef __cplusplus
extern "C" {
extern DxBallCppExceptionRecord *dxball_cpp_current_exception;
extern DxBallCppContext *dxball_cpp_current_context;
void dxball_cpp_destruct_exception_object(DxBallCppExceptionRecord *, unsigned char);
}
#endif
#endif
