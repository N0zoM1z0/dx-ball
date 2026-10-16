#include "runtime_cpp_catch.h"
#include <excpt.h>

DxBallCppExceptionRecord *dxball_cpp_current_exception = 0;
DxBallCppContext *dxball_cpp_current_context = 0;

/* FUNCTION: DXBALL 0x0041B820 */
void *dxball_cpp_call_catch_block(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context,
    const DxBallCppFunctionPrefix *function, void (*handler)(void), int nesting,
    unsigned int flags)
{
    void *continuation = (void *)handler;
    void *&frame_stack = ((DxBallCppFrameStackPrefix *)((char *)registration
        - offsetof(DxBallCppFrameStackPrefix, registration)))->saved_stack;
    void *saved_stack = frame_stack;
    DxBallCppExceptionRecord *saved_exception = dxball_cpp_current_exception;
    DxBallCppContext *saved_context = dxball_cpp_current_context;
    dxball_cpp_current_exception = exception;
    dxball_cpp_current_context = context;
    __try {
        __try {
            continuation = _CallCatchBlock2((EHRegistrationNode *)registration,
                (const _s_FuncInfo *)function, continuation, nesting, flags);
        } __except (dxball_cpp_rethrow_filter(
                (DxBallCppExceptionPointers *)_exception_info())) {
            continuation = 0;
            return 0;
        }
    } __finally {
        frame_stack = saved_stack;
        dxball_cpp_current_exception = saved_exception;
        dxball_cpp_current_context = saved_context;
        if (exception->code == 0xe06d7363U &&
                ((DxBallCppExceptionDetail *)exception)->parameter_count == 3 &&
                ((DxBallCppExceptionDetail *)exception)->information[0] == 0x19930520U &&
                continuation)
            dxball_cpp_destruct_exception_object(exception, _abnormal_termination());
    }
    return continuation;
}
